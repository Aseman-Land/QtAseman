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

#include "asemanmouseeventlistener.h"

#include <QDebug>

class AsemanMouseEventListenerPrivate
{
public:
    QPointF point;
    bool ignoreEvent;
};

AsemanMouseEventListener::AsemanMouseEventListener(QQuickItem *parent) :
    QQuickItem(parent)
{
    p = new AsemanMouseEventListenerPrivate;
    p->ignoreEvent = false;
    setFiltersChildMouseEvents(true);
}

bool AsemanMouseEventListener::childMouseEventFilter(QQuickItem *item, QEvent *e)
{
    QMouseEvent *mevent = static_cast<QMouseEvent*>(e);
    switch(static_cast<int>(e->type()))
    {
    case QEvent::MouseMove:
    {
        QPointF newP = mapFromItem(item, mevent->pos());
        bool xChanged = (newP.x() != p->point.x());
        bool yChanged = (newP.y() != p->point.y());
        p->point = newP;
        if(xChanged) Q_EMIT mouseXChanged();
        if(yChanged) Q_EMIT mouseYChanged();
        Q_EMIT mousePositionChanged();
        break;
    }
    case QEvent::MouseButtonPress:
        p->point = mapFromItem(item, mevent->pos());
        Q_EMIT mousePressed();
        break;
    case QEvent::MouseButtonRelease:
        p->point = mapFromItem(item, mevent->pos());
        Q_EMIT mouseReleased();
        break;

    default:
        p->ignoreEvent = false;
        break;
    }

    if(p->ignoreEvent)
    {
        p->ignoreEvent = false;
        return true;
    }
    else
        return QQuickItem::childMouseEventFilter(item, e);
}

qreal AsemanMouseEventListener::mouseX() const
{
    return p->point.x();
}

qreal AsemanMouseEventListener::mouseY() const
{
    return p->point.y();
}

QPointF AsemanMouseEventListener::mousePosition() const
{
    return p->point;
}

void AsemanMouseEventListener::ignoreEvent()
{
    p->ignoreEvent = true;
}

void AsemanMouseEventListener::acceptEvent()
{
    p->ignoreEvent = false;
}

AsemanMouseEventListener::~AsemanMouseEventListener()
{
    delete p;
}
