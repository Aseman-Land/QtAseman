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

#ifndef ASEMANDRAGAREA_H
#define ASEMANDRAGAREA_H

#include <QQuickItem>

#include "asemantools_global.h"

class AsemanDragAreaPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanDragArea : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(int mouseX READ mouseX NOTIFY mouseXChanged)
    Q_PROPERTY(int mouseY READ mouseY NOTIFY mouseYChanged)

public:
    AsemanDragArea(QQuickItem *parent = 0);
    virtual ~AsemanDragArea();

    void setMinimum(int min);
    int minimum() const;

    void setOrientation(int ori);
    int orientation() const;

    int mouseX() const;
    int mouseY() const;

Q_SIGNALS:
    void minimumChanged();
    void orientationChanged();

    void positionChanged();
    void mouseXChanged();
    void mouseYChanged();
    void pressed();
    void released();

protected:
    bool childMouseEventFilter(QQuickItem *item, QEvent *event);

private:
    AsemanDragAreaPrivate *p;
};

typedef AsemanDragArea QAsemanDragArea;

#endif // ASEMANDRAGAREA_H
