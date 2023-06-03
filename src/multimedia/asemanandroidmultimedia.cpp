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

#include "asemanandroidmultimedia.h"

#include <QDebug>
#include <QSet>
#include <QPair>
#include <QList>
#include <QDateTime>
#include <QFile>
#include <QCoreApplication>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QPointer>
#include <QColor>

#include <jni.h>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QJniEnvironment>
#include <QJniObject>
typedef QJniEnvironment QAndroidJniEnvironment;
typedef QJniObject QAndroidJniObject;
#else
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#endif

static QSet<AsemanAndroidMultimedia*> android_multimedia_objects;
static QList< QPair<QString,QString> > java_layer_inc_share_buffer;
static QList< QString > java_layer_inc_image_buffer;

static bool aseman_jlayer_registerNativeMethods();
static bool aseman_jlayer_native_methods_registered = aseman_jlayer_registerNativeMethods();

class AsemanAndroidMultimediaPrivate
{
public:
    QAndroidJniObject object;
    QAndroidJniEnvironment env;
};

AsemanAndroidMultimedia::AsemanAndroidMultimedia() :
    QObject()
{
    p = new AsemanAndroidMultimediaPrivate;
    p->object = QAndroidJniObject("io/aseman/android/AsemanMultimedia");

#if defined(Q_OS_ANDROID) && defined(ASEMAN_STATIC_BUILD)
    QMetaObject::invokeMethod( this, "registerObject", Qt::QueuedConnection );
#else
    registerObject();
#endif

    setImplemented(true);
}

void AsemanAndroidMultimedia::registerObject()
{
    android_multimedia_objects.insert(this);
}

AsemanAndroidMultimedia *AsemanAndroidMultimedia::instance()
{
    if(!aseman_jlayer_native_methods_registered)
        aseman_jlayer_registerNativeMethods();

    static QPointer<AsemanAndroidMultimedia> java_layer_instance;
    if( !java_layer_instance )
    {
        java_layer_instance = new AsemanAndroidMultimedia();
        if(QCoreApplication::instance())
            QObject::connect(QCoreApplication::instance(), &QCoreApplication::destroyed, java_layer_instance, &AsemanAndroidMultimedia::deleteLater);
    }

    return java_layer_instance;
}

QString AsemanAndroidMultimedia::getAllMusics()
{
    QString res = p->object.callObjectMethod(__FUNCTION__, "()Ljava/lang/String;" ).toString();
    return res;
}

QString AsemanAndroidMultimedia::getAllAlbums()
{
    QString res = p->object.callObjectMethod(__FUNCTION__, "()Ljava/lang/String;" ).toString();
    return res;
}

QString AsemanAndroidMultimedia::getAllArtists()
{
    QString res = p->object.callObjectMethod(__FUNCTION__, "()Ljava/lang/String;" ).toString();
    return res;
}

QString AsemanAndroidMultimedia::getArtistAlbums(const QString &artistId)
{
    QAndroidJniObject jartistId = QAndroidJniObject::fromString(artistId);
    QString res = p->object.callObjectMethod(__FUNCTION__, "(Ljava/lang/String;)Ljava/lang/String;", jartistId.object<jstring>()).toString();
    return res;
}

QString AsemanAndroidMultimedia::getArtistSongs(const QString &artistId)
{
    QAndroidJniObject jartistId = QAndroidJniObject::fromString(artistId);
    QString res = p->object.callObjectMethod(__FUNCTION__, "(Ljava/lang/String;)Ljava/lang/String;", jartistId.object<jstring>()).toString();
    return res;
}

QString AsemanAndroidMultimedia::getAlbumSongs(const QString &albumId)
{
    QAndroidJniObject jalbumId = QAndroidJniObject::fromString(albumId);
    QString res = p->object.callObjectMethod(__FUNCTION__, "(Ljava/lang/String;)Ljava/lang/String;", jalbumId.object<jstring>()).toString();
    return res;
}

void AsemanAndroidMultimedia::setImplemented(bool stt)
{
    jboolean jstt = stt;
    p->object.callMethod<jboolean>(__FUNCTION__, "(Z)Z", jstt);
}

AsemanAndroidMultimedia::~AsemanAndroidMultimedia()
{
    android_multimedia_objects.remove(this);
    delete p;
}

bool aseman_jlayer_registerNativeMethods() {
    if(aseman_jlayer_native_methods_registered)
        return true;

    QAndroidJniObject javaClass("io/aseman/android/AsemanMultimedia");
    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());

    env->DeleteLocalRef(objectClass);
    return true;
}
