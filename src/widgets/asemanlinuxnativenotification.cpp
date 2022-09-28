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

#define DBUS_SERVICE QStringLiteral("org.freedesktop.Notifications")
#define DBUS_PATH    QStringLiteral("/org/freedesktop/Notifications")
#define DBUS_OBJECT  QStringLiteral("org.freedesktop.Notifications")
#define DBUS_CLOSED  QStringLiteral("NotificationClosed")
#define DBUS_ACTION  QStringLiteral("ActionInvoked")
#define DBUS_NOTIFY  QStringLiteral("Notify")
#define DBUS_NCLOSE  QStringLiteral("CloseNotification")

#include "asemanlinuxnativenotification.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QCoreApplication>
#include <QDebug>

class AsemanLinuxNativeNotificationPrivate
{
public:
    QDBusConnection *connection;

    QSet<uint> notifies;
    QColor color;
};

AsemanLinuxNativeNotification::AsemanLinuxNativeNotification(QObject *parent) :
    QObject(parent)
{
    p = new AsemanLinuxNativeNotificationPrivate;

    p->connection = new QDBusConnection( QDBusConnection::sessionBus() );
    p->connection->connect( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_CLOSED , this , SLOT(notificationClosed(QDBusMessage)) );
    p->connection->connect( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_ACTION , this , SLOT(actionInvoked(QDBusMessage))      );
}

void AsemanLinuxNativeNotification::setColor(const QColor &color)
{
    if(p->color == color)
        return;

    p->color = color;
    Q_EMIT colorChanged();
}

QColor AsemanLinuxNativeNotification::color() const
{
    return p->color;
}

uint AsemanLinuxNativeNotification::sendNotify(const QString &title, const QString &body, const QString &icon_path, uint replace_id, int timeOut, const QStringList &actions)
{
    QVariantList args;
    args << QCoreApplication::applicationName();
    args << replace_id;
    args << icon_path;
    args << title;
    args << body;
    args << QVariant::fromValue<QStringList>(actions) ;
    args << QVariant::fromValue<QVariantMap>(QVariantMap());
    args << timeOut;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_NOTIFY );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    uint id_res = res.first().toUInt();
    p->notifies.insert( id_res );
    return id_res;
}

void AsemanLinuxNativeNotification::closeNotification(uint id)
{
    if( !p->notifies.contains(id) )
        return;

    QVariantList args;
    args << id;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_NCLOSE );
    omsg.setArguments( args );

    p->connection->call( omsg , QDBus::NoBlock );
}

void AsemanLinuxNativeNotification::notificationClosed(const QDBusMessage &dmsg)
{
    if( dmsg.type() != QDBusMessage::SignalMessage )
        return ;

    const QVariantList & args = dmsg.arguments();
    if( args.isEmpty() )
        return ;

    uint id = args.at(0).toUInt();
    if( !p->notifies.contains(id) )
        return;

    if( args.count() == 1 )
    {
        Q_EMIT notifyClosed(id);
        p->notifies.remove(id);
        return;
    }

    int type = args.at(1).toInt();
    switch (type) {
    case 1:
        Q_EMIT notifyTimedOut( id );
        break;

    case 2:
    default:
        Q_EMIT notifyClosed( id );
        p->notifies.remove(id);
        break;
    }
}

void AsemanLinuxNativeNotification::actionInvoked(const QDBusMessage &dmsg)
{
    if( dmsg.type() != QDBusMessage::SignalMessage )
        return ;

    const QVariantList & args = dmsg.arguments();
    if( args.count() != 2 )
        return ;

    uint id = args.at(0).toUInt();
    if( !p->notifies.contains(id) )
        return;

    QString action = args.at(1).toString();
    Q_EMIT notifyAction(id, action);
}

AsemanLinuxNativeNotification::~AsemanLinuxNativeNotification()
{
    delete p->connection;
    delete p;
}
