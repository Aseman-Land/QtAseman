#include "asemannetworkrequest.h"

#include <QBuffer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QQmlEngine>

class AsemanNetworkRequest::Private
{
public:
    QHash<QNetworkReply*, QByteArray> buffers;
    qint32 httpStatusCode;
};

AsemanNetworkRequest::AsemanNetworkRequest(QObject *parent) :
    QObject(parent)
{
    p = new Private;
}

void AsemanNetworkRequest::post(const QString &address, const QVariantMap &urlQuery, const QString &data, const QJSValue &callback, const QString &type)
{
    QNetworkAccessManager *am = new QNetworkAccessManager(this);

    QUrlQuery query;
    QMapIterator<QString, QVariant> i(urlQuery);
    while(i.hasNext())
    {
        i.next();
        query.addQueryItem(i.key(), i.value().toString());
    }

    QUrl url(address);
    url.setQuery(query);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, type);

    QNetworkReply *reply = am->post(req, data.toUtf8());
    p->buffers[reply] = QByteArray();

    connect(reply, &QNetworkReply::readyRead, this, [this, reply](){
        p->buffers[reply] += reply->readAll();
        p->httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply, callback](){
        QString result = p->buffers.take(reply);

        QQmlEngine *engine = qmlEngine(this);
        if(engine && callback.isCallable())
        {

            QJSValueList args;
            args << engine->toScriptValue<QString>(result);
            args << p->httpStatusCode;

            QJSValue(callback).call(args);
        }

        reply->deleteLater();
    });
}

void AsemanNetworkRequest::get(const QString &address, const QVariantMap &urlQuery, const QJSValue &callback)
{
    QNetworkAccessManager *am = new QNetworkAccessManager(this);

    QUrlQuery query;
    QMapIterator<QString, QVariant> i(urlQuery);
    while(i.hasNext())
    {
        i.next();
        query.addQueryItem(i.key(), i.value().toString());
    }

    QUrl url(address);
    url.setQuery(query);

    QNetworkRequest req(url);

    QNetworkReply *reply = am->get(req);
    p->buffers[reply] = QByteArray();

    connect(reply, &QNetworkReply::readyRead, this, [this, reply](){
        p->buffers[reply] += reply->readAll();
        p->httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply, callback](){
        QString result = p->buffers.take(reply);

        QQmlEngine *engine = qmlEngine(this);
        if(engine && callback.isCallable())
        {

            QJSValueList args;
            args << engine->toScriptValue<QString>(result);
            args << p->httpStatusCode;

            QJSValue(callback).call(args);
        }

        reply->deleteLater();
    });
}

AsemanNetworkRequest::~AsemanNetworkRequest()
{
    delete p;
}
