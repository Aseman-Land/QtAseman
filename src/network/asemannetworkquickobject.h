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

#ifndef ASEMANQUICKOBJECT_H
#define ASEMANQUICKOBJECT_H

#include <QObject>
#include <QQmlListProperty>

#include "asemanglobals.h"

#include "asemannetwork_global.h"

class AsemanNetworkQuickObjectPrivate;
class LIBQTASEMAN_NETWORK_EXPORT AsemanNetworkQuickObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<QObject> items READ items NOTIFY itemsChanged)
    Q_CLASSINFO("DefaultProperty", "items")

public:
    Q_INVOKABLE explicit AsemanNetworkQuickObject(QObject *parent = Q_NULLPTR);
    virtual ~AsemanNetworkQuickObject();

    QQmlListProperty<QObject> items();
    QList<QObject*> itemsList() const;

    static bool isValid(AsemanNetworkQuickObject* obj);

Q_SIGNALS:
    void itemsChanged();

private:
    static void append(QQmlListProperty<QObject> *p, QObject *v);
    static int count(QQmlListProperty<QObject> *p);
    static QObject *at(QQmlListProperty<QObject> *p, int idx);
    static void clear(QQmlListProperty<QObject> *p);

private:
    AsemanNetworkQuickObjectPrivate *p;
};

typedef AsemanNetworkQuickObject QAsemanNetworkQuickObject;

#endif // ASEMANQUICKOBJECT_H
