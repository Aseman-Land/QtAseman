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

#include "asemandebugobjectcounter.h"

#include <QTimer>
#include <QPointer>
#include <QMap>
#include <QDebug>

class AsemanDebugObjectCounterPrivate
{
public:
    QTimer *timer;
    QPointer<QObject> object;
};

AsemanDebugObjectCounter::AsemanDebugObjectCounter(QObject *parent) :
    QObject(parent)
{
    p = new AsemanDebugObjectCounterPrivate;
    p->timer = new QTimer(this);

    connect(p->timer, &QTimer::timeout, this, &AsemanDebugObjectCounter::timeout);
}

void AsemanDebugObjectCounter::start(QObject *object, int interval)
{
    p->timer->stop();

    p->object = object;
    p->timer->setInterval(interval);
    p->timer->start();
}

void AsemanDebugObjectCounter::timeout()
{
    if(!p->object)
    {
        p->timer->stop();
        return;
    }

    QMap<QString,int> counts;
    calculate(p->object, counts);

    qDebug() << "\n\n";
    int total = 0;
    QMapIterator<QString,int> i(counts);
    while(i.hasNext())
    {
        i.next();
        qDebug() << i.key() + " = " << i.value();
        total += i.value();
    }

    qDebug() << "total" << total;
}

void AsemanDebugObjectCounter::calculate(QObject *obj, QMap<QString, int> &count)
{
    count[QString::fromUtf8(obj->metaObject()->className())] = count[QString::fromUtf8(obj->metaObject()->className())]+1;

    QObjectList childs = obj->children();
    for(QObject *child: childs)
        calculate(child, count);
}

AsemanDebugObjectCounter::~AsemanDebugObjectCounter()
{
    delete p;
}
