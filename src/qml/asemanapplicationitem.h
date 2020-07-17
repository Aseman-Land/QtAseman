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

#ifndef ASEMANAPPLICATIONITEM_H
#define ASEMANAPPLICATIONITEM_H

#include "aseman_macros.h"
#include "asemanquickobject.h"
#include "asemanapplication.h"

#include <QVariant>
#include <QCoreApplication>
#include <QUrl>
#include <QJSValue>
#include <QQmlEngine>
#include <QQmlListProperty>

#include "asemantools_global.h"

class AsemanNetworkProxy;
class AsemanApplicationItemPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanApplicationItem : public AsemanApplication
{
    Q_OBJECT
    Q_PROPERTY(AsemanNetworkProxy* proxy READ proxy WRITE setProxy NOTIFY proxyChanged)
    Q_PROPERTY(QString applicationId READ applicationId WRITE setApplicationId NOTIFY applicationIdChanged)
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(int statusBarStyle READ statusBarStyle WRITE setStatusBarStyle NOTIFY statusBarStyleChanged)

    Q_PROPERTY(QQmlListProperty<QObject> items READ items NOTIFY itemsChanged)
    Q_CLASSINFO("DefaultProperty", "items")

    Q_ENUMS(StatusBarStyles)

public:
    enum StatusBarStyles {
        StatusBarStyleLight,
        StatusBarStyleDark,
        StatusBarStyleAuto
    };

    AsemanApplicationItem(QQmlEngine *engine);
    AsemanApplicationItem();
    virtual ~AsemanApplicationItem();

    static void setApplicationId(const QString &applicationId);
    static QString applicationId();

    static bool isRunning();

    AsemanNetworkProxy *proxy() const;
    void setProxy(AsemanNetworkProxy *proxy);

    QQmlListProperty<QObject> items();
    QList<QObject*> itemsList() const;

    int statusBarStyle();
    void setStatusBarStyle(int statusBarStyle);

public Q_SLOTS:
    void sendMessage(const QString &msg);

    bool checkPermissions(const QString &persmission);
    QVariantMap requestPermissions(QStringList persmissions, QJSValue callback);

Q_SIGNALS:
    void proxyChanged();
    void applicationIdChanged();
    void isRunningChanged();
    void messageReceived(const QString &msg);
    void itemsChanged();
    void statusBarStyleChanged();

private:
    static void append(QQmlListProperty<QObject> *p, QObject *v);
    static int count(QQmlListProperty<QObject> *p);
    static QObject *at(QQmlListProperty<QObject> *p, int idx);
    static void clear(QQmlListProperty<QObject> *p);

private:
    static bool aseman_app_inited;
    static bool aseman_app_init();

private:
    AsemanApplicationItemPrivate *p;
};

typedef AsemanApplicationItem QAsemanApplicationItem;

#endif // ASEMANAPPLICATIONITEM_H
