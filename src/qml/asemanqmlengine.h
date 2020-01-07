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

#ifndef ASEMANQMLENGINE_H
#define ASEMANQMLENGINE_H

#include <QQmlApplicationEngine>

#include "asemantools_global.h"

class AsemanQmlEnginePrivate;
class LIBQTASEMAN_QML_EXPORT AsemanQmlEngine : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    AsemanQmlEngine(QObject *parent = 0);
    virtual ~AsemanQmlEngine();

Q_SIGNALS:

public Q_SLOTS:

private:
    AsemanQmlEnginePrivate *p;
};

typedef AsemanQmlEngine QAsemanQmlEngine;

#endif // ASEMANQMLENGINE_H
