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
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <asemantools.h>
#include <QFile>
#include <QMimeDatabase>
#include <QFileInfo>

class AsemanNetworkRequestManager::Private
{
public:
    QNetworkAccessManager *accessManager;
    QString boundaryToken;
    static int fullLog_env;
};

int AsemanNetworkRequestManager::Private::fullLog_env = -1;

AsemanNetworkRequestManager::AsemanNetworkRequestManager(QObject *parent) :
    QObject(parent)
{
    p = new Private;

#ifdef QT_DEBUG
    if (Private::fullLog_env == -1)
        Private::fullLog_env = (qgetenv("QTASEMAN_NETWORK_DEBUG_MODE") == "true"? 1 : 0);
#else
    Private::fullLog_env = 0;
#endif

    p->boundaryToken = QStringLiteral("Aseman:292a15d1-64af-4ee2-82b5-2d42adb9fd43");

    p->accessManager = new QNetworkAccessManager(this);
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::get(const QUrl &_url, const QVariantMap &keys, const QVariantMap &headers)
{
    const QUrlQuery query = queryOfMap(keys);

    QUrl url = _url;
    if (query.queryItems().count())
        url.setQuery(query);

    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, POST url:" << url.toString();

    addHeaderData(req, headers);

    QNetworkReply *reply = p->accessManager->get(req);
    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(reply);

    return reqReply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::post(const QUrl &url, const QByteArray &data, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.size()).toUtf8());

    addHeaderData(req, headers);

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, POST url:" << url.toString() << "data-length:" << data.length();

    QNetworkReply *reply = p->accessManager->post(req, data);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(reply);

    return reqReply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::post(const QUrl &url, QHttpMultiPart *parts, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    addHeaderData(req, headers);

    req.setRawHeader("Content-Type", "multipart/form-data; boundary=\"" + p->boundaryToken.toUtf8() + "\"");

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, POST url:" << url.toString() << "data-length: uncalculatble";

    QNetworkReply *reply = p->accessManager->post(req, parts);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(reply);

    return reqReply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::customMethod(const QString &method, const QUrl &url, const QByteArray &data, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.size()).toUtf8());

    addHeaderData(req, headers);

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, " + method.toUpper().toUtf8() + " url:" << url.toString() << "data-length:" << data.length();

    QNetworkReply *reply = p->accessManager->sendCustomRequest(req, method.toUtf8(), data);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(reply);

    return reqReply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::customMethod(const QString &method, const QUrl &url, QHttpMultiPart *parts, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    addHeaderData(req, headers);

    req.setRawHeader("Content-Type", "multipart/form-data; boundary=\"" + p->boundaryToken.toUtf8() + "\"");

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, " + method.toUpper().toUtf8() + " url:" << url.toString() << "data-length: uncalculatble";

    QNetworkReply *reply = p->accessManager->sendCustomRequest(req, method.toUtf8(), parts);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(reply);

    return reqReply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::customMethodForm(const QString &method, const QUrl &url, const QVariantMap &formData, const QVariantMap &headers)
{
    QHttpMultiPart *parts = generateFormData(formData);
    return AsemanNetworkRequestManager::customMethod(method, url, parts, headers);
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::postForm(const QUrl &url, const QVariantMap &formData, const QVariantMap &headers)
{
    QHttpMultiPart *parts = generateFormData(formData);
    return AsemanNetworkRequestManager::post(url, parts, headers);
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::put(const QUrl &url, const QByteArray &data, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    req.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.size()).toUtf8());

    addHeaderData(req, headers);

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, PUT url:" << url.toString() << "data-length:" + data.size();

    QNetworkReply *reply = p->accessManager->put(req, data);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(reply);

    return reqReply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::put(const QUrl &url, QHttpMultiPart *parts, const QVariantMap &headers)
{
    QNetworkRequest req;
    req.setUrl(url);
    req.setMaximumRedirectsAllowed(10);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    addHeaderData(req, headers);

    req.setRawHeader("Content-Type", "multipart/form-data; boundary=\"" + p->boundaryToken.toUtf8() + "\"");

    if (Private::fullLog_env)
        qDebug() << "QtAseman::Network, POST url:" << url.toString() << "data-length: uncalculatble";

    QNetworkReply *reply = p->accessManager->put(req, parts);
    reply->setParent(this);

    AsemanNetworkRequestReply *reqReply = new AsemanNetworkRequestReply(reply);

    return reqReply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::putForm(const QUrl &url, const QVariantMap &formData, const QVariantMap &headers)
{
    QHttpMultiPart *parts = generateFormData(formData);
    return AsemanNetworkRequestManager::put(url, parts, headers);
}

void AsemanNetworkRequestManager::processPostedRequest(AsemanNetworkRequestReply *reply, AsemanNetworkRequestObject *request, std::function<QVariant (QByteArray)> dataConvertMethod)
{
    request->setError(QStringLiteral(""));
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
            const QString filePath = AsemanTools::urlToLocalPath(source);

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

QString AsemanNetworkRequestManager::generateJson(const QVariantMap &map) const
{
    return QString::fromUtf8( QJsonDocument::fromVariant(map).toJson(QJsonDocument::Compact) );
}

QByteArray AsemanNetworkRequestManager::requestData(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    switch (static_cast<qint32>(request->contentType()))
    {
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

AsemanNetworkRequestReply *AsemanNetworkRequestManager::get(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    QVariantMap keys = ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap();
    AsemanNetworkRequestReply *reply = get(request->url(), keys, request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::post(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    AsemanNetworkRequestReply *reply;
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = postForm(request->url(), (ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()), request->headers());
    else
        reply = post(request->url(), requestData(request, ignoreEmptyValues), request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::put(AsemanNetworkRequestObject *request, bool ignoreEmptyValues)
{
    AsemanNetworkRequestReply *reply;
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = putForm(request->url(), (ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()), request->headers());
    else
        reply = put(request->url(), requestData(request, ignoreEmptyValues), request->headers());

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
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = customMethodForm(method, request->url(), (ignoreEmptyValues? removeEmptyValues(request->toMap()) : request->toMap()), request->headers());
    else
        reply = customMethod(method, request->url(), requestData(request, ignoreEmptyValues), request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestManager::~AsemanNetworkRequestManager()
{
    delete p;
}
