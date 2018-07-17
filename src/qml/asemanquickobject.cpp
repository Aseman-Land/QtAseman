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

#include "asemanquickobject.h"

#include <QSet>

QSet<AsemanQuickObject*> aseman_quick_objs;

class AsemanQuickObjectPrivate
{
public:
    QList<QObject*> items;
};

AsemanQuickObject::AsemanQuickObject(QObject *parent) :
    QObject(parent)
{
    p = new AsemanQuickObjectPrivate;
    aseman_quick_objs.insert(this);
}

QQmlListProperty<QObject> AsemanQuickObject::items()
{
    return QQmlListProperty<QObject>(this, &p->items, QQmlListProperty<QObject>::AppendFunction(append),
                                                      QQmlListProperty<QObject>::CountFunction(count),
                                                      QQmlListProperty<QObject>::AtFunction(at),
                                     QQmlListProperty<QObject>::ClearFunction(clear) );
}

QList<QObject *> AsemanQuickObject::itemsList() const
{
    return p->items;
}

bool AsemanQuickObject::isValid(AsemanQuickObject *obj)
{
    return aseman_quick_objs.contains(obj);
}

void AsemanQuickObject::append(QQmlListProperty<QObject> *p, QObject *v)
{
    AsemanQuickObject *aobj = static_cast<AsemanQuickObject*>(p->object);
    aobj->p->items.append(v);
    Q_EMIT aobj->itemsChanged();
}

int AsemanQuickObject::count(QQmlListProperty<QObject> *p)
{
    AsemanQuickObject *aobj = static_cast<AsemanQuickObject*>(p->object);
    return aobj->p->items.count();
}

QObject *AsemanQuickObject::at(QQmlListProperty<QObject> *p, int idx)
{
    AsemanQuickObject *aobj = static_cast<AsemanQuickObject*>(p->object);
    return aobj->p->items.at(idx);
}

void AsemanQuickObject::clear(QQmlListProperty<QObject> *p)
{
    AsemanQuickObject *aobj = static_cast<AsemanQuickObject*>(p->object);
    aobj->p->items.clear();
    Q_EMIT aobj->itemsChanged();
}

AsemanQuickObject::~AsemanQuickObject()
{
    aseman_quick_objs.remove(this);
    delete p;
}
