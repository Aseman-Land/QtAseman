#include "asemanhttpserver.h"
#include "qhttpserver.hpp"

#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

#include <QRunnable>
#include <QThreadPool>

using namespace qhttp::server;

QList<AsemanHttpServer::Responder*> AsemanHttpServer::Responder::mGarbages;
QMutex AsemanHttpServer::Responder::mMutex;

class AsemanHttpServer::Private
{
public:
    class CallbackPack {
    public:
        AsyncRouteCallback async;
        SyncRouteCallback sync;
        bool thread;
        QString path;
        AsemanHttpServer::HttpMethod method;
    };

    QHttpServer *server;
    QHash<int, QHash<QString, QList<CallbackPack>>> routes;
    QHash<QHttpRequest*, QByteArray> requestsData;

    QThreadPool *pool;

    void route(CallbackPack callback);
    void handle(AsemanHttpServer *parent, QHttpRequest* req, QHttpResponse* res);
    void call_auto(AsemanHttpServer *parent, const CallbackPack &pk, QHttpRequest *, QHttpResponse *res);
    void call(AsemanHttpServer *parent, const CallbackPack &pk, QHttpRequest *, QHttpResponse *res, const QByteArray &data);
};

AsemanHttpServer::AsemanHttpServer(QObject *parent)
    : QObject(parent)
{
    p = new Private;
    p->server = Q_NULLPTR;
    p->pool = Q_NULLPTR;
}

void AsemanHttpServer::listen(const QString &host, quint16 port)
{
    if (p->server)
        stop();
    if (!p->pool)
        p->pool = new QThreadPool(this);

    p->server = new QHttpServer(this);

    connect(p->server, &QHttpServer::newRequest, this, [this](QHttpRequest* req, QHttpResponse* res){
        p->handle(this, req, res);
    });

    p->server->listen(QHostAddress(host), port);
}

void AsemanHttpServer::stop()
{
    p->server->stopListening();
    p->server->deleteLater();
    p->server = Q_NULLPTR;
}

void AsemanHttpServer::response(void *core, const QByteArray &data, int status, const QString &contentType)
{
    auto responder = static_cast<QHttpResponse*>(core);

    if (contentType.length())
        responder->addHeader("Content-Type", contentType.toUtf8());

    responder->setStatusCode(static_cast<qhttp::TStatusCode>(status));
    responder->end(data);
}

void AsemanHttpServer::cleanGarbages()
{
    QMutexLocker locker(&AsemanHttpServer::Responder::mMutex);
    for (auto g: AsemanHttpServer::Responder::mGarbages)
        delete g;

    AsemanHttpServer::Responder::mGarbages.clear();
}

AsemanHttpServer::~AsemanHttpServer()
{
    delete p->server;
    delete p;
}

void AsemanHttpServer::route(const QString &path, HttpMethod method, AsemanHttpServer::AsyncRouteCallback callback, bool threaded)
{
    Private::CallbackPack pack;
    pack.async = callback;
    pack.sync = Q_NULLPTR;
    pack.thread = threaded;
    pack.path = path;
    pack.method = method;

    p->route(pack);
}

void AsemanHttpServer::route(const QString &path, HttpMethod method, AsemanHttpServer::SyncRouteCallback callback, bool threaded)
{
    Private::CallbackPack pack;
    pack.async = Q_NULLPTR;
    pack.sync = callback;
    pack.thread = threaded;
    pack.path = path;
    pack.method = method;

    p->route(pack);
}

void AsemanHttpServer::Private::route(AsemanHttpServer::Private::CallbackPack callback)
{
    auto path = callback.path;
    auto idx = path.indexOf(QStringLiteral("<"));
    if (idx > -1)
        path = path.left(idx);

    routes[static_cast<int>(callback.method)][path] << callback;
}

void AsemanHttpServer::Private::handle(AsemanHttpServer *parent, QHttpRequest *req, QHttpResponse *res)
{
    const auto &url = req->url();
    const auto &methodString = url.path();
    const auto routesList = routes[static_cast<int>(req->method())];
    if (routesList.isEmpty())
    {
        res->setStatusCode(qhttp::ESTATUS_NOT_FOUND);
        res->end();
        return;
    }

    if (routesList.contains(methodString))
    {
        const auto &pks = routesList.value(methodString);
        for (const auto &pk: pks)
            if (pk.path == methodString)
            {
                call_auto(parent, pk, req, res);
                return;
            }
    }

    QString adrs;
    QStringList parts = methodString.split('/');
    const auto cnt = parts.count();
    for (int idx=0; idx<cnt; idx++)
    {
        adrs += parts.at(idx) + QStringLiteral("/");

        const auto &packs = routesList.value(adrs);
        for (const auto &pk: packs)
        {
            auto pk_parts = pk.path.split('/');
            if (cnt == pk_parts.count())
            {
                bool is_that = true;
                for (int i=0; i<cnt; i++)
                {
                    auto parts_item = parts.at(i);
                    auto pk_item = pk_parts.at(i);
                    if (parts_item == pk_item)
                        continue;
                    if (pk_item.count() > 2 && pk_item.left(1) == QStringLiteral("<") && pk_item.right(1) == QStringLiteral(">"))
                        continue;

                    is_that = false;
                    break;
                }

                if (is_that)
                {
                    call_auto(parent, pk, req, res);
                    return;
                }
            }
        }
    }

    res->setStatusCode(qhttp::ESTATUS_NOT_FOUND);
    res->end();
}

void AsemanHttpServer::Private::call_auto(AsemanHttpServer *parent, const AsemanHttpServer::Private::CallbackPack &pk, QHttpRequest *req, QHttpResponse *res)
{
    QObject::connect(req, &QHttpRequest::data, parent, [this, req](QByteArray data){
        requestsData[req] += data;
    });

    QObject::connect(req, &QHttpRequest::end, parent, [parent, pk, req, res, this](){
        if (pk.thread)
        {
            class CallRunnable: public QRunnable
            {
            public:
                AsemanHttpServer *parent;
                AsemanHttpServer::Private::CallbackPack pk;
                QHttpRequest *req;
                QHttpResponse *res;
                QByteArray data;

                void run() {
                    parent->p->call(parent, pk, req, res, data);
                }
            };

            auto r = new CallRunnable;
            r->parent = parent;
            r->pk = pk;
            r->req = req;
            r->res = res;
            r->data = requestsData.take(req);
            r->setAutoDelete(true);

            pool->start(r);
        }
        else
            call(parent, pk, req, res, requestsData.take(req));
    });
}

void AsemanHttpServer::Private::call(AsemanHttpServer *parent, const AsemanHttpServer::Private::CallbackPack &pk, QHttpRequest *req, QHttpResponse *res, const QByteArray &data)
{
    Request request;
    request.mUrl = req->url();
    request.mQuery = QUrlQuery(request.mUrl);
    request.mHeaders = req->headers();
    request.mMethod = static_cast<AsemanHttpServer::HttpMethod>(req->method());
    request.mRemoteAddress = req->remoteAddress();
    request.mBody = data;
    request.mRoutePath = pk.path;

    if (pk.async)
    {
        auto responder = new Responder(parent, res, pk.thread);
        pk.async(request, responder);
    }
    else
    if (pk.sync)
    {
        auto responder = pk.sync(request);
        int status_int = static_cast<int>(responder.mStatus);
        if (pk.thread)
            QMetaObject::invokeMethod(parent, "response", Qt::QueuedConnection, Q_ARG(void*, res), Q_ARG(QByteArray, responder.mData), Q_ARG(int, status_int), Q_ARG(QString, responder.mContentType));
        else
            parent->response(res, responder.mData, status_int, responder.mContentType);
    }
}

void AsemanHttpServer::Responder::write(const QByteArray &data, StatusCode status, const QString &contentType)
{
    auto responder = static_cast<QHttpResponse*>(mResponseCore);
    int status_int = static_cast<int>(status);
    if (mThreaded)
        QMetaObject::invokeMethod(mParent, "response", Qt::QueuedConnection, Q_ARG(void*, responder), Q_ARG(QByteArray, data), Q_ARG(int, status_int), Q_ARG(QString, contentType));
    else
        mParent->response(responder, data, status_int, contentType);

    QMutexLocker locker(&mMutex);
    mGarbages << this;
}
