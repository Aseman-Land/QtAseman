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

#ifndef ASEMANMAPOBJECT_H
#define ASEMANMAPOBJECT_H

#include <QObject>
#include <QVariant>

#include "asemancore_global.h"

class AsemanMapObjectPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanMapObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QVariantList values READ values NOTIFY valuesChanged)
    Q_PROPERTY(QStringList keys READ keys NOTIFY keysChanged)

public:
    AsemanMapObject(QObject *parent = Q_NULLPTR);
    virtual ~AsemanMapObject();

    Q_INVOKABLE void insert(const QString & key, const QVariant & value );
    Q_INVOKABLE void insertMulti(const QString & key, const QVariant & value );
    Q_INVOKABLE void remove( const QString & key );
    Q_INVOKABLE void remove( const QString & key, const QVariant & value );

    Q_INVOKABLE QVariant key( const QVariant & value );
    Q_INVOKABLE QStringList keys( const QVariant & value );
    Q_INVOKABLE QStringList uniqueKeys();
    Q_INVOKABLE QStringList keys();
    Q_INVOKABLE QVariant value( const QString & key );
    Q_INVOKABLE QVariantList values( const QString & key );
    QVariantList values() const;

    Q_INVOKABLE QVariant containt( const QString & key );
    Q_INVOKABLE QVariant containt( const QString & key, const QVariant & value );
    Q_INVOKABLE QVariant contains( const QString & key );
    Q_INVOKABLE QVariant contains( const QString & key, const QVariant & value );

    Q_INVOKABLE void clear();
    Q_INVOKABLE int count();

    Q_INVOKABLE QVariantMap toMap() const;

Q_SIGNALS:
    void countChanged();
    void valuesChanged();
    void keysChanged();

private:
    AsemanMapObjectPrivate *p;
};

typedef AsemanMapObject QAsemanMapObject;

#endif // ASEMANMAPOBJECT_H
