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

#include "asemannetworkquickobject.h"

#include <QSet>

QSet<AsemanNetworkQuickObject*> aseman_network_quick_objs;

class AsemanNetworkQuickObjectPrivate
{
public:
    QList<QObject*> items;
};

AsemanNetworkQuickObject::AsemanNetworkQuickObject(QObject *parent) :
    QObject(parent)
{
    p = new AsemanNetworkQuickObjectPrivate;
    aseman_network_quick_objs.insert(this);
}

QQmlListProperty<QObject> AsemanNetworkQuickObject::items()
{
    return QQmlListProperty<QObject>(this, &p->items, QQmlListProperty<QObject>::AppendFunction(append),
                                                      QQmlListProperty<QObject>::CountFunction(count),
                                                      QQmlListProperty<QObject>::AtFunction(at),
                                     QQmlListProperty<QObject>::ClearFunction(clear) );
}

QList<QObject *> AsemanNetworkQuickObject::itemsList() const
{
    return p->items;
}

bool AsemanNetworkQuickObject::isValid(AsemanNetworkQuickObject *obj)
{
    return aseman_network_quick_objs.contains(obj);
}

void AsemanNetworkQuickObject::append(QQmlListProperty<QObject> *p, QObject *v)
{
    AsemanNetworkQuickObject *aobj = static_cast<AsemanNetworkQuickObject*>(p->object);
    aobj->p->items.append(v);
    Q_EMIT aobj->itemsChanged();
}

int AsemanNetworkQuickObject::count(QQmlListProperty<QObject> *p)
{
    AsemanNetworkQuickObject *aobj = static_cast<AsemanNetworkQuickObject*>(p->object);
    return aobj->p->items.count();
}

QObject *AsemanNetworkQuickObject::at(QQmlListProperty<QObject> *p, int idx)
{
    AsemanNetworkQuickObject *aobj = static_cast<AsemanNetworkQuickObject*>(p->object);
    return aobj->p->items.at(idx);
}

void AsemanNetworkQuickObject::clear(QQmlListProperty<QObject> *p)
{
    AsemanNetworkQuickObject *aobj = static_cast<AsemanNetworkQuickObject*>(p->object);
    aobj->p->items.clear();
    Q_EMIT aobj->itemsChanged();
}

AsemanNetworkQuickObject::~AsemanNetworkQuickObject()
{
    aseman_network_quick_objs.remove(this);
    delete p;
}
