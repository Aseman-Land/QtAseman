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

#ifndef ASEMANGLOBALS_H
#define ASEMANGLOBALS_H

/*!
    \defgroup AsemanCore
    Provides core classes, methods and tools of the QAseman modules.
    It only needs QtCore module and has no GUI.

    You can add it to your project using below command:
    \code{.pro}
    QT += asemancore
    \endcode
 */

#include <QtGlobal>

#define SET_PROPERTY(PROPERTY_NAME) \
    if(_##PROPERTY_NAME == PROPERTY_NAME) return; \
    _##PROPERTY_NAME = PROPERTY_NAME; \
    Q_EMIT PROPERTY_NAME##Changed();

#define SET_PROPERTY_P(PROPERTY_NAME) \
    if(p->PROPERTY_NAME == PROPERTY_NAME) return; \
    p->PROPERTY_NAME = PROPERTY_NAME; \
    Q_EMIT PROPERTY_NAME##Changed();

#endif // ASEMANGLOBALS_H
