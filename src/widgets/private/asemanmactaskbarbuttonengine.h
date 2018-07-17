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

#ifndef ASEMANMACTASKBARBUTTONENGINE_H
#define ASEMANMACTASKBARBUTTONENGINE_H

#include "asemanabstracttaskbarbuttonengine.h"

#include "asemanwidgets_global.h"

class LIBQTASEMAN_WIDGETS_EXPORT AsemanMacTaskbarButtonEngine : public AsemanAbstractTaskbarButtonEngine
{
public:
    AsemanMacTaskbarButtonEngine(){}
    virtual ~AsemanMacTaskbarButtonEngine(){}

    void updateBadgeNumber(int number);
    void updateProgress(qreal progress);
};

#endif // ASEMANMACTASKBARBUTTONENGINE_H
