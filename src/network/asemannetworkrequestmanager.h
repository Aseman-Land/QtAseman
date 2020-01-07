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

#ifndef ASEMANNETWORKREQUESTMANAGER_H
#define ASEMANNETWORKREQUESTMANAGER_H

#include <QNetworkRequest>
#include <QObject>
#include <QUrlQuery>
#include <QVariantMap>
#include <QHttpMultiPart>

#include "asemannetworkrequestobject.h"
#include "asemannetworkrequestreply.h"

#include <functional>

#include "asemannetwork_global.h"

class LIBQTASEMAN_NETWORK_EXPORT AsemanNetworkRequestManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString boundaryToken READ boundaryToken WRITE setBoundaryToken NOTIFY boundaryTokenChanged)
    class Private;

public:
    AsemanNetworkRequestManager(QObject *parent = Q_NULLPTR);
    virtual ~AsemanNetworkRequestManager();

    static QVariantMap removeEmptyValues(const QVariantMap &data);

    void setBoundaryToken(const QString &boundaryToken);
    QString boundaryToken() const;

Q_SIGNALS:
    void boundaryTokenChanged();

public Q_SLOTS:
    AsemanNetworkRequestReply *get(AsemanNetworkRequestObject *request, bool ignoreEmptyValues = true);
    AsemanNetworkRequestReply *post(AsemanNetworkRequestObject *request);
    AsemanNetworkRequestReply *put(AsemanNetworkRequestObject *request);
    AsemanNetworkRequestReply *patch(AsemanNetworkRequestObject *request);
    AsemanNetworkRequestReply *deleteMethod(AsemanNetworkRequestObject *request);
    AsemanNetworkRequestReply *customMethod(const QString &method, AsemanNetworkRequestObject *request);

protected:
    virtual AsemanNetworkRequestReply *get(const QUrl &apiUrl, const QVariantMap &keys = QVariantMap(), const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *post(const QUrl &apiUrl, const QByteArray &data, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *post(const QUrl &apiUrl, QHttpMultiPart *parts, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *postForm(const QUrl &apiUrl, const QVariantMap &formData, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *put(const QUrl &apiUrl, const QByteArray &data, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *put(const QUrl &apiUrl, QHttpMultiPart *parts, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *putForm(const QUrl &apiUrl, const QVariantMap &formData, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *customMethod(const QString &method, const QUrl &apiUrl, const QByteArray &data, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *customMethod(const QString &method, const QUrl &apiUrl, QHttpMultiPart *parts, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *customMethodForm(const QString &method, const QUrl &apiUrl, const QVariantMap &formData, const QVariantMap &headers = QVariantMap());
    virtual void processPostedRequest(AsemanNetworkRequestReply *reply, AsemanNetworkRequestObject *request, std::function<QVariant (QByteArray)> dataConvertMethod = Q_NULLPTR);

private:
    QUrlQuery queryOfMap(const QVariantMap &keys) const;
    QByteArray variantToData(const QVariant &var) const;
    QVariant processData(AsemanNetworkRequestReply *reply, const QByteArray &data) const;
    void addHeaderData(QNetworkRequest &request, const QVariantMap &headers);

    QHttpMultiPart *generateFormData(const QVariantMap &map);
    QString generateWWWFormData(const QVariantMap &map, bool ignoreEmpty = false) const;
    QString generateJson(const QVariantMap &map) const;
    QByteArray requestData(AsemanNetworkRequestObject *request);

private:
    Private *p;
};

typedef AsemanNetworkRequestManager QAsemanNetworkRequestManager;

#endif // ASEMANNETWORKREQUESTMANAGER_H
