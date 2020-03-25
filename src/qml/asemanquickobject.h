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

#include "asemantools_global.h"

#define aqobject_cast(OBJECT) static_cast<AsemanQuickObject*>(OBJECT)

#define DEFINE_QML_PROEPRTY(TYPE, PNAME) \
    private: \
        QVariant _##PNAME; \
    Q_SIGNALS: \
        void PNAME##Changed(); \
    public: \
        Q_PROPERTY(TYPE PNAME READ PNAME WRITE set##PNAME NOTIFY PNAME##Changed) \
        TYPE PNAME() const { return _##PNAME.value<TYPE>(); } \
        void set##PNAME(TYPE PNAME) { SET_PROPERTY(PNAME) }

class AsemanQuickObjectPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanQuickObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<QObject> items READ items NOTIFY itemsChanged)
    Q_CLASSINFO("DefaultProperty", "items")

public:
    Q_INVOKABLE explicit AsemanQuickObject(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickObject();

    QQmlListProperty<QObject> items();
    QList<QObject*> itemsList() const;

    static bool isValid(AsemanQuickObject* obj);

Q_SIGNALS:
    void itemsChanged();

private:
    static void append(QQmlListProperty<QObject> *p, QObject *v);
    static int count(QQmlListProperty<QObject> *p);
    static QObject *at(QQmlListProperty<QObject> *p, int idx);
    static void clear(QQmlListProperty<QObject> *p);

private:
    AsemanQuickObjectPrivate *p;
};

typedef AsemanQuickObject QAsemanQuickObject;

#endif // ASEMANQUICKOBJECT_H
