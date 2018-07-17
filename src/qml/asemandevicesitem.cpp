#include "asemandevicesitem.h"
#include "asemandesktoptools.h"

#ifdef Q_OS_ANDROID
#include "asemanjavalayer.h"
#endif

class AsemanDevicesItemPrivate
{
public:
#ifdef Q_OS_ANDROID
    AsemanJavaLayer *java_layer;
#endif
};

AsemanDevicesItem::AsemanDevicesItem(QObject *parent) :
    AsemanDevices(parent)
{
    p = new AsemanDevicesItemPrivate;
#ifdef Q_OS_ANDROID
    p->java_layer = AsemanJavaLayer::instance();
    connect( p->java_layer, &AsemanJavaLayer::incomingImage, this, &AsemanDevicesItem::incoming_image, Qt::QueuedConnection );
    connect( p->java_layer, &AsemanJavaLayer::selectImageResult, this, &AsemanDevicesItem::select_image_result, Qt::QueuedConnection );
#endif
}

bool AsemanDevicesItem::getOpenPictures()
{
#ifdef Q_OS_ANDROID
    return p->java_layer->getOpenPictures();
#else
    QString path = AsemanDesktopTools::getOpenFileName();
    if(path.isEmpty())
        return false;

    Q_EMIT selectImageResult(path);
    return true;
#endif
}

void AsemanDevicesItem::incoming_image(const QString &path)
{
    Q_EMIT incomingImage(path);
}

void AsemanDevicesItem::select_image_result(const QString &path)
{
    Q_EMIT selectImageResult(path);
}

AsemanDevicesItem::~AsemanDevicesItem()
{
    delete p;
}
