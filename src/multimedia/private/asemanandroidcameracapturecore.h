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

#ifndef ASEMANANDROIDCAMERACAPTURE_H
#define ASEMANANDROIDCAMERACAPTURE_H

#include "asemanabstractcameracapturecore.h"

#include "asemanmultimedia_global.h"

class AsemanAndroidCameraCaptureCorePrivate;
class LIBQTASEMAN_MULTIMEDIA_EXPORT AsemanAndroidCameraCaptureCore : public AsemanAbstractCameraCaptureCore
{
    Q_OBJECT
public:
    AsemanAndroidCameraCaptureCore(QObject *parent = Q_NULLPTR);
    virtual ~AsemanAndroidCameraCaptureCore();

    int capture(const QString &dest, AsemanCameraCapture::CameraFace face);

Q_SIGNALS:
    void imageCaptured(int id, const QString &path);

private:
    AsemanAndroidCameraCaptureCorePrivate *p;
};

#endif // ASEMANANDROIDCAMERACAPTURE_H
