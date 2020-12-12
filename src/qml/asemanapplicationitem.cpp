/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemanapplicationitem.h"
#include "asemandevices.h"
#include "asemannetworkproxy.h"
#include "asemantools.h"
#include "qtsingleapplication/qtlocalpeer.h"
#ifdef Q_OS_ANDROID
#include "asemanjavalayer.h"
#endif

#include <QDir>
#include <QThread>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QStandardPaths>
#include <QPointer>
#include <QQmlEngine>
#include <QGuiApplication>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#endif
#ifdef Q_OS_IOS
#include "private/quickios/quickios.h"
#endif

static AsemanApplicationItem *aseman_app_singleton = 0;
static QSet<AsemanApplicationItem*> aseman_app_objects;

bool AsemanApplicationItem::aseman_app_inited = AsemanApplicationItem::aseman_app_init();

class AsemanApplicationItemPrivate
{
public:
    QPointer<QQmlEngine> engine;
    QList<QObject*> items;

    static QtLocalPeer *peer;
    QPointer<AsemanNetworkProxy> proxy;

    static qint32 statusBarStyle;
    QTimer *statusbarStyleTimer_ios;
};

QtLocalPeer *AsemanApplicationItemPrivate::peer = 0;
qint32 AsemanApplicationItemPrivate::statusBarStyle = AsemanApplicationItem::StatusBarStyleAuto;


AsemanApplicationItem::AsemanApplicationItem(QQmlEngine *engine) :
    AsemanApplicationItem()
{
    p->engine = engine;
}

AsemanApplicationItem::AsemanApplicationItem() :
    AsemanApplication()
{
    p = new AsemanApplicationItemPrivate;

#ifdef Q_OS_IOS
    p->statusbarStyleTimer_ios = new QTimer(this);
    p->statusbarStyleTimer_ios->setSingleShot(true);
    connect(p->statusbarStyleTimer_ios, &QTimer::timeout, this, [this](){
        if (p->engine)
            return;

        setStatusBarStyle(p->statusBarStyle);
        p->statusbarStyleTimer_ios->start(2000);
    });

    auto app = qobject_cast<QGuiApplication*>(QGuiApplication::instance());
    if (app)
    {
        connect(app, &QGuiApplication::applicationStateChanged, this, [this](Qt::ApplicationState state){
            if (p->engine)
                return;

            switch (static_cast<int>(state))
            {
            case Qt::ApplicationActive:
                p->statusbarStyleTimer_ios->stop();
                p->statusbarStyleTimer_ios->start(10);
                break;
            }
        });
    }
#endif
}

bool AsemanApplicationItem::aseman_app_init()
{
    if(aseman_app_inited)
        return true;

#ifndef FORCE_ASEMAN_DENSITY
#ifdef Q_OS_ANDROID
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    if(!QGuiApplication::testAttribute(Qt::AA_EnableHighDpiScaling) && qgetenv("QT_SCALE_FACTOR").isNull() && qgetenv("ASEMAN_SCALE_FACTOR").isNull())
    {
        qreal ratio = AsemanJavaLayer::instance()->density()*(AsemanDevices::isTablet()? 1.28 : 1);
        qputenv("QT_SCALE_FACTOR",QByteArray::number(ratio));
    }
#endif
#endif
    return true;
}

void AsemanApplicationItem::setApplicationId(const QString &applicationId)
{
    if(AsemanApplicationItemPrivate::peer && AsemanApplicationItemPrivate::peer->applicationId() == applicationId)
        return;
    if(AsemanApplicationItemPrivate::peer)
        delete AsemanApplicationItemPrivate::peer;

    AsemanApplicationItemPrivate::peer = 0;
    if(!applicationId.isEmpty())
    {
        AsemanApplicationItemPrivate::peer = new QtLocalPeer(0, applicationId);
        for(AsemanApplicationItem *app: aseman_app_objects)
            connect(AsemanApplicationItemPrivate::peer, &QtLocalPeer::messageReceived, app, &AsemanApplicationItem::messageReceived);
    }

    for(AsemanApplicationItem *app: aseman_app_objects)
    {
        Q_EMIT app->applicationIdChanged();
        Q_EMIT app->isRunningChanged();
    }
}

QString AsemanApplicationItem::applicationId()
{
    if(AsemanApplicationItemPrivate::peer)
        return AsemanApplicationItemPrivate::peer->applicationId();
    else
        return QString();
}

bool AsemanApplicationItem::isRunning()
{
    if(AsemanApplicationItemPrivate::peer)
        return AsemanApplicationItemPrivate::peer->isClient();

    return false;
}

int AsemanApplicationItem::statusBarStyle()
{
    return p->statusBarStyle;
}

void AsemanApplicationItem::setStatusBarStyle(int statusBarStyle)
{
#ifdef Q_OS_IOS
    QuickIOS::StatusBarStyle style = QuickIOS::StatusBarStyleDefault;
    switch (statusBarStyle)
    {
    case StatusBarStyleLight:
        style = QuickIOS::StatusBarStyleLightContent;
        break;
    case StatusBarStyleDark:
        style = QuickIOS::StatusBarStyleBlackTranslucent;
        break;
    case StatusBarStyleAuto:
        style = QuickIOS::StatusBarStyleDefault;
        break;
    }

    QuickIOS::setStatusBarStyle(style);
#endif

    if (p->statusBarStyle == statusBarStyle)
        return;

    p->statusBarStyle = statusBarStyle;
#ifdef Q_OS_IOS
    switch (statusBarStyle)
    {
    case StatusBarStyleLight:
    case StatusBarStyleDark:
        p->statusbarStyleTimer_ios->stop();
        p->statusbarStyleTimer_ios->start(1);
        break;
    case StatusBarStyleAuto:
        p->statusbarStyleTimer_ios->stop();
        break;
    }
#endif

    Q_EMIT statusBarStyleChanged();
}

void AsemanApplicationItem::sendMessage(const QString &msg)
{
    if(AsemanApplicationItemPrivate::peer)
        AsemanApplicationItemPrivate::peer->sendMessage(msg, 5000);
}

#ifdef QT_QML_LIB
bool AsemanApplicationItem::checkPermissions(const QString &persmission)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)) && defined (Q_OS_ANDROID)
    if (QtAndroid::checkPermission(persmission) == QtAndroid::PermissionResult::Granted)
        return true;
    else
        return false;
#else
    Q_UNUSED(persmission)
    return true;
#endif
}
#endif

#ifdef QT_QML_LIB
QVariantMap AsemanApplicationItem::requestPermissions(QStringList persmissions, QJSValue callback)
{
    QVariantMap _res;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)) && defined (Q_OS_ANDROID)
    auto c_callback = [callback](const QtAndroid::PermissionResultMap &res) -> QVariantMap {
        QVariantMap map;

        QHashIterator<QString, QtAndroid::PermissionResult> i(res);
        while(i.hasNext())
        {
            i.next();
            map[i.key()] = (i.value() == QtAndroid::PermissionResult::Granted);
        }

        return map;
    };

    for(QString pr: persmissions)
        if(QtAndroid::checkPermission(pr) == QtAndroid::PermissionResult::Granted)
        {
            persmissions.removeAll(pr);
            _res[pr] = true;
        }

    if(persmissions.count())
    {
        if(callback.isCallable())
            QtAndroid::requestPermissions(persmissions, [callback, c_callback, _res, this](const QtAndroid::PermissionResultMap &res){
                QVariantMap map = c_callback(res);
                map.unite(_res);

                QJSValue callbackCopy = callback;
                if(p->engine)
                    callbackCopy.call(QJSValueList() << p->engine->toScriptValue<QVariant>(map));
            });
        else
            _res.unite(c_callback( QtAndroid::requestPermissionsSync(persmissions) ));
    }
    else
    {
        if(callback.isCallable())
        {
            if(p->engine)
                callback.call(QJSValueList() << p->engine->toScriptValue<QVariant>(_res));
        }
    }
#else
    QVariantMap map;
    for (const QString &perm: persmissions)
        map[perm] = true;

    QJSValue callbackCopy = callback;
    if(p->engine)
        callbackCopy.call(QJSValueList() << p->engine->toScriptValue<QVariant>(map));
#endif
    return _res;
}
#endif

AsemanNetworkProxy *AsemanApplicationItem::proxy() const
{
    return p->proxy;
}

void AsemanApplicationItem::setProxy(AsemanNetworkProxy *proxy)
{
    if(p->proxy == proxy)
        return;

    if(p->proxy)
        delete p->proxy;

    p->proxy = proxy;
    Q_EMIT proxyChanged();
}

QQmlListProperty<QObject> AsemanApplicationItem::items()
{
    return QQmlListProperty<QObject>(this, &p->items, QQmlListProperty<QObject>::AppendFunction(append),
                                                      QQmlListProperty<QObject>::CountFunction(count),
                                                      QQmlListProperty<QObject>::AtFunction(at),
                                     QQmlListProperty<QObject>::ClearFunction(clear) );
}

QList<QObject *> AsemanApplicationItem::itemsList() const
{
    return p->items;
}

void AsemanApplicationItem::append(QQmlListProperty<QObject> *p, QObject *v)
{
    AsemanApplicationItem *aobj = static_cast<AsemanApplicationItem*>(p->object);
    aobj->p->items.append(v);
    Q_EMIT aobj->itemsChanged();
}

int AsemanApplicationItem::count(QQmlListProperty<QObject> *p)
{
    AsemanApplicationItem *aobj = static_cast<AsemanApplicationItem*>(p->object);
    return aobj->p->items.count();
}

QObject *AsemanApplicationItem::at(QQmlListProperty<QObject> *p, int idx)
{
    AsemanApplicationItem *aobj = static_cast<AsemanApplicationItem*>(p->object);
    return aobj->p->items.at(idx);
}

void AsemanApplicationItem::clear(QQmlListProperty<QObject> *p)
{
    AsemanApplicationItem *aobj = static_cast<AsemanApplicationItem*>(p->object);
    aobj->p->items.clear();
    Q_EMIT aobj->itemsChanged();
}

AsemanApplicationItem::~AsemanApplicationItem()
{
    aseman_app_objects.remove(this);
    if(aseman_app_singleton == this)
    {
        if(AsemanApplicationItemPrivate::peer)
        {
            delete AsemanApplicationItemPrivate::peer;
            AsemanApplicationItemPrivate::peer = 0;
        }
        aseman_app_singleton = 0;
    }

    delete p;
}
