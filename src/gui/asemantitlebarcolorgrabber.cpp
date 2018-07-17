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

#include "asemantitlebarcolorgrabber.h"

#include <QScreen>
#include <QPointer>
#include <QTimer>
#include <QDebug>
#include <QGuiApplication>

class AsemanTitleBarColorGrabberPrivate
{
public:
    QPointer<QWindow> window;
    QColor color;
    QColor defaultColor;
    bool autoRefresh;
    int firstAttemps;

    QTimer *normalTimer;
    QTimer *activeTimer;
};

AsemanTitleBarColorGrabber::AsemanTitleBarColorGrabber(QObject *parent) :
    QObject(parent)
{
    p = new AsemanTitleBarColorGrabberPrivate;
    p->firstAttemps = 0;
    p->autoRefresh = false;

    p->normalTimer = new QTimer(this);
    p->normalTimer->setSingleShot(false);
    p->normalTimer->setInterval(10000);

    p->activeTimer = new QTimer(this);
    p->activeTimer->setSingleShot(true);
    p->activeTimer->setInterval(500);

    connect(p->normalTimer, &QTimer::timeout, this, &AsemanTitleBarColorGrabber::refresh);
    connect(p->activeTimer, &QTimer::timeout, this, &AsemanTitleBarColorGrabber::refresh);
}

void AsemanTitleBarColorGrabber::setWindow(QWindow *win)
{
    if(p->window == win)
        return;
    if(p->window)
        disconnect(win, &QWindow::activeChanged, this, &AsemanTitleBarColorGrabber::activeChanged);

    p->window = win;
    if(p->window)
        connect(win, &QWindow::activeChanged, this, &AsemanTitleBarColorGrabber::activeChanged);

    Q_EMIT windowChanged();

    p->color = QColor();
    Q_EMIT colorChanged();

    p->firstAttemps = 0;
    refresh();
}

QWindow *AsemanTitleBarColorGrabber::window() const
{
    return p->window;
}

void AsemanTitleBarColorGrabber::setAutoRefresh(bool stt)
{
    if(p->autoRefresh == stt)
        return;

    p->autoRefresh = stt;
    if(p->autoRefresh)
        p->normalTimer->start();
    else
        p->normalTimer->stop();

    Q_EMIT autoRefreshChanged();
}

bool AsemanTitleBarColorGrabber::autoRefresh() const
{
    return p->autoRefresh;
}

void AsemanTitleBarColorGrabber::setDefaultColor(const QColor &defaultColor)
{
    if(p->defaultColor == defaultColor)
        return;

    p->defaultColor = defaultColor;
    Q_EMIT defaultColorChanged();
    Q_EMIT colorChanged();
}

QColor AsemanTitleBarColorGrabber::defaultColor() const
{
    return p->defaultColor;
}

QColor AsemanTitleBarColorGrabber::color() const
{
    return p->color.isValid()? p->color : p->defaultColor;
}

void AsemanTitleBarColorGrabber::refresh()
{
    if(!p->window)
    {
        QColor color;
        if(p->color == color)
            return;

        p->color = color;
        Q_EMIT colorChanged();
        return;
    }
    if(!p->window->isActive() || QGuiApplication::focusWindow() != p->window)
    {
        if(p->color == QColor())
            QTimer::singleShot(100, this, SLOT(refresh()));

        return;
    }
    p->firstAttemps++;
    if(p->firstAttemps < 6)
        QTimer::singleShot(300, this, SLOT(refresh()));

    QImage img = p->window->screen()->grabWindow(0, p->window->x()+100, p->window->y()-4, 1, 1).toImage();
    QColor color = img.pixel(0,0);
    if(p->color == color)
        return;

    p->color = color;
    Q_EMIT colorChanged();
}

void AsemanTitleBarColorGrabber::activeChanged()
{
    p->activeTimer->stop();
    p->activeTimer->start();
}

AsemanTitleBarColorGrabber::~AsemanTitleBarColorGrabber()
{
    delete p;
}
