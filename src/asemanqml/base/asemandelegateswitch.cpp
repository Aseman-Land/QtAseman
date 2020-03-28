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

#include "asemandelegateswitch.h"

#include <QPointer>

class AsemanDelegateSwitch::Private
{
public:
    QList<QQmlComponent*> components;
    qint32 current = -1;
    QPointer<QQuickItem> item;
};

AsemanDelegateSwitch::AsemanDelegateSwitch(QQuickItem *parent) :
    QQuickItem(parent)
{
    p = new Private;
    connect(this, &AsemanDelegateSwitch::componentsChanged, this, &AsemanDelegateSwitch::refresh);
}

QQmlListProperty<QQmlComponent> AsemanDelegateSwitch::components()
{
    return QQmlListProperty<QQmlComponent>(this, &p->components, QQmlListProperty<QQmlComponent>::AppendFunction(append),
                                                QQmlListProperty<QQmlComponent>::CountFunction(count),
                                                QQmlListProperty<QQmlComponent>::AtFunction(at),
                                                QQmlListProperty<QQmlComponent>::ClearFunction(clear) );
}

QList<QQmlComponent *> AsemanDelegateSwitch::componentsList() const
{
    return p->components;
}

void AsemanDelegateSwitch::setCurrent(qint32 current)
{
    if (p->current == current)
        return;

    p->current = current;
    refresh();
    Q_EMIT currentChanged();
}

qint32 AsemanDelegateSwitch::current() const
{
    return p->current;
}

QQuickItem *AsemanDelegateSwitch::item() const
{
    return p->item;
}

void AsemanDelegateSwitch::append(QQmlListProperty<QQmlComponent> *p, QQmlComponent *v)
{
    AsemanDelegateSwitch *aobj = static_cast<AsemanDelegateSwitch*>(p->object);
    aobj->p->components.append(v);
    Q_EMIT aobj->componentsChanged();
}

int AsemanDelegateSwitch::count(QQmlListProperty<QQmlComponent> *p)
{
    AsemanDelegateSwitch *aobj = static_cast<AsemanDelegateSwitch*>(p->object);
    return aobj->p->components.count();
}

QQmlComponent *AsemanDelegateSwitch::at(QQmlListProperty<QQmlComponent> *p, int idx)
{
    AsemanDelegateSwitch *aobj = static_cast<AsemanDelegateSwitch*>(p->object);
    return aobj->p->components.at(idx);
}

void AsemanDelegateSwitch::clear(QQmlListProperty<QQmlComponent> *p)
{
    AsemanDelegateSwitch *aobj = static_cast<AsemanDelegateSwitch*>(p->object);
    aobj->p->components.clear();
    Q_EMIT aobj->componentsChanged();
}

void AsemanDelegateSwitch::refresh()
{
    if (p->item)
    {
        p->item->deleteLater();
        p->item = Q_NULLPTR;
    }
    if (p->current < 0 || p->components.isEmpty() || p->current >= p->components.count())
    {
        Q_EMIT itemChanged();
        return;
    }

    QQmlComponent *component = p->components.at(p->current);
    QQmlContext *context = qmlContext(this);
    QObject *object = component->create(context);
    if(!object)
        return;

    QQuickItem *objectItem = qobject_cast<QQuickItem*>(object);
    if (!objectItem)
    {
        object->deleteLater();
        return;
    }

    object->setParent(this);
    objectItem->setParentItem(this);
    p->item = objectItem;

    connect(p->item, &QQuickItem::widthChanged, this, &AsemanDelegateSwitch::refreshWidth);
    connect(p->item, &QQuickItem::heightChanged, this, &AsemanDelegateSwitch::refreshHeight);

    refreshWidth();
    refreshHeight();

    Q_EMIT itemChanged();
}

void AsemanDelegateSwitch::refreshWidth()
{
    if (!p->item)
        resetWidth();
    else
        setWidth(p->item->width());
}

void AsemanDelegateSwitch::refreshHeight()
{
    if (!p->item)
        resetHeight();
    else
        setHeight(p->item->height());
}

AsemanDelegateSwitch::~AsemanDelegateSwitch()
{
    delete p;
}
