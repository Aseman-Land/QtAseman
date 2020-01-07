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

#ifndef ASEMANMOUSEEVENTLISTENER_H
#define ASEMANMOUSEEVENTLISTENER_H

#include <QQuickItem>

#include "asemantools_global.h"

class AsemanMouseEventListenerPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanMouseEventListener : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal mouseX READ mouseX NOTIFY mouseXChanged)
    Q_PROPERTY(qreal mouseY READ mouseY NOTIFY mouseYChanged)
    Q_PROPERTY(QPointF mousePosition READ mousePosition NOTIFY mousePositionChanged)

public:
    AsemanMouseEventListener(QQuickItem *parent = Q_NULLPTR);
    virtual ~AsemanMouseEventListener();

    qreal mouseX() const;
    qreal mouseY() const;
    QPointF mousePosition() const;

public Q_SLOTS:
    void ignoreEvent();
    void acceptEvent();

Q_SIGNALS:
    void mouseXChanged();
    void mouseYChanged();
    void mousePositionChanged();
    void mousePressed();
    void mouseReleased();

protected:
    bool childMouseEventFilter(QQuickItem *item, QEvent *event);

private:
    AsemanMouseEventListenerPrivate *p;
};

typedef AsemanMouseEventListener QAsemanMouseEventListener;

#endif // ASEMANMOUSEEVENTLISTENER_H
