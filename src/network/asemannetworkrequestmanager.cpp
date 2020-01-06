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

class AsemanNetworkRequestManager::Private
{
public:
    QNetworkAccessManager *accessManager;
    QString boundaryToken;
};

AsemanNetworkRequestManager::AsemanNetworkRequestManager(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->boundaryToken = "Aseman:292a15d1-64af-4ee2-82b5-2d42adb9fd43";

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
    request->setError("");
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
    if (reply->headers().value("content-type").toString().contains("application/json"))
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
        if (var.type() != QVariant::String)
            var.convert(QVariant::String);

        QHttpPart part;
        part.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant("form-data; name=\"" + i.key().toUtf8() + "\""));
        part.setBody(i.value().toString().toUtf8());

        parts->append(part);
    }

    return parts;
}

QString AsemanNetworkRequestManager::generateWWWFormData(const QVariantMap &map, bool ignoreEmpty) const
{
    QString res;
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext())
    {
        i.next();
        QVariant var = i.value();
        if (var.type() != QVariant::String)
            var.convert(QVariant::String);
        if (ignoreEmpty && var.toString().isEmpty())
            continue;

        if (res.count())
            res += "\n";

        res += i.value().toString() + "=" + var.toString().toUtf8().toPercentEncoding();
    }
    return res;
}

QString AsemanNetworkRequestManager::generateJson(const QVariantMap &map) const
{
    return QJsonDocument::fromVariant(map).toJson(QJsonDocument::Compact);
}

QByteArray AsemanNetworkRequestManager::requestData(AsemanNetworkRequestObject *request)
{
    switch (static_cast<qint32>(request->contentType()))
    {
    case AsemanNetworkRequestObject::TypeWWWForm:
        return generateWWWFormData(request->toMap()).toUtf8();
    case AsemanNetworkRequestObject::TypeJson:
        return generateJson(request->toMap()).toUtf8();
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

AsemanNetworkRequestReply *AsemanNetworkRequestManager::post(AsemanNetworkRequestObject *request)
{
    AsemanNetworkRequestReply *reply;
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = postForm(request->url(), request->toMap(), request->headers());
    else
        reply = post(request->url(), requestData(request), request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::put(AsemanNetworkRequestObject *request)
{
    AsemanNetworkRequestReply *reply;
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = putForm(request->url(), request->toMap(), request->headers());
    else
        reply = put(request->url(), requestData(request), request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::patch(AsemanNetworkRequestObject *request)
{
    return customMethod("PATCH", request);
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::deleteMethod(AsemanNetworkRequestObject *request)
{
    return customMethod("DELETE", request);
}

AsemanNetworkRequestReply *AsemanNetworkRequestManager::customMethod(const QString &method, AsemanNetworkRequestObject *request)
{
    AsemanNetworkRequestReply *reply;
    if (request->contentType() == AsemanNetworkRequestObject::TypeForm)
        reply = customMethodForm(method, request->url(), request->toMap(), request->headers());
    else
        reply = customMethod(method, request->url(), requestData(request), request->headers());

    processPostedRequest(reply, request, [this, reply](const QByteArray &data) -> QVariant { return processData(reply, data); });
    return reply;
}

AsemanNetworkRequestManager::~AsemanNetworkRequestManager()
{
    delete p;
}
