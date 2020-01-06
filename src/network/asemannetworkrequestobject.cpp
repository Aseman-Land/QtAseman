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

#include "asemannetworkrequestobject.h"
#include "asemannetworkrequestmanager.h"

#include <QJsonDocument>
#include <QMetaProperty>
#include <QTimer>
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QDir>

class AsemanNetworkRequestObject::Private
{
public:
    QVariant cachedData;
    QVariant response;
    QVariant data;
    qint32 status;
    qint32 contentType;
    bool refreshing;
    QString error;
    QStringList ignoreKeys;
    QVariantMap headers;
    QUrl url;

    std::function<void ()> refresherMethod_cpp;
    QTimer *refreshTimer;
    QString cachePath;

    bool storeLock;

    QHash<QByteArray, QByteArray> signalsProperties;
};

AsemanNetworkRequestObject::AsemanNetworkRequestObject(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->status = -1;
    p->refreshing = false;
    p->storeLock = false;
    p->refresherMethod_cpp = Q_NULLPTR;
    p->contentType = TypeForm;

    p->refreshTimer = new QTimer(this);
    p->refreshTimer->setInterval(100);
    p->refreshTimer->setSingleShot(true);

    connect(this, &AsemanNetworkRequestObject::headersChanged, this, &AsemanNetworkRequestObject::refresh);
    connect(p->refreshTimer, &QTimer::timeout, this, &AsemanNetworkRequestObject::tryRefresh);

    QMetaObject::invokeMethod(this, "initProperties", Qt::QueuedConnection);
}

QVariant AsemanNetworkRequestObject::response() const
{
    return p->response;
}

QVariant AsemanNetworkRequestObject::data() const
{
    return p->data;
}

void AsemanNetworkRequestObject::setData(const QVariant &data)
{
    if (p->data == data)
        return;

    p->data = data;
    Q_EMIT dataChanged();
}

int AsemanNetworkRequestObject::contentType() const
{
    return p->contentType;
}

void AsemanNetworkRequestObject::setContentType(int contentType)
{
    if (p->contentType == contentType)
        return;

    p->contentType = contentType;
    Q_EMIT contentTypeChanged();
}

QVariant AsemanNetworkRequestObject::cachedData() const
{
    return p->cachedData;
}

void AsemanNetworkRequestObject::setCachedData(const QVariant &cachedData)
{
    if (p->cachedData == cachedData)
        return;

    p->cachedData = cachedData;
    store();
    Q_EMIT cachedDataChanged();
}

void AsemanNetworkRequestObject::setCachePath(const QString &cachePath)
{
    if (p->cachePath == cachePath)
        return;

    p->cachePath = cachePath;
    restore();
    Q_EMIT cachePathChanged();
}

QString AsemanNetworkRequestObject::cachePath() const
{
    return p->cachePath;
}

qint32 AsemanNetworkRequestObject::status() const
{
    return p->status;
}

void AsemanNetworkRequestObject::setResult(const QVariant &response, qint32 status)
{
    p->response = response;
    p->status = status;

    qint32 code = p->status/100;
    switch (code)
    {
    case 2:
        Q_EMIT successfull(status);
        break;
    case 4:
        Q_EMIT clientError(status);
        Q_EMIT unsuccessfull(status);
        break;
    case 5:
        Q_EMIT serverError(status);
        Q_EMIT unsuccessfull(status);
        break;
    }

    Q_EMIT statusChanged();
    Q_EMIT responseChanged();
}

bool AsemanNetworkRequestObject::refreshing() const
{
    return p->refreshing;
}

void AsemanNetworkRequestObject::setRefreshing(bool refreshing)
{
    if (p->refreshing == refreshing)
        return;

    p->refreshing = refreshing;
    Q_EMIT refreshingChanged();
}

QString AsemanNetworkRequestObject::error() const
{
    return p->error;
}

void AsemanNetworkRequestObject::setError(const QString &error)
{
    if (p->error == error)
        return;

    p->error = error;
    Q_EMIT errorChanged();
}

void AsemanNetworkRequestObject::setRefresherMethod(std::function<void ()> refresherMethod)
{
    p->refresherMethod_cpp = refresherMethod;
}

QVariantMap AsemanNetworkRequestObject::headers() const
{
    return p->headers;
}

void AsemanNetworkRequestObject::setHeaders(const QVariantMap &headers)
{
    if (p->headers == headers)
        return;

    p->headers = headers;
    Q_EMIT headersChanged();
}

QUrl AsemanNetworkRequestObject::url() const
{
    return p->url;
}

void AsemanNetworkRequestObject::setUrl(const QUrl &url)
{
    if (p->url == url)
        return;

    p->url = url;
    Q_EMIT urlChanged();
}

QStringList AsemanNetworkRequestObject::ignoreKeys() const
{
    return p->ignoreKeys;
}

void AsemanNetworkRequestObject::setIgnoreKeys(const QStringList &ignoreKeys)
{
    if (p->ignoreKeys == ignoreKeys)
        return;

    p->ignoreKeys = ignoreKeys;
    Q_EMIT ignoreKeysChanged();
}

QVariantMap AsemanNetworkRequestObject:: toMap() const
{
    QVariantMap res;
    const QStringList &properties = AsemanNetworkRequestObject::properties();
    for (const QString &pr: properties)
        if (!p->ignoreKeys.contains(pr))
            res[pr] = property(pr.toUtf8());
    return res;
}

void AsemanNetworkRequestObject::fromMap(const QVariantMap &map)
{
    const QStringList &properties = AsemanNetworkRequestObject::properties();
    for (const QString &pr: properties)
        if (!p->ignoreKeys.contains(pr) && map.contains(pr))
            setProperty(pr.toUtf8(), map.value(pr));
}

QString AsemanNetworkRequestObject::toJson() const
{
    return QJsonDocument::fromVariant(toMap()).toJson();
}

void AsemanNetworkRequestObject::fromJson(const QString &json)
{
    fromMap( QJsonDocument::fromJson(json.toUtf8()).toVariant().toMap() );
}

QString AsemanNetworkRequestObject::toFormData(bool ignoreEmpty) const
{
    QString res;
    const QStringList &properties = AsemanNetworkRequestObject::properties();
    for (const QString &pr: properties)
    {
        if (p->ignoreKeys.contains(pr))
            continue;
        QVariant var = property(pr.toUtf8());
        if (var.type() != QVariant::String)
            var.convert(QVariant::String);
        if (ignoreEmpty && var.toString().isEmpty())
            continue;

        if (res.count())
            res += QStringLiteral("\n");

        res += pr + QStringLiteral("=") + var.toString().toUtf8().toPercentEncoding();
    }
    return res;
}

void AsemanNetworkRequestObject::fromFormData(const QString &formData)
{
    QVariantMap map;
    QStringList lines = formData.split(QStringLiteral("\n"), QString::SkipEmptyParts);
    for (const QString &l: lines)
    {
        qint32 idx = l.indexOf(QStringLiteral("="));
        if (idx == -1)
            continue;

        QString key = l.left(idx);
        if (p->ignoreKeys.contains(key))
            continue;

        QString val = QByteArray::fromPercentEncoding(l.mid(idx+1).toUtf8());

        map[key] = val;
    }

    fromMap(map);
}

QStringList AsemanNetworkRequestObject::properties() const
{
    QStringList res;

    const QMetaObject *meta = metaObject();
    const QMetaObject *thisMeta = &AsemanNetworkRequestObject::staticMetaObject;
    for (int i=thisMeta->propertyCount(); i<meta->propertyCount(); i++)
    {
        QMetaProperty property = meta->property(i);
        const QByteArray &propertyName = property.name();
        res << QString::fromUtf8(propertyName);
    }

    return res;
}

void AsemanNetworkRequestObject::refresh()
{
    p->refreshTimer->stop();
    if (!p->refresherMethod_cpp)
        return;

    p->refreshTimer->start();
}

void AsemanNetworkRequestObject::tryRefresh()
{
    if (p->refresherMethod_cpp)
        p->refresherMethod_cpp();
}

void AsemanNetworkRequestObject::initProperties()
{
    AsemanNetworkRequestObject::properties();
    const QMetaObject *meta = metaObject();
    const QMetaObject *thisMeta = &AsemanNetworkRequestObject::staticMetaObject;
    for (int i=thisMeta->propertyCount(); i<meta->propertyCount(); i++)
    {
        QMetaProperty property = meta->property(i);
        const QByteArray &propertyName = property.name();
        const QByteArray &signalSign = property.notifySignal().methodSignature();
        p->signalsProperties[signalSign] = propertyName;
        connect(this, QByteArray(QByteArray::number(QSIGNAL_CODE)+signalSign),
                this, SLOT(propertyChanged()));
    }
}

void AsemanNetworkRequestObject::store()
{
    if (p->cachePath.isEmpty() || p->storeLock)
        return;

    QFileInfo inf(p->cachePath);
    QString root = inf.dir().path();
    QDir().mkpath(root);

    QFile file(p->cachePath);
    if (!file.open(QFile::WriteOnly))
        return;

    QDataStream stream(&file);
    stream << p->cachedData;

    file.close();
}

void AsemanNetworkRequestObject::restore()
{
    if (p->cachePath.isEmpty())
        return;

    QFileInfo inf(p->cachePath);
    QString root = inf.dir().path();
    QDir().mkpath(root);

    QFile file(p->cachePath);
    if (!file.open(QFile::ReadOnly))
        return;

    QVariant data;

    QDataStream stream(&file);
    stream >> data;

    file.close();

    p->storeLock = true;
    setCachedData(data);
    p->storeLock = false;
}

void AsemanNetworkRequestObject::propertyChanged()
{
    if(sender() != this)
        return;

    const int signalIndex = senderSignalIndex();
    if(signalIndex == -1)
        return;

    QMetaMethod signalObj = metaObject()->method(signalIndex);
    const QByteArray &propertyName = p->signalsProperties.value(signalObj.methodSignature());
    const QVariant &value = property(propertyName);

    Q_UNUSED(value)
    refresh();
}

AsemanNetworkRequestObject::~AsemanNetworkRequestObject()
{
    delete p;
}
