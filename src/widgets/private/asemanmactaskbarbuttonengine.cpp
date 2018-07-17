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

#include "asemanmactaskbarbuttonengine.h"

#ifdef QT_MACEXTRAS_LIB
#include <QtMac>
#endif

void AsemanMacTaskbarButtonEngine::updateBadgeNumber(int number)
{
#ifdef QT_MACEXTRAS_LIB
    QtMac::setBadgeLabelText(number?QString::number(number):"");
#else
    Q_UNUSED(number)
#endif
}

void AsemanMacTaskbarButtonEngine::updateProgress(qreal progress)
{
    Q_UNUSED(progress)
}
