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

#ifndef ASEMANDEBUGOBJECTCOUNTER_H
#define ASEMANDEBUGOBJECTCOUNTER_H

#include <QObject>

#include "asemancore_global.h"

class AsemanDebugObjectCounterPrivate;
/*!
    \private
 */
class LIBQTASEMAN_CORE_EXPORT AsemanDebugObjectCounter : public QObject
{
    Q_OBJECT
public:
    AsemanDebugObjectCounter(QObject *parent = Q_NULLPTR);
    virtual ~AsemanDebugObjectCounter();

public Q_SLOTS:
    void start(QObject *object, int interval);

private Q_SLOTS:
    void timeout();

private:
    void calculate(QObject *obj, QMap<QString, int> &count);

private:
    AsemanDebugObjectCounterPrivate *p;
};

typedef AsemanDebugObjectCounter QAsemanDebugObjectCounter;

#endif // ASEMANDEBUGOBJECTCOUNTER_H
