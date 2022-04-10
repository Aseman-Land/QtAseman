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

#include "asemannativenotification.h"
#include "asemannativenotificationitem.h"

#include <QHash>

class AsemanNativeNotificationPrivate
{
public:
    QHash<uint, AsemanNativeNotificationItem*> items;
    uint last_id;

    QColor color;
};

AsemanNativeNotification::AsemanNativeNotification(QObject *parent) :
    QObject(parent)
{
    p = new AsemanNativeNotificationPrivate;
    p->last_id = 1000;
}

void AsemanNativeNotification::setColor(const QColor &color)
{
    if(p->color == color)
        return;

    p->color = color;
    Q_EMIT colorChanged();
}

QColor AsemanNativeNotification::color() const
{
    return p->color;
}

uint AsemanNativeNotification::sendNotify(const QString &title, const QString &body, const QString &icon, uint replace_id, int timeOut, const QStringList &actions)
{
    uint result = replace_id;

    AsemanNativeNotificationItem *item = p->items.value(replace_id);
    if(!item)
    {
        item = new AsemanNativeNotificationItem();
        item->setFixedWidth(400);
        item->setColor(p->color);

        p->items.insert(p->last_id, item);

        result = p->last_id;
        p->last_id++;

        connect(item, &AsemanNativeNotificationItem::destroyed, this, &AsemanNativeNotification::itemClosed);
        connect(item, &AsemanNativeNotificationItem::actionTriggered, this, &AsemanNativeNotification::actionTriggered);
    }

    item->setTitle(title);
    item->setBody(body);
    item->setIcon(icon);
    item->setActions(actions);
    item->setTimeOut(timeOut);
    item->show();

    return result;
}

void AsemanNativeNotification::closeNotification(uint id)
{
    AsemanNativeNotificationItem *item = p->items.value(id);
    if(!id)
        return;

    item->close();
}

void AsemanNativeNotification::itemClosed()
{
    AsemanNativeNotificationItem *item = static_cast<AsemanNativeNotificationItem*>(sender());
    if(!item)
        return;

    uint id = p->items.key(item);
    if(!id)
        return;

    p->items.remove(id);
    Q_EMIT notifyClosed(id);
}

void AsemanNativeNotification::actionTriggered(const QString &action)
{
    AsemanNativeNotificationItem *item = static_cast<AsemanNativeNotificationItem*>(sender());
    if(!item)
        return;

    uint id = p->items.key(item);
    if(!id)
        return;

    Q_EMIT notifyAction(id, action);
    item->close();
}

AsemanNativeNotification::~AsemanNativeNotification()
{
    delete p;
}
