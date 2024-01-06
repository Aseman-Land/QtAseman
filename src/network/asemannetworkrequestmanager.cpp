/*
    Copyright (C) 2019 Aseman Team
    http://aseman.io

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemannetworkrequestmanager.h"

#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QDebug>
#include <QPointer>
#include <QJsonDocument>
#include <QJsonDocument>
#include <QFile>
#include <QMimeDatabase>
#include <QFileInfo>

#if QT_CONFIG(http)
#include <QHttpMultiPart>
#endif

class AsemanNetworkRequestManager::Private
{
public:
#ifdef Q_OS_WASM
    static QNetworkAccessManager *accessManager;
#else
    QNetworkAccessManager *accessManager;
#endif
    QString boundaryToken;
    static int fullLog_env;
    bool ignoreSslErrors;
};

int AsemanNetworkRequestManager::Private::fullLog_env = -1;

#ifdef Q_OS_WASM
QNetworkAccessManager *AsemanNetworkRequestManager::Private::accessManager = nullptr;
#endif

AsemanNetworkRequestManager::AsemanNetworkRequestManager(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->ignoreSslErrors = false;

#ifdef QT_DEBUG
    if (Private::fullLog_env == -1)
        Private::fullLog_env = (qgetenv("QTASEMAN_NETWORK_DEBUG_MODE") == "true"? 1 : 0);
#else
    Private::fullLog_env = 0;
#endif

    p->boundaryToken = QStringLiteral("Aseman:292a15d1-64af-4ee2-82b5-2d42adb9fd43");

#ifdef Q_OS_WASM
    if (!p->accessManager)
        p->accessManager = new QNetworkAccessManager;
#else
    p->accessManager = new QNetworkAccessManager(this);
#endif
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::get(AsemanNetworkRequestObject *request, const QUrl &_url, const QVariantMap &keys, const QVariantMap &headers)
{
    const QUrlQuery query = queryOfMap(keys);

    QUrl url = _url;
    if (query.queryItems().count())
        url.setQuery(query);

    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
#ifdef ASEMAN_QT6
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
#else
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#endif

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, POST url:" << url.toString();

    addHeaderData(req, headers);

    switch (request->contentType())
    {
    case AsemanNetworkRequestObject::TypeWWWForm:
        req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        break;
    case AsemanNetworkRequestObject::TypeJson:
        req.setRawHeader("Content-Type", "application/json");
        break;
    }

    QNetworkReply *reply = p->accessManager->get(req);
    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(p->ignoreSslErrors || request->ignoreSslErrors(), reply);

    return reqReply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::post(AsemanNetworkRequestObject *request, const QUrl &url, const QByteArray &data, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
#ifdef ASEMAN_QT6
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
#else
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#endif
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.size()).toUtf8());

    addHeaderData(req, headers);

    switch (request->contentType())
    {
    case AsemanNetworkRequestObject::TypeWWWForm:
        req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        break;
    case AsemanNetworkRequestObject::TypeJson:
        req.setRawHeader("Content-Type", "application/json");
        break;
    }

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, POST url:" << url.toString() << "data-length:" << data.length();

    QNetworkReply *reply = p->accessManager->post(req, data);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(p->ignoreSslErrors || request->ignoreSslErrors(), reply);

    return reqReply;
}

#if QT_CONFIG(http)
AsemanNetworkRequestReply *AsemanNetworkRequestManager::post(AsemanNetworkRequestObject *request, const QUrl &url, QHttpMultiPart *parts, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
#ifdef ASEMAN_QT6
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
#else
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#endif

    addHeaderData(req, headers);

    req.setRawHeader("Content-Type", "multipart/form-data; boundary=\"" + p->boundaryToken.toUtf8() + "\"");

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, POST url:" << url.toString() << "data-length: uncalculatble";

    QNetworkReply *reply = p->accessManager->post(req, parts);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(p->ignoreSslErrors || request->ignoreSslErrors(), reply);

    return reqReply;
}
#endif

AsemanNetworkRequestReply *AsemanNetworkRequestManager::postForm(AsemanNetworkRequestObject *request, const QUrl &url, const QVariantMap &formData, const QVariantMap &headers)
{
#if QT_CONFIG(http)
    QHttpMultiPart *parts = generateFormData(formData);
    return AsemanNetworkRequestManager::post(request, url, parts, headers);
#else
    QByteArray data = generateForm(formData).toUtf8();
    QVariantMap newHeaders = headers;
    newHeaders["Content-Type"] = QVariant::fromValue<QString>("multipart/form-data; boundary=" + p->boundaryToken);
    return AsemanNetworkRequestManager::post(request, url, data, newHeaders);
#endif
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::customMethod(AsemanNetworkRequestObject *request, const QString &method, const QUrl &url, const QByteArray &data, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
#ifdef ASEMAN_QT6
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
#else
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#endif
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.size()).toUtf8());

    addHeaderData(req, headers);

    switch (request->contentType())
    {
    case AsemanNetworkRequestObject::TypeWWWForm:
        req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        break;
    case AsemanNetworkRequestObject::TypeJson:
        req.setRawHeader("Content-Type", "application/json");
        break;
    }

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, " + method.toUpper().toUtf8() + " url:" << url.toString() << "data-length:" << data.length();

    QNetworkReply *reply = p->accessManager->sendCustomRequest(req, method.toUtf8(), data);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(p->ignoreSslErrors || request->ignoreSslErrors(), reply);

    return reqReply;
}

#if QT_CONFIG(http)
AsemanNetworkRequestReply *AsemanNetworkRequestManager::customMethod(AsemanNetworkRequestObject *request, const QString &method, const QUrl &url, QHttpMultiPart *parts, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
#ifdef ASEMAN_QT6
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
#else
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#endif

    addHeaderData(req, headers);

    req.setRawHeader("Content-Type", "multipart/form-data; boundary=\"" + p->boundaryToken.toUtf8() + "\"");

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, " + method.toUpper().toUtf8() + " url:" << url.toString() << "data-length: uncalculatble";

    QNetworkReply *reply = p->accessManager->sendCustomRequest(req, method.toUtf8(), parts);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(p->ignoreSslErrors || request->ignoreSslErrors(), reply);

    return reqReply;
}
#endif

AsemanNetworkRequestReply *AsemanNetworkRequestManager::customMethodForm(AsemanNetworkRequestObject *request, const QString &method, const QUrl &url, const QVariantMap &formData, const QVariantMap &headers)
{
#if QT_CONFIG(http)
    QHttpMultiPart *parts = generateFormData(formData);
    return AsemanNetworkRequestManager::customMethod(request, method, url, parts, headers);
#else
    QByteArray data = generateForm(formData).toUtf8();
    QVariantMap newHeaders = headers;
    newHeaders["Content-Type"] = QVariant::fromValue<QString>("multipart/form-data; boundary=" + p->boundaryToken);
    return AsemanNetworkRequestManager::customMethod(request, method, url, data, newHeaders);
#endif
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::put(AsemanNetworkRequestObject *request, const QUrl &url, const QByteArray &data, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
#ifdef ASEMAN_QT6
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
#else
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#endif
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.size()).toUtf8());

    addHeaderData(req, headers);

    switch (request->contentType())
    {
    case AsemanNetworkRequestObject::TypeWWWForm:
        req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        break;
    case AsemanNetworkRequestObject::TypeJson:
        req.setRawHeader("Content-Type", "application/json");
        break;
    }

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, PUT url:" << url.toString() << "data-length:" + QString::number(data.size());

    QNetworkReply *reply = p->accessManager->put(req, data);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(p->ignoreSslErrors || request->ignoreSslErrors(), reply);

    return reqReply;
}

#if QT_CONFIG(http)
AsemanNetworkRequestReply *AsemanNetworkRequestManager::put(AsemanNetworkRequestObject *request, const QUrl &url, QHttpMultiPart *parts, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
#ifdef ASEMAN_QT6
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
#else
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
#endif

    addHeaderData(req, headers);

    req.setRawHeader("Content-Type", "multipart/form-data; boundary=\"" + p->boundaryToken.toUtf8() + "\"");

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, POST url:" << url.toString() << "data-length: uncalculatble";

    QNetworkReply *reply = p->accessManager->put(req, parts);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(p->ignoreSslErrors || request->ignoreSslErrors(), reply);

    return reqReply;
}
#endif

AsemanNetworkRequestReply *AsemanNetworkRequestManager::putForm(AsemanNetworkRequestObject *request, const QUrl &url, const QVariantMap &formData, const QVariantMap &headers)
{
#if QT_CONFIG(http)
    QHttpMultiPart *parts = generateFormData(formData);
    return AsemanNetworkRequestManager::put(request, url, parts, headers);
#else
    QByteArray data = generateForm(formData).toUtf8();
    QVariantMap newHeaders = headers;
    newHeaders["Content-Type"] = QVariant::fromValue<QString>("multipart/form-data; boundary=" + p->boundaryToken);
    return AsemanNetworkRequestManager::put(request, url, data, newHeaders);
#endif
}

void AsemanNetworkRequestManager::processPostedRequest(AsemanNetworkRequestReply *reply, AsemanNetworkRequestObject *request, std::function<QVariant (QByteArray)> dataConvertMethod)
{
    request->setError(QStringLiteral(""));
    request->setSslErrors(QStringLiteral(""));
    request->setResult(QVariant(), -1);
    request->setRefreshing(true);

    QPointer<AsemanNetworkRequestObject> req = request;
    connect(reply, &AsemanNetworkRequestReply::finished, this, [req, dataConvertMethod](qint32 status, const QByteArray &data){
        QVariant response;
        if (dataConvertMethod)
            response = dataConvertMethod(data);
        else
            response = QVariant::fromValue<QByteArray>(data);

        req->setResult(response, status);
        req->setRefreshing(false);
    });
    connect(reply, &AsemanNetworkRequestReply::error, this, [req](const QString &errorString, QNetworkReply::NetworkError){
        req->setError(errorString);
        req->setRefreshing(false);
    });
#if QT_CONFIG(ssl)
    connect(reply, &AsemanNetworkRequestReply::sslErrors, this, [req](const QString &errorString){
        req->setSslErrors(errorString);
    });
#endif
    connect(reply, &AsemanNetworkRequestReply::uploadProgress, req, &AsemanNetworkRequestObject::uploadProgress);
    connect(reply, &AsemanNetworkRequestReply::downloadProgress, req, &AsemanNetworkRequestObject::downloadProgress);
}

QUrlQuery AsemanNetworkRequestManager::queryOfMap(const QVariantMap &keys) const
{
    QUrlQuery query;
    QMapIterator<QString, QVariant> i(keys);
    while (i.hasNext())
    {
        i.next();
        QVariant var = i.value();
        if (var.type() != QVariant::String)
            var.convert(QVariant::String);

        query.addQueryItem(i.key(), var.toString());
    }

    return query;
}

QByteArray AsemanNetworkRequestManager::variantToData(const QVariant &var) const
{
    QByteArray data;
    QVariant dataVar = var;
    switch (static_cast<qint32>(dataVar.type()))
    {
    case QVariant::String:
        data = dataVar.toString().toUtf8();
        break;

    case QVariant::ByteArray:
        data = dataVar.toByteArray();
        break;

    default:
        dataVar.convert(QVariant::String);
        data = dataVar.toString().toUtf8();
        break;
    }
    return data;
}

QVariant AsemanNetworkRequestManager::processData(AsemanNetworkRequestReply *reply, const QByteArray &data) const
{
    if (reply->headers().value(QStringLiteral("content-type")).toString().contains(QStringLiteral("application/json")))
        return QJsonDocument::fromJson(data).toVariant();
    else
        return QVariant::fromValue(data);
}

void AsemanNetworkRequestManager::addHeaderData(QNetworkRequest &request, const QVariantMap &headers)
{
    QMapIterator<QString, QVariant> i(headers);
    while (i.hasNext())
    {
        i.next();
        QVariant var = i.value();
        if (var.type() != QVariant::String)
            var.convert(QVariant::String);

        request.setRawHeader(i.key().toUtf8(), var.toString().toUtf8());
    }
}

#if QT_CONFIG(http)
QHttpMultiPart *AsemanNetworkRequestManager::generateFormData(const QVariantMap &map)
{
    QHttpMultiPart *parts = new QHttpMultiPart(this);
    parts->setBoundary(p->boundaryToken.toUtf8());

    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext())
    {
        i.next();
        QVariant var = i.value();
        if (var.type() == QVariant::Url)
        {
            QUrl source = var.toUrl();
            QString filePath = source.toLocalFile();
            if (filePath.isEmpty() && !source.isEmpty())
                filePath = source.toString();

            QFile *file = new QFile(filePath);
            file->open(QIODevice::ReadOnly);
            file->setParent(parts);

            QMimeDatabase mimeDb;

            QHttpPart imagePart;
            imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mimeDb.mimeTypeForFile(filePath).name()));
            imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + i.key().toUtf8() + "\"; filename=\"" + QFileInfo(filePath).fileName() + "\""));
            imagePart.setBodyDevice(file);

            parts->append(imagePart);
        }
        else
        {
            if (var.type() != QVariant::String)
                var.convert(QVariant::String);

            QHttpPart part;
            part.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant("form-data; name=\"" + i.key().toUtf8() + "\""));
            part.setBody(i.value().toString().toUtf8());

            parts->append(part);
        }
    }

    return parts;
}
#endif

QString AsemanNetworkRequestManager::generateWWWFormData(const QVariantMap &map, bool ignoreEmpty) const
{
    QUrlQuery query;
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext())
    {
        i.next();
        QVariant var = i.value();
        if (var.type() != QVariant::String)
            var.convert(QVariant::String);
        if (ignoreEmpty && var.toString().isEmpty())
            continue;

        query.addQueryItem(i.key(), var.toString());
    }
    return query.query();
}

QString AsemanNetworkRequestManager::generateForm(const QVariantMap &map, bool ignoreEmpty) const
{
    QString query;
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext())
    {
        i.next();
        QVariant var = i.value();
        if (var.type() != QVariant::String)
            var.convert(QVariant::String);
        if (ignoreEmpty && var.toString().isEmpty())
            continue;

        query += QStringLiteral("--%1\r\nContent-Disposition: form-data; name=\"%2\"\r\n\r\n%3\r\n")
                .arg(p->boundaryToken)
                .arg(i.key())
                .arg(var.toString());
    }

    query += "--" + p->boundaryToken + "--\r\n";
    return query;
}

QString AsemanNetworkRequestManager::generateJson(const QVariantMap &map) const
{
    return QString::fromUtf8( QJsonDocument::fromVariant(map).toJson(QJsonDocument::Compact) );
}

QByteArray AsemanNetworkRequestManager::requestData(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    switch (static_cast<qint32>(request->contentType()))
    {
    case AsemanNetworkRequestObject::TypeForm:
        return generateForm(ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()).toUtf8();
    case AsemanNetworkRequestObject::TypeWWWForm:
        return generateWWWFormData(ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()).toUtf8();
    case AsemanNetworkRequestObject::TypeJson:
        return generateJson(ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()).toUtf8();
    default:
        return variantToData(request->data());
    }
    return QByteArray();
}

QVariantMap AsemanNetworkRequestManager::removeEmptyValues(const QVariantMap &data)
{
    QVariantMap requestData;
    QVariantMap map = data;
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext())
    {
        i.next();
        if (i.value().type() == QVariant::String && i.value().toString().isEmpty())
            continue;

        requestData[i.key()] = i.value();
    }
    return requestData;
}

void AsemanNetworkRequestManager::setBoundaryToken(const QString &boundaryToken)
{
    if (p->boundaryToken == boundaryToken)
        return;

    p->boundaryToken = boundaryToken;
    Q_EMIT boundaryTokenChanged();
}

QString AsemanNetworkRequestManager::boundaryToken() const
{
    return p->boundaryToken;
}

void AsemanNetworkRequestManager::setIgnoreSslErrors(bool ignoreSslErrors)
{
    if (p->ignoreSslErrors == ignoreSslErrors)
        return;

    p->ignoreSslErrors = ignoreSslErrors;
    Q_EMIT ignoreSslErrorsChanged();
}

bool AsemanNetworkRequestManager::ignoreSslErrors() const
{
    return p->ignoreSslErrors;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::get(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    QVariantMap keys = ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap();
    AsemanNetworkRequestReply *reply = get(request, request->url(), keys, request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::post(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    AsemanNetworkRequestReply *reply;
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = postForm(request, request->url(), (ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()), request->headers());
    else
        reply = post(request, request->url(), requestData(request, ignoreEmptyValues), request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::put(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    AsemanNetworkRequestReply *reply;
#if QT_CONFIG(http)
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = putForm(request, request->url(), (ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()), request->headers());
    else
#endif
        reply = put(request, request->url(), requestData(request, ignoreEmptyValues), request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::patch(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    return customMethod(QStringLiteral("PATCH"), request, ignoreEmptyValues);
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::deleteMethod(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    return customMethod(QStringLiteral("DELETE"), request, ignoreEmptyValues);
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::customMethod(const QString &method, AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    AsemanNetworkRequestReply *reply;
#if QT_CONFIG(http)
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = customMethodForm(request, method, request->url(), (ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()), request->headers());
    else
#endif
        reply = customMethod(request, method, request->url(), requestData(request, ignoreEmptyValues), request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestManager::~AsemanNetworkRequestManager()
{
    delete p;
}
