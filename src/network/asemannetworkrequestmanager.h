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

#include "asemannetworkrequestobject.h"
#include "asemannetworkrequestreply.h"

#include <functional>

#include "asemannetwork_global.h"

#if QT_CONFIG(http)
class QHttpMultiPart;
#endif

class LIBQTASEMAN_NETWORK_EXPORT AsemanNetworkRequestManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString boundaryToken READ boundaryToken WRITE setBoundaryToken NOTIFY boundaryTokenChanged)
    Q_PROPERTY(bool ignoreSslErrors READ ignoreSslErrors WRITE setIgnoreSslErrors NOTIFY ignoreSslErrorsChanged)
    class Private;

public:
    AsemanNetworkRequestManager(QObject *parent = Q_NULLPTR);
    virtual ~AsemanNetworkRequestManager();

    static QVariantMap removeEmptyValues(const QVariantMap &data);

    void setBoundaryToken(const QString &boundaryToken);
    QString boundaryToken() const;

    void setIgnoreSslErrors(bool ignoreSslErrors);
    bool ignoreSslErrors() const;

Q_SIGNALS:
    void boundaryTokenChanged();
    void ignoreSslErrorsChanged();

public Q_SLOTS:
    AsemanNetworkRequestReply *get(AsemanNetworkRequestObject *request, bool ignoreEmptyValues = true);
    AsemanNetworkRequestReply *post(AsemanNetworkRequestObject *request, bool ignoreEmptyValues = true);
    AsemanNetworkRequestReply *put(AsemanNetworkRequestObject *request, bool ignoreEmptyValues = true);
    AsemanNetworkRequestReply *patch(AsemanNetworkRequestObject *request, bool ignoreEmptyValues = true);
    AsemanNetworkRequestReply *deleteMethod(AsemanNetworkRequestObject *request, bool ignoreEmptyValues = true);
    AsemanNetworkRequestReply *customMethod(const QString &method, AsemanNetworkRequestObject *request, bool ignoreEmptyValues = true);

protected:
    virtual AsemanNetworkRequestReply *get(AsemanNetworkRequestObject *request, const QUrl &apiUrl, const QVariantMap &keys = QVariantMap(), const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *post(AsemanNetworkRequestObject *request, const QUrl &apiUrl, const QByteArray &data, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *put(AsemanNetworkRequestObject *request, const QUrl &apiUrl, const QByteArray &data, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *customMethod(AsemanNetworkRequestObject *request, const QString &method, const QUrl &apiUrl, const QByteArray &data, const QVariantMap &headers = QVariantMap());
    virtual void processPostedRequest(AsemanNetworkRequestReply *reply, AsemanNetworkRequestObject *request, std::function<QVariant (QByteArray)> dataConvertMethod = Q_NULLPTR);

#if QT_CONFIG(http)
    virtual AsemanNetworkRequestReply *postForm(AsemanNetworkRequestObject *request, const QUrl &apiUrl, const QVariantMap &formData, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *putForm(AsemanNetworkRequestObject *request, const QUrl &apiUrl, const QVariantMap &formData, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *customMethodForm(AsemanNetworkRequestObject *request, const QString &method, const QUrl &apiUrl, const QVariantMap &formData, const QVariantMap &headers = QVariantMap());

    virtual AsemanNetworkRequestReply *post(AsemanNetworkRequestObject *request, const QUrl &apiUrl, QHttpMultiPart *parts, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *put(AsemanNetworkRequestObject *request, const QUrl &apiUrl, QHttpMultiPart *parts, const QVariantMap &headers = QVariantMap());
    virtual AsemanNetworkRequestReply *customMethod(AsemanNetworkRequestObject *request, const QString &method, const QUrl &apiUrl, QHttpMultiPart *parts, const QVariantMap &headers = QVariantMap());
#endif

private:
    QUrlQuery queryOfMap(const QVariantMap &keys) const;
    QByteArray variantToData(const QVariant &var) const;
    QVariant processData(AsemanNetworkRequestReply *reply, const QByteArray &data) const;
    void addHeaderData(QNetworkRequest &request, const QVariantMap &headers);

#if QT_CONFIG(http)
    QHttpMultiPart *generateFormData(const QVariantMap &map);
#endif

    QString generateWWWFormData(const QVariantMap &map, bool ignoreEmpty = false) const;
    QString generateJson(const QVariantMap &map) const;
    QByteArray requestData(AsemanNetworkRequestObject *request, bool ignoreEmptyValues);

private:
    Private *p;
};

typedef AsemanNetworkRequestManager QAsemanNetworkRequestManager;

#endif // ASEMANNETWORKREQUESTMANAGER_H
