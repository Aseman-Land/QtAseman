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

#ifndef ASEMANABSTRACTCAMERACAPTURECORE_H
#define ASEMANABSTRACTCAMERACAPTURECORE_H

#include <QObject>
#include "../asemancameracapture.h"

#include "asemanmultimedia_global.h"

class LIBQTASEMAN_MULTIMEDIA_EXPORT AsemanAbstractCameraCaptureCore : public QObject
{
    Q_OBJECT
public:
    AsemanAbstractCameraCaptureCore(QObject *parent = Q_NULLPTR);
    virtual ~AsemanAbstractCameraCaptureCore();

    virtual int capture(const QString &dest, AsemanCameraCapture::CameraFace face) = 0;

Q_SIGNALS:
    void imageCaptured(int id, const QString &path);
};

#endif // ASEMANABSTRACTCAMERACAPTURECORE_H
