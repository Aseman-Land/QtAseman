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

#include "asemanlistobject.h"

#include <QVariantList>
#include <QDebug>

class AsemanListObjectPrivate
{
public:
    QVariantList list;
};

AsemanListObject::AsemanListObject(QObject *parent) :
    QObject(parent)
{
    p = new AsemanListObjectPrivate;
}

void AsemanListObject::removeAll(const QVariant &v)
{
    p->list.removeAll( v );
    Q_EMIT countChanged();
}

void AsemanListObject::removeOne(const QVariant &v)
{
    p->list.removeOne( v );
    Q_EMIT countChanged();
}

void AsemanListObject::removeAt(int index)
{
    p->list.removeAt( index );
    Q_EMIT countChanged();
}

QVariant AsemanListObject::takeLast()
{
    if( p->list.isEmpty() )
        return QVariant();

    const QVariant & res = p->list.takeLast();
    Q_EMIT countChanged();

    return res;
}

QVariant AsemanListObject::takeFirst()
{
    if( p->list.isEmpty() )
        return QVariant();

    const QVariant & res = p->list.takeFirst();
    Q_EMIT countChanged();

    return res;
}

QVariant AsemanListObject::takeAt(int index)
{
    const QVariant & res = p->list.takeAt( index );
    Q_EMIT countChanged();

    return res;
}

void AsemanListObject::clear()
{
    p->list.clear();
    Q_EMIT countChanged();
}

QVariant AsemanListObject::last() const
{
    if( p->list.isEmpty() )
        return QVariant();

    return p->list.last();
}

QVariant AsemanListObject::first() const
{
    if( p->list.isEmpty() )
        return QVariant();

    return p->list.first();
}

void AsemanListObject::insert(int index, const QVariant &v)
{
    p->list.insert( index, v );
    Q_EMIT countChanged();
}

void AsemanListObject::append(const QVariant &v)
{
    p->list.append( v );
    Q_EMIT countChanged();
}

void AsemanListObject::prepend(const QVariant &v)
{
    p->list.prepend( v );
    Q_EMIT countChanged();
}

void AsemanListObject::replace(int index, const QVariant &v)
{
    p->list.replace(index, v);
}

void AsemanListObject::swap(int idx0, int idx1)
{
    p->list.swap(idx0, idx1);
}

int AsemanListObject::count() const
{
    return p->list.count();
}

bool AsemanListObject::isEmpty() const
{
    return p->list.isEmpty();
}

QVariant AsemanListObject::at(int index) const
{
    if(index == -1)
        return QVariant();

    return p->list.at(index);
}

int AsemanListObject::indexOf(const QVariant &v) const
{
    return p->list.indexOf(v);
}

void AsemanListObject::fromList(const QVariantList &list)
{
    if( p->list == list )
        return;

    p->list = list;
    Q_EMIT countChanged();
}

QVariantList AsemanListObject::toList() const
{
    return p->list;
}

bool AsemanListObject::contains(const QVariant &v) const
{
    return p->list.contains(v);
}

void AsemanListObject::sort()
{
    std::stable_sort(p->list.begin(), p->list.end());
}

AsemanListObject::~AsemanListObject()
{
    delete p;
}
