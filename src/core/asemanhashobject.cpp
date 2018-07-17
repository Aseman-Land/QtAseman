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

#include "asemanhashobject.h"

#include <QList>
#include <QPair>
#include <QDebug>
#include <QDebug>

class AsemanHashObjectPrivate
{
public:
    QMultiHash<QString,QVariant> hash;
};

AsemanHashObject::AsemanHashObject(QObject *parent) :
    QObject(parent)
{
    p = new AsemanHashObjectPrivate;
}

void AsemanHashObject::insert(const QString &key, const QVariant &value)
{
    p->hash.insert(key,value);
    Q_EMIT countChanged();
}

void AsemanHashObject::insertMulti(const QString &key, const QVariant &value)
{
    p->hash.insertMulti(key,value);
    Q_EMIT countChanged();
}

void AsemanHashObject::remove(const QString &key)
{
    p->hash.remove(key);
    Q_EMIT countChanged();
}

void AsemanHashObject::remove(const QString &key, const QVariant &value)
{
    p->hash.remove(key,value);
    Q_EMIT countChanged();
}

QVariant AsemanHashObject::key(const QVariant &value)
{
    return p->hash.key(value);
}

QStringList AsemanHashObject::keys(const QVariant &value)
{
    return p->hash.keys(value);
}

QStringList AsemanHashObject::uniqueKeys()
{
    return p->hash.uniqueKeys();
}

QStringList AsemanHashObject::keys()
{
    return p->hash.keys();
}

QVariant AsemanHashObject::value(const QString &key)
{
    return p->hash.value(key);
}

QVariantList AsemanHashObject::values(const QString &key)
{
    return p->hash.values(key);
}

QVariant AsemanHashObject::containt(const QString &key)
{
    return contains(key);
}

QVariant AsemanHashObject::containt(const QString &key, const QVariant &value)
{
    return contains(key, value);
}

QVariant AsemanHashObject::contains(const QString &key)
{
    return p->hash.contains(key);
}

QVariant AsemanHashObject::contains(const QString &key, const QVariant &value)
{
    return p->hash.contains(key,value);
}

void AsemanHashObject::clear()
{
    if(p->hash.isEmpty())
        return;
    p->hash.clear();
    Q_EMIT countChanged();
}

int AsemanHashObject::count()
{
    return p->hash.count();
}

QVariantMap AsemanHashObject::toMap() const
{
    QVariantMap map;
    QHashIterator<QString, QVariant> i(p->hash);
    while(i.hasNext())
    {
        i.next();
        map.insertMulti(i.key(), i.value());
    }
    return map;
}

AsemanHashObject::~AsemanHashObject()
{
    delete p;
}
