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

#ifndef ASEMANNETWORKREQUESTOBJECT_H
#define ASEMANNETWORKREQUESTOBJECT_H

#include <QObject>
#include <QVariantMap>
#include <QHttpMultiPart>
#include <QUrl>

#include <functional>

#include "asemannetwork_global.h"

class LIBQTASEMAN_NETWORK_EXPORT AsemanNetworkRequestObject : public QObject
{
    Q_OBJECT
    Q_ENUMS(ContentType)

    Q_PROPERTY(QVariant response READ response NOTIFY responseChanged)
    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QVariant cachedData READ cachedData WRITE setCachedData NOTIFY cachedDataChanged)
    Q_PROPERTY(int contentType READ contentType WRITE setContentType NOTIFY contentTypeChanged)
    Q_PROPERTY(qint32 status READ status NOTIFY statusChanged)
    Q_PROPERTY(bool refreshing READ refreshing NOTIFY refreshingChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(QStringList ignoreKeys READ ignoreKeys WRITE setIgnoreKeys NOTIFY ignoreKeysChanged)
    Q_PROPERTY(QString cachePath READ cachePath WRITE setCachePath NOTIFY cachePathChanged)
    Q_PROPERTY(QVariantMap headers READ headers WRITE setHeaders NOTIFY headersChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)

    class Private;
    friend class AsemanNetworkRequestManager;

public:
    enum ContentType {
        TypeJson,
        TypeForm,
        TypeWWWForm,
        TypeNone
    };

    AsemanNetworkRequestObject(QObject *parent = Q_NULLPTR);
    virtual ~AsemanNetworkRequestObject();

    QVariant response() const;

    QVariant data() const;
    void setData(const QVariant &data);

    int contentType() const;
    void setContentType(int contentType);

    QVariant cachedData() const;
    void setCachedData(const QVariant &cachedData);

    void setCachePath(const QString &cachePath);
    QString cachePath() const;

    qint32 status() const;

    bool refreshing() const;
    void setRefreshing(bool refreshing);

    QString error() const;
    void setError(const QString &error);

    void setRefresherMethod(std::function<void ()> refresherMethod);

    QVariantMap headers() const;
    void setHeaders(const QVariantMap &headers);

    QUrl url() const;
    void setUrl(const QUrl &url);

    QStringList ignoreKeys() const;
    void setIgnoreKeys(const QStringList &ignoreKeys);

Q_SIGNALS:
    void responseChanged();
    void cachedDataChanged();
    void contentTypeChanged();
    void statusChanged();
    void refreshingChanged();
    void errorChanged();
    void ignoreKeysChanged();
    void cachePathChanged();
    void headersChanged();
    void urlChanged();
    void dataChanged();
    void successfull(qint32 status);
    void unsuccessfull(qint32 status);
    void clientError(qint32 status);
    void serverError(qint32 status);

public Q_SLOTS:
    QVariantMap toMap() const;
    void fromMap(const QVariantMap &map);

    QString toJson() const;
    void fromJson(const QString &json);

    QString toFormData(bool ignoreEmpty = false) const;
    void fromFormData(const QString &formData);

    QStringList properties() const;

protected:
    void refresh();

private Q_SLOTS:
    void initProperties();

private:
    void tryRefresh();
    void setResult(const QVariant &response, qint32 status);

    void store();
    void restore();

private Q_SLOTS:
    void propertyChanged();

private:
    Private *p;
};

#endif // ASEMANNETWORKREQUESTOBJECT_H
