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

#include "asemanmacnativenotification.h"

#include <QSystemTrayIcon>
#include <QTimer>
#include <QMenu>
#include <QHash>

class AsemanMacNativeNotificationItem: public QSystemTrayIcon
{
public:
    AsemanMacNativeNotificationItem(QObject *parent): QSystemTrayIcon(parent){
        setContextMenu(new QMenu());
        show();
    }
    virtual ~AsemanMacNativeNotificationItem(){}

    QStringList actions;
    QString icon;
};

class AsemanMacNativeNotificationPrivate
{
public:
    QStringList last_actions;

    QHash<uint, AsemanMacNativeNotificationItem*> items;
    uint last_id;
    QColor color;
};

AsemanMacNativeNotification::AsemanMacNativeNotification(QObject *parent) :
    QObject(parent)
{
    p = new AsemanMacNativeNotificationPrivate;
    p->last_id = 1000;

}

void AsemanMacNativeNotification::setColor(const QColor &color)
{
    if(p->color == color)
        return;

    p->color = color;
    Q_EMIT colorChanged();
}

QColor AsemanMacNativeNotification::color() const
{
    return p->color;
}

uint AsemanMacNativeNotification::sendNotify(const QString &title, const QString &body, const QString &icon, uint replace_id, int timeOut, const QStringList &actions)
{
    uint result = replace_id;

    AsemanMacNativeNotificationItem *item = p->items.value(replace_id);
    if(!item)
    {
        item = new AsemanMacNativeNotificationItem(this);

        p->items.insert(p->last_id, item);

        result = p->last_id;
        p->last_id++;

        connect(item, &AsemanMacNativeNotificationItem::messageClicked,
                this, &AsemanMacNativeNotification::messageClicked, Qt::QueuedConnection );
        connect(item, &AsemanMacNativeNotificationItem::destroyed,
                this, &AsemanMacNativeNotification::messageDestroyed, Qt::QueuedConnection );
    }

    item->showMessage(title, body, QSystemTrayIcon::Information, timeOut);
    item->actions = actions;
    item->icon = icon;

    if(timeOut)
        QTimer::singleShot(timeOut+500, item, SLOT(deleteLater()));

    return result;
}

void AsemanMacNativeNotification::closeNotification(uint id)
{
    AsemanMacNativeNotificationItem *item = p->items.value(id);
    if(!item)
        return;

    item->deleteLater();
    p->items.remove(id);
}

void AsemanMacNativeNotification::messageClicked()
{
    AsemanMacNativeNotificationItem *item = static_cast<AsemanMacNativeNotificationItem*>(sender());
    if(!item)
        return;

    const uint id = p->items.key(item);
    if(!id)
        return;

    const QStringList & actions = item->actions;
    if(!actions.isEmpty())
        Q_EMIT notifyAction(id, actions.first());

    item->deleteLater();
}

void AsemanMacNativeNotification::messageDestroyed()
{
    AsemanMacNativeNotificationItem *item = static_cast<AsemanMacNativeNotificationItem*>(sender());
    if(!item)
        return;

    const uint id = p->items.key(item);
    if(!id)
        return;

    p->items.remove(id);
}

AsemanMacNativeNotification::~AsemanMacNativeNotification()
{
    delete p;
}
