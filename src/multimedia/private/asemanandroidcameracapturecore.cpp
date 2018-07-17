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

#include "asemanandroidcameracapturecore.h"

#include <QDebug>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QPointer>
#include <QString>
#include <QThread>
#include <QCoreApplication>

#include <jni.h>

QHash<jobject, AsemanAndroidCameraCaptureCore*> android_camera_capture_objects;

AsemanAndroidCameraCaptureCore *getCameraCaptureObject(jobject obj)
{
    QHashIterator<jobject, AsemanAndroidCameraCaptureCore*> i(android_camera_capture_objects);
    while(i.hasNext())
    {
        i.next();
        if(QAndroidJniObject(i.key()) == QAndroidJniObject(obj))
            return i.value();
    }

    return 0;
}

class AsemanAndroidCameraCaptureCorePrivate
{
public:
    QAndroidJniObject object;
    QAndroidJniEnvironment env;
    int idIndexs;
};

AsemanAndroidCameraCaptureCore::AsemanAndroidCameraCaptureCore(QObject *parent) :
    AsemanAbstractCameraCaptureCore(parent)
{
    p = new AsemanAndroidCameraCaptureCorePrivate;
    p->idIndexs = 1000;
    p->object = QAndroidJniObject("land/aseman/android/extra/AsemanCameraCapture");
    android_camera_capture_objects.insert(p->object.object<jobject>(), this);
}

int AsemanAndroidCameraCaptureCore::capture(const QString &dest, AsemanCameraCapture::CameraFace face)
{
    p->idIndexs++;
    jboolean jface = (face==AsemanCameraCapture::CameraFacingFront?true:false);
    jstring jdest = p->env->NewString(reinterpret_cast<const jchar*>(dest.constData()), dest.length());
    p->object.callMethod<void>(__FUNCTION__, "(ILjava/lang/String;Z)V", p->idIndexs, jdest, jface);
    return p->idIndexs;
}

AsemanAndroidCameraCaptureCore::~AsemanAndroidCameraCaptureCore()
{
    android_camera_capture_objects.remove(p->object.object<jobject>());
    delete p;
}

static void imageCaptured( JNIEnv *env, jobject obj, jint id, jstring path)
{
    AsemanAndroidCameraCaptureCore *smc = getCameraCaptureObject(obj);
    if(!smc)
        return;

    jboolean a;
    QString qpath = env->GetStringUTFChars(path,&a);
    int cid = id;
    QMetaObject::invokeMethod(smc, "imageCaptured", Q_ARG(int,cid), Q_ARG(QString, qpath));
}

bool aseman_android_camcap_registerNativeMethods() {
    JNINativeMethod methods[] {{"_imageCaptured", "(ILjava/lang/String;)V", reinterpret_cast<void *>(imageCaptured)}};

    QAndroidJniObject javaClass("land/aseman/android/extra/AsemanCameraCapture");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());

    env->RegisterNatives(objectClass, methods, sizeof(methods) / sizeof(methods[0]));

    env->DeleteLocalRef(objectClass);
    return true;
}

const bool aseman_android_camcap_native_methods_registered = aseman_android_camcap_registerNativeMethods();
