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

#ifndef ASEMANWINDOWDETAILS_H
#define ASEMANWINDOWDETAILS_H

#include <QObject>
#include <QWindow>
#include <QScreen>

#include "asemangui_global.h"

class AsemanWindowDetailsPrivate;
class LIBQTASEMAN_GUI_EXPORT AsemanWindowDetails : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ window WRITE setWindow NOTIFY windowChanged)
    Q_PROPERTY(QScreen* screen READ screen NOTIFY screenChanged)

public:
    AsemanWindowDetails(QObject *parent = Q_NULLPTR);
    virtual ~AsemanWindowDetails();

    QWindow *window() const;
    void setWindow(QWindow *window);

    QScreen *screen() const;

Q_SIGNALS:
    void windowChanged();
    void screenChanged();

private:
    AsemanWindowDetailsPrivate *p;
};

typedef AsemanWindowDetails QAsemanWindowDetails;

#endif // ASEMANWINDOWDETAILS_H
