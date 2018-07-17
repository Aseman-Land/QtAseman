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

#ifndef ASEMAN_MACROS_H
#define ASEMAN_MACROS_H

#include <QtGlobal>

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS) || defined(Q_OS_WINPHONE) || defined(Q_OS_UBUNTUTOUCH)
#define TOUCH_DEVICE
#else
#define DESKTOP_DEVICE
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
#define DESKTOP_LINUX
#endif
#endif

#endif // ASEMAN_MACROS_H
