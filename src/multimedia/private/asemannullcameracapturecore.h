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

#ifndef ASEMANNULLCAMERACAPTURECORE_H
#define ASEMANNULLCAMERACAPTURECORE_H

#include "asemanabstractcameracapturecore.h"

#include "asemanmultimedia_global.h"

class LIBQTASEMAN_MULTIMEDIA_EXPORT AsemanNullCameraCaptureCore : public AsemanAbstractCameraCaptureCore
{
    Q_OBJECT
public:
    AsemanNullCameraCaptureCore(QObject *parent = 0);
    virtual ~AsemanNullCameraCaptureCore();

    int capture(const QString &dest, AsemanCameraCapture::CameraFace face);
};

#endif // ASEMANNULLCAMERACAPTURECORE_H
