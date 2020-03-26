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

#include "asemanandroidlocationlistenercore.h"

#include <QDebug>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QPointer>
#include <QString>
#include <QThread>
#include <QCoreApplication>

#include <jni.h>

QHash<jobject, AsemanAndroidLocationListenerCore*> android_location_listener_objects;

AsemanAndroidLocationListenerCore *getLocationListenerObject(jobject obj)
{
    QHashIterator<jobject, AsemanAndroidLocationListenerCore*> i(android_location_listener_objects);
    while(i.hasNext())
    {
        i.next();
        if(QAndroidJniObject(i.key()) == QAndroidJniObject(obj))
            return i.value();
    }

    return 0;
}

class AsemanAndroidLocationListenerPrivate
{
public:
    QAndroidJniObject object;
    QAndroidJniEnvironment env;
};

AsemanAndroidLocationListenerCore::AsemanAndroidLocationListenerCore(QObject *parent) :
    AsemanAbstractLocationListenerCore(parent)
{
    p = new AsemanAndroidLocationListenerPrivate;
    qRegisterMetaType<QGeoPositionInfo>("QGeoPositionInfo");

    p->object = QAndroidJniObject("io/aseman/android/extra/AsemanLocationListener");
    android_location_listener_objects.insert(p->object.object<jobject>(), this);
}

AsemanAndroidLocationListenerCore::~AsemanAndroidLocationListenerCore()
{
    android_location_listener_objects.remove(p->object.object<jobject>());
    delete p;
}

void AsemanAndroidLocationListenerCore::requestLocationUpdates(int interval)
{
    p->object.callMethod<void>(__FUNCTION__, "(I)V", interval);
}

void AsemanAndroidLocationListenerCore::getLastKnownLocation()
{
    p->object.callMethod<void>(__FUNCTION__, "()V");
}

static void locationListened( JNIEnv *env, jobject obj ,jdouble longitude, jdouble latitude, jdouble altitude, jstring city )
{
    Q_UNUSED(env)
    Q_UNUSED(city)
    AsemanAndroidLocationListenerCore *all = getLocationListenerObject(obj);
    if(!all)
        return;

    QGeoCoordinate coo(latitude, longitude, altitude);
    QGeoPositionInfo info(coo, QDateTime::currentDateTime());
    QMetaObject::invokeMethod(all, "positionUpdated", Q_ARG(QGeoPositionInfo, info));
}

bool aseman_android_loclis_registerNativeMethods() {
    JNINativeMethod methods[] {{"_locationListened", "(DDDLjava/lang/String;)V", reinterpret_cast<void *>(locationListened)}};

    QAndroidJniObject javaClass("io/aseman/android/extra/AsemanLocationListener");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());

    env->RegisterNatives(objectClass, methods, sizeof(methods) / sizeof(methods[0]));

    env->DeleteLocalRef(objectClass);
    return true;
}

const bool aseman_android_loclis_native_methods_registered = aseman_android_loclis_registerNativeMethods();
