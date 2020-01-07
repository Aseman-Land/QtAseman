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

#ifndef ASEMANBACKHANDLER_H
#define ASEMANBACKHANDLER_H

#include <QObject>
#include <QJSValue>

#include "asemantools_global.h"

class AsemanBackHandlerPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanBackHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* topHandlerObject READ topHandlerObject NOTIFY topHandlerChanged)
    Q_PROPERTY(QJSValue topHandlerMethod READ topHandlerMethod NOTIFY topHandlerChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    AsemanBackHandler(QObject *parent = 0);
    virtual ~AsemanBackHandler();

    QObject *topHandlerObject() const;
    QJSValue topHandlerMethod() const;

    int count();

public Q_SLOTS:
    void pushHandler( QObject *obj, QJSValue jsv );
    void pushDownHandler( QObject *obj, QJSValue jsv );
    void removeHandler( QObject *obj );

    QObject *tryPopHandler();
    QObject *forcePopHandler();
    void clear();

    bool back();

Q_SIGNALS:
    void topHandlerChanged();
    void countChanged();
    void backFinished();

private Q_SLOTS:
    void object_destroyed( QObject *obj );

private:
    void setupObject(QObject *obj);

private:
    AsemanBackHandlerPrivate *p;
};

typedef AsemanBackHandler QAsemanBackHandler;

#endif // ASEMANBACKHANDLER_H
