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

#include "asemanwindowdetails.h"

#include <QPointer>
#include <QGuiApplication>

class AsemanWindowDetailsPrivate
{
public:
    QPointer<QWindow> window;
};

AsemanWindowDetails::AsemanWindowDetails(QObject *parent) :
    QObject(parent)
{
    p = new AsemanWindowDetailsPrivate;
}

QWindow *AsemanWindowDetails::window() const
{
    return p->window;
}

void AsemanWindowDetails::setWindow(QWindow *window)
{
    if(p->window == window)
        return;

    if(p->window)
        disconnect(p->window, &QWindow::screenChanged, this, &AsemanWindowDetails::screenChanged);

    p->window = window;
    if(p->window)
        connect(p->window, &QWindow::screenChanged, this, &AsemanWindowDetails::screenChanged);

    Q_EMIT windowChanged();
    Q_EMIT screenChanged();
}

QScreen *AsemanWindowDetails::screen() const
{
    if(p->window)
        return p->window->screen();
    else
        return QGuiApplication::primaryScreen();
}

AsemanWindowDetails::~AsemanWindowDetails()
{
    delete p;
}
