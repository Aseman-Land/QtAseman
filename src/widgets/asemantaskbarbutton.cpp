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

#include "asemantaskbarbutton.h"
#include "private/asemanabstracttaskbarbuttonengine.h"

#include <QDebug>

#ifdef Q_OS_WIN
#include "private/asemanwintaskbarbuttonengine.h"
#else
#ifdef Q_OS_MAC
#include "private/asemanmactaskbarbuttonengine.h"
#else
#if defined(Q_OS_LINUX) && defined(QT_DBUS_LIB)
#include "private/asemanunitytaskbarbuttonengine.h"
#else
#include "private/asemanabstracttaskbarbuttonengine.h"
class AsemanNullTaskbarButtonEngine: public AsemanAbstractTaskbarButtonEngine
{
public:
    void updateBadgeNumber(int number){Q_UNUSED(number)}
    void updateProgress(qreal progress){Q_UNUSED(progress)}
};
#endif
#endif
#endif

class AsemanTaskbarButtonPrivate
{
public:
    int badgeNumber;
    qreal progress;
    QString launcher;
    AsemanAbstractTaskbarButtonEngine *engine;
    QWindow *window;
};

AsemanTaskbarButton::AsemanTaskbarButton(QObject *parent) :
    QObject(parent)
{
    p = new AsemanTaskbarButtonPrivate;
    p->badgeNumber = 0;
    p->progress = 0;
    p->window = 0;
    p->engine = 0;

#ifdef Q_OS_WIN
#ifdef QT_WINEXTRAS_LIB
    p->engine = new AsemanWinTaskbarButtonEngine();
#endif
#else
#ifdef Q_OS_MAC
#ifdef QT_MACEXTRAS_LIB
    p->engine = new AsemanMacTaskbarButtonEngine();
#endif
#else
#if defined(Q_OS_LINUX) && defined(QT_DBUS_LIB)
    p->engine = new AsemanUnityTaskbarButtonEngine();
#else
    p->engine = new AsemanNullTaskbarButtonEngine();
#endif
#endif
#endif
}

void AsemanTaskbarButton::setBadgeNumber(int num)
{
    if(p->badgeNumber == num)
        return;

    p->badgeNumber = num;
    if(p->engine) p->engine->updateBadgeNumber(num);
    Q_EMIT badgeNumberChanged();
}

int AsemanTaskbarButton::badgeNumber() const
{
    return p->badgeNumber;
}

void AsemanTaskbarButton::setProgress(qreal progress)
{
    if(p->progress == progress)
        return;

    p->progress = progress;
    if(p->engine) p->engine->updateProgress(progress);
    Q_EMIT progressChanged();
}

qreal AsemanTaskbarButton::progress() const
{
    return p->progress;
}

void AsemanTaskbarButton::setLauncher(const QString &launcher)
{
    if(p->launcher == launcher)
        return;

    p->launcher = launcher;
    if(p->engine) p->engine->updateLauncher(p->launcher);
    Q_EMIT launcherChanged();
}

QString AsemanTaskbarButton::launcher() const
{
    return p->launcher;
}

void AsemanTaskbarButton::setWindow(QWindow *win)
{
    if(p->window == win)
        return;

    p->window = win;
    if(p->engine) p->engine->updateWindow(p->window);
    Q_EMIT windowChanged();
}

QWindow *AsemanTaskbarButton::window() const
{
    return p->window;
}

void AsemanTaskbarButton::userAttention()
{
    if(p->engine) p->engine->userAttention();
}

AsemanTaskbarButton::~AsemanTaskbarButton()
{
    if(p->engine) delete p->engine;
    delete p;
}
