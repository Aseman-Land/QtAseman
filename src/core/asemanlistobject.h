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

#ifndef ASEMANLISTOBJECT_H
#define ASEMANLISTOBJECT_H

#include <QObject>
#include <QVariant>

#include "asemancore_global.h"

class AsemanListObjectPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanListObject : public QObject
{
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QVariantList list READ toList WRITE fromList NOTIFY countChanged)

    Q_OBJECT
public:
    AsemanListObject(QObject *parent = 0);
    virtual ~AsemanListObject();

public Q_SLOTS:
    void removeAll( const QVariant & v );
    void removeOne( const QVariant & v );
    void removeAt( int index );
    QVariant takeLast();
    QVariant takeFirst();
    QVariant takeAt( int index );

    void clear();

    QVariant last() const;
    QVariant first() const;

    void insert( int index, const QVariant & v );
    void append( const QVariant & v );
    void prepend( const QVariant & v );

    int count() const;
    bool isEmpty() const;

    QVariant at( int index ) const;
    int indexOf( const QVariant & v ) const;

    void fromList( const QVariantList & list );
    QVariantList toList() const;

    bool contains( const QVariant & v ) const;
    void sort();

Q_SIGNALS:
    void countChanged();

private:
    AsemanListObjectPrivate *p;
};

#endif // ASEMANLISTOBJECT_H
