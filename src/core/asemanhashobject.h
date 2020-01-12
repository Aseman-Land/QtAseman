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

#ifndef ASEMANHASHOBJECT_H
#define ASEMANHASHOBJECT_H

#include <QObject>
#include <QVariant>

#include "asemancore_global.h"

class AsemanHashObjectPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanHashObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    AsemanHashObject(QObject *parent = 0);
    virtual ~AsemanHashObject();

public Q_SLOTS:
    void insert(const QString & key, const QVariant & value );
    void insertMulti(const QString & key, const QVariant & value );
    void remove( const QString & key );
    void remove( const QString & key, const QVariant & value );

    QVariant key( const QVariant & value );
    QStringList keys( const QVariant & value );
    QStringList uniqueKeys();
    QStringList keys();
    QVariant value( const QString & key );
    QVariantList values( const QString & key );

    QVariant contains( const QString & key );
    QVariant contains( const QString & key, const QVariant & value );

    void clear();
    int count();

    QVariantMap toMap() const;

Q_SIGNALS:
    void countChanged();

private:
    AsemanHashObjectPrivate *p;
};

typedef AsemanHashObject QAsemanHashObject;

#endif // ASEMANHASHOBJECT_H
