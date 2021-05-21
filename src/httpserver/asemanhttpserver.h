#ifndef ASEMANHTTPSERVER_H
#define ASEMANHTTPSERVER_H

#include <QJsonDocument>
#include <QMutex>
#include <QObject>
#include <QUrlQuery>

#include <functional>

#include "asemanhttpserver_global.h"

class LIBQTASEMAN_HTTPSERVER_EXPORT AsemanHttpServer : public QObject
{
    Q_OBJECT
    class Private;
public:
    enum class HttpMethod {
        DELETE         =  0,        ///< DELETE
        GET            =  1,        ///< GET
        HEAD           =  2,        ///< HEAD
        POST           =  3,        ///< POST
        PUT            =  4,        ///< PUT
        /* pathological */
        CONNECT        =  5,        ///< CONNECT
        OPTIONS        =  6,        ///< OPTIONS
        TRACE          =  7,        ///< TRACE
        /* webdav */
        COPY           =  8,        ///< COPY
        LOCK           =  9,        ///< LOCK
        MKCOL          = 10,        ///< MKCOL
        MOVE           = 11,        ///< MOVE
        PROPFIND       = 12,        ///< PROPFIND
        PROPPATCH      = 13,        ///< PROPPATCH
        SEARCH         = 14,        ///< SEARCH
        UNLOCK         = 15,        ///< UNLOCK
        BIND           = 16,        ///< BIND
        REBIND         = 17,        ///< REBIND
        UNBIND         = 18,        ///< UNBIND
        ACL            = 19,        ///< ACL
        /* subversion */
        REPORT         = 20,        ///< REPORT
        MKACTIVITY     = 21,        ///< MKACTIVITY
        CHECKOUT       = 22,        ///< CHECKOUT
        MERGE          = 23,        ///< MERGE
        /* upnp */
        MSEARCH        = 24,        ///< M-SEARCH
        NOTIFY         = 25,        ///< NOTIFY
        SUBSCRIBE      = 26,        ///< SUBSCRIBE
        UNSUBSCRIBE    = 27,        ///< UNSUBSCRIBE
        /* RFC-5789 */
        PATCH          = 28,        ///< PATCH
        PURGE          = 29,        ///< PURGE
        /* CalDAV */
        MKCALENDAR     = 30,        ///< MKCALENDAR
        /* RFC-2068, section 19.6.1.2 */
        LINK           = 31,        ///< LINK
        UNLINK         = 32,        ///< UNLINK
    };
    enum class StatusCode {
         CONTINUE                           = 100,
         SWITCH_PROTOCOLS                   = 101,
         OK                                 = 200,
         CREATED                            = 201,
         ACCEPTED                           = 202,
         NON_AUTHORITATIVE_INFORMATION      = 203,
         NO_CONTENT                         = 204,
         RESET_CONTENT                      = 205,
         PARTIAL_CONTENT                    = 206,
         MULTI_STATUS                       = 207,
         MULTIPLE_CHOICES                   = 300,
         MOVED_PERMANENTLY                  = 301,
         FOUND                              = 302,
         SEE_OTHER                          = 303,
         NOT_MODIFIED                       = 304,
         USE_PROXY                          = 305,
         TEMPORARY_REDIRECT                 = 307,
         BAD_REQUEST                        = 400,
         UNAUTHORIZED                       = 401,
         PAYMENT_REQUIRED                   = 402,
         FORBIDDEN                          = 403,
         NOT_FOUND                          = 404,
         METHOD_NOT_ALLOWED                 = 405,
         NOT_ACCEPTABLE                     = 406,
         PROXY_AUTHENTICATION_REQUIRED      = 407,
         REQUEST_TIMEOUT                    = 408,
         CONFLICT                           = 409,
         GONE                               = 410,
         LENGTH_REQUIRED                    = 411,
         PRECONDITION_FAILED                = 412,
         REQUEST_ENTITY_TOO_LARGE           = 413,
         REQUEST_URI_TOO_LONG               = 414,
         REQUEST_UNSUPPORTED_MEDIA_TYPE     = 415,
         REQUESTED_RANGE_NOT_SATISFIABLE    = 416,
         EXPECTATION_FAILED                 = 417,
         INTERNAL_SERVER_ERROR              = 500,
         NOT_IMPLEMENTED                    = 501,
         BAD_GATEWAY                        = 502,
         SERVICE_UNAVAILABLE                = 503,
         GATEWAY_TIMEOUT                    = 504,
         HTTP_VERSION_NOT_SUPPORTED         = 505
    };

    class Responder;
    class Request;
    class SyncResponder;

    AsemanHttpServer(QObject *parent = Q_NULLPTR);
    virtual ~AsemanHttpServer();

    using AsyncRouteCallback = std::function<void (const Request &request, Responder *responder)>;
    using SyncRouteCallback = std::function<SyncResponder (const Request &request)>;

    void route(const QString &path, HttpMethod method, AsyncRouteCallback callback, bool threaded = false);
    void route(const QString &path, HttpMethod method, SyncRouteCallback callback, bool threaded = false);

public Q_SLOTS:
    void listen(const QString &host, quint16 port);
    void stop();

Q_SIGNALS:

private Q_SLOTS:
    void response(void *core, const QByteArray &data, int status, const QString &contentType);

protected:
    void cleanGarbages();

private:
    Private *p;
};


class LIBQTASEMAN_HTTPSERVER_EXPORT AsemanHttpServer::SyncResponder
{
    friend class AsemanHttpServer;
public:
    SyncResponder(const QJsonDocument &doc, StatusCode status = StatusCode::OK) : SyncResponder(doc.toJson(QJsonDocument::Compact), status, QStringLiteral("application/json")) {}
    SyncResponder(const QString &text, StatusCode status = StatusCode::OK, const QString &contentType = QString()) : SyncResponder(text.toUtf8(), status, contentType) {}
    SyncResponder(const char *data, StatusCode status = StatusCode::OK, const QString &contentType = QString()) : SyncResponder(QByteArray(data), status, contentType) {}
    SyncResponder(const QByteArray &data, StatusCode status = StatusCode::OK, const QString &contentType = QString()) : mData(data), mStatus(status), mContentType(contentType) {}

private:
    QByteArray mData;
    StatusCode mStatus;
    QString mContentType;
};

class LIBQTASEMAN_HTTPSERVER_EXPORT AsemanHttpServer::Responder
{
    friend class AsemanHttpServer;
public:
    void write(const QJsonDocument &doc, StatusCode status = StatusCode::OK) { write(doc.toJson(QJsonDocument::Compact), status, QStringLiteral("application/json")); }
    void write(const QString &text, StatusCode status = StatusCode::OK, const QString &contentType = QString()) { write(text.toUtf8(), status, contentType); }
    void write(const QByteArray &data, StatusCode status = StatusCode::OK, const QString &contentType = QString());

private:
    Responder(AsemanHttpServer *parent, void *responseCore, bool threaded)
        : mParent(parent), mResponseCore(responseCore), mThreaded(threaded) {}

    AsemanHttpServer *mParent;
    void *mResponseCore;
    bool mThreaded;
    static QList<Responder*> mGarbages;
    static QMutex mMutex;
};

class LIBQTASEMAN_HTTPSERVER_EXPORT AsemanHttpServer::Request
{
    friend class AsemanHttpServer;
public:
    QByteArray body() const { return mBody; };
    QHash<QByteArray, QByteArray> headers() const { return mHeaders; };
    AsemanHttpServer::HttpMethod method() const { return mMethod; };
    QString remoteAddress() const { return mRemoteAddress; };
    QUrl url() const { return mUrl; };
    QUrlQuery query() const { return mQuery; }

    template<typename T>
    T arg(const QString &key) const {
        return qvariant_cast<T>(QVariant::fromValue(mQuery.queryItemValue(key)));
    }

private:
    Request() {}

    QByteArray mBody;
    QHash<QByteArray, QByteArray> mHeaders;
    AsemanHttpServer::HttpMethod mMethod;
    QString mRemoteAddress;
    QUrl mUrl;
    QUrlQuery mQuery;

};

typedef AsemanHttpServer QAsemanHttpServer;

#endif // ASEMANHTTPSERVER_H
