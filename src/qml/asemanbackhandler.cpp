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

#include "asemanbackhandler.h"
#include "asemantools.h"

#include <QPair>
#include <QStack>
#include <QDebug>

class AsemanHandlerItem
{
public:
    QObject *obj = Q_NULLPTR;
    QJSValue jsv;
};

class AsemanBackHandlerPrivate
{
public:
    QList<AsemanHandlerItem> stack;

    AsemanHandlerItem lastActiveItem(qint32 *index = Q_NULLPTR) {
        if (index)
            *index = -1;

        AsemanHandlerItem item;
        for (qint32 i=stack.count()-1; i>=0; i--)
        {
            AsemanHandlerItem _itm = stack.at(i);
            if (_itm.obj->property("disableBack").toBool() == false)
            {
                item = _itm;
                if (index)
                    *index = i;
                break;
            }
        }

        return item;
    }
};

AsemanBackHandler::AsemanBackHandler(QObject *parent) :
    QObject(parent)
{
    p = new AsemanBackHandlerPrivate;
}

QObject *AsemanBackHandler::topHandlerObject() const
{
    if( p->stack.isEmpty() )
        return Q_NULLPTR;

    return p->stack.last().obj;
}

QJSValue AsemanBackHandler::topHandlerMethod() const
{
    if( p->stack.isEmpty() )
        return QString();

    return p->stack.last().jsv;
}

int AsemanBackHandler::count()
{
    qint32 index = 0;
    AsemanHandlerItem item = p->lastActiveItem(&index);
    return index+1;
}

void AsemanBackHandler::pushHandler(QObject *obj, QJSValue jsv)
{
    AsemanHandlerItem item;
    item.obj = obj;
    item.jsv = jsv;

    p->stack.append( item );
    Q_EMIT countChanged();

    setupObject(obj);
}

void AsemanBackHandler::pushDownHandler(QObject *obj, QJSValue jsv)
{
    AsemanHandlerItem item;
    item.obj = obj;
    item.jsv = jsv;

    p->stack.prepend( item );
    Q_EMIT countChanged();

    setupObject(obj);
}

void AsemanBackHandler::removeHandler(QObject *obj)
{
    for( int i=p->stack.count()-1; i>=0; i-- )
        if( p->stack.at(i).obj == obj )
        {
            p->stack.removeAt(i);
            break;
        }

    Q_EMIT countChanged();
}

QObject *AsemanBackHandler::tryPopHandler()
{
    if( p->stack.isEmpty() )
        return Q_NULLPTR;

    qint32 index = 0;
    AsemanHandlerItem item = p->lastActiveItem(&index);
    if (!item.obj)
        return Q_NULLPTR;

    const int count = p->stack.count();

    const QJSValue & res = item.jsv.call();
    if( !res.isUndefined() && res.toBool() == false )
        return Q_NULLPTR;

    if( p->stack.count() == count )
        p->stack.takeAt(index);

    Q_EMIT countChanged();
    return item.obj;
}

QObject *AsemanBackHandler::forcePopHandler()
{
    if( p->stack.isEmpty() )
        return Q_NULLPTR;

    qint32 index = 0;
    AsemanHandlerItem item = p->lastActiveItem(&index);
    if (!item.obj)
        return Q_NULLPTR;

    const int count = p->stack.count();

    item.jsv.call();
    if( p->stack.count() == count )
        p->stack.takeAt(index);

    Q_EMIT countChanged();
    return item.obj;
}

void AsemanBackHandler::clear()
{
    p->stack.clear();
}

bool AsemanBackHandler::back()
{
    if(count() == 0)
    {
        Q_EMIT backFinished();
        return false;
    }

    tryPopHandler();
    return true;
}

void AsemanBackHandler::object_destroyed(QObject *obj)
{
    for( int i=0; i<p->stack.count(); i++ )
        if( p->stack.at(i).obj == obj )
        {
            p->stack.removeAt(i);
            i--;
        }

    Q_EMIT countChanged();
}

void AsemanBackHandler::setupObject(QObject *obj)
{
    if (!obj->property("disableBack").isNull())
        connect(obj, SIGNAL(disableBackChanged()), this, SIGNAL(countChanged()));

    connect(obj, &QObject::destroyed, this, &AsemanBackHandler::object_destroyed );
}

AsemanBackHandler::~AsemanBackHandler()
{
    delete p;
}
