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
/*!
    \class AsemanHashObject
    \brief In fact it acts like a QHash<QString, QVariant> class, But
    in the QML.

    \reentrant
    \ingroup AsemanCore
 */

/*!
    \fn AsemanHashObject::countChanged
    This signal emits when count of the hash object changed.
    \sa insert
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


/*!
    \brief Inserts a new item with the \a key and \a value of value.

    If there is already an item with the key,
    that item's value is replaced with value.
    If there are multiple items with the key,
    the most recently inserted item's value is replaced with value.

    \sa insertMulti
 */
void AsemanHashObject::insert(const QString &key, const QVariant &value)
{
    p->hash.insert(key,value);
    Q_EMIT countChanged();
}


/*!
    \brief Inserts a new item with the \a key and \a value of value.

    If there is already an item with the same key in the hash,
    this function will simply create a new one.

    \sa insert
 */
void AsemanHashObject::insertMulti(const QString &key, const QVariant &value)
{
    p->hash.insertMulti(key,value);
    Q_EMIT countChanged();
}


/*!
    \brief Removes all the items that have the \a key from the hash.
    Returns the number of items removed which is usually 1 but will
    be 0 if the key isn't in the hash, or greater than 1 if insertMulti()
    has been used with the key.

    \sa insertMulti
 */
void AsemanHashObject::remove(const QString &key)
{
    p->hash.remove(key);
    Q_EMIT countChanged();
}


/*!
    \brief Removes all the items that have both the \a key and the \a value
    from the hash.
    Returns the number of items removed which is usually 1 but will
    be 0 if the key isn't in the hash, or greater than 1 if insertMulti()
    has been used with the key.

    \sa insertMulti
 */
void AsemanHashObject::remove(const QString &key, const QVariant &value)
{
    p->hash.remove(key,value);
    Q_EMIT countChanged();
}


/*!
    \brief Returns the first key mapped to value.
    If the hash contains no item with the value,
    the function returns a default-constructed key.

    \sa value
    \sa key
 */
QVariant AsemanHashObject::key(const QVariant &value)
{
    return p->hash.key(value);
}


/*!
    \brief Returns a list containing all the keys in the hash, in an
    arbitrary order. Keys that occur multiple times in the hash
    (because items were inserted with insertMulti(), or unite() was
    used) also occur multiple times in the list.

    To obtain a list of unique keys, where each key from the map
    only occurs once, use uniqueKeys().

    The order is guaranteed to be the same as that used by values().

    \sa uniqueKeys
    \sa key
    \sa values
 */
QStringList AsemanHashObject::keys(const QVariant &value)
{
    return p->hash.keys(value);
}


/*!
    \brief Returns a list containing all the keys in the map.
    Keys that occur multiple times in the map (because items
    were inserted with insertMulti(), or unite() was used) occur
    only once in the returned list.

    \sa key
    \sa values
 */
QStringList AsemanHashObject::uniqueKeys()
{
    return p->hash.uniqueKeys();
}


/*!
    \brief Returns a list containing all the keys in the hash,
    in an arbitrary order. Keys that occur multiple times in
    the hash (because items were inserted with insertMulti(),
    or unite() was used) also occur multiple times in the list.

    To obtain a list of unique keys, where each key from the
    map only occurs once, use uniqueKeys().

    The order is guaranteed to be the same as that used by values().

    \sa key
    \sa values
    \sa uniqueKeys
 */
QStringList AsemanHashObject::keys()
{
    return p->hash.keys();
}


/*!
    \brief Returns the value associated with the \a key.

    If the hash contains no item with the \a key, the function
    returns a default-constructed value. If there are multiple
    items for the key in the hash, the value of the most
    recently inserted one is returned.

    \sa key
    \sa values
    \sa contains
 */
QVariant AsemanHashObject::value(const QString &key)
{
    return p->hash.value(key);
}


/*!
    \brief Returns a list containing all the values in the hash,
    in an arbitrary order. If a \a key is associated with multiple
    values, all of its values will be in the list, and not just
    the most recently inserted one.

    The order is guaranteed to be the same as that used by keys().

    \sa keys
    \sa value
 */
QVariantList AsemanHashObject::values(const QString &key)
{
    return p->hash.values(key);
}


/*!
    \brief Returns true if the hash contains an item with the \a key;
    otherwise returns false.

    \sa count
 */
QVariant AsemanHashObject::contains(const QString &key)
{
    return p->hash.contains(key);
}


/*!
    \brief Returns true if the hash contains an item with the \a key and \a value;
    otherwise returns false.

    \sa count
 */
QVariant AsemanHashObject::contains(const QString &key, const QVariant &value)
{
    return p->hash.contains(key,value);
}


/*!
    \brief Removes all items from the hash.

    \sa remove
 */
void AsemanHashObject::clear()
{
    if(p->hash.isEmpty())
        return;
    p->hash.clear();
    Q_EMIT countChanged();
}


/*!
    \brief Returns the number of items associated with the key.

    \sa contains
    \sa insertMulti
 */
int AsemanHashObject::count()
{
    return p->hash.count();
}


/*!
    \brief Converts and Return hash to the QVariantMap object.

    \sa keys
    \sa values
 */
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
