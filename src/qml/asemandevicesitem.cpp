#include "asemandevicesitem.h"
#include "asemandesktoptools.h"
#include "asemanapplicationitem.h"

#include <QQmlEngine>
#include <QMimeDatabase>
#include <QTimer>

#if defined(QT_WIDGETS_LIB)
#include <QFileDialog>
#include <QStandardPaths>
#include <asemantools.h>
#endif

#ifdef Q_OS_IOS
#include "private/quickios/qiimagepicker.h"
#include "private/quickios/quickios.h"
#endif

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
#ifdef Q_OS_IOS
    QuickIOS::registerTypes();
#endif
}

bool AsemanDevicesItem::getOpenPictures()
{
    QString path;

#if defined(Q_OS_ANDROID)
    p->java_layer->getOpenPictures();
    return true;
#elif defined(Q_OS_IOS)
    auto picker = new QIImagePicker(this);

    connect(picker, &QIImagePicker::referenceUrlChanged, this, [picker](){
        QString tempPath = AsemanApplication::tempPath() + '/' + QUuid::createUuid().toString(QUuid::WithoutBraces);
        if (picker->referenceUrl().toLower().contains(QStringLiteral("png")))
            tempPath += QStringLiteral(".png");
        else
            tempPath += QStringLiteral(".jpg");

        picker->save(tempPath);
    });
    connect(picker, &QIImagePicker::saved, this, [this, picker](QString url){
        url = AsemanTools::urlToLocalPath(url);
        Q_EMIT selectImageResult(url);
        picker->close();
        QTimer::singleShot(1000, picker, &QIImagePicker::deleteLater);
    });

    picker->show();
    return true;
#else
#if defined(QT_WIDGETS_LIB)
    path = QFileDialog::getOpenFileName(Q_NULLPTR, QStringLiteral(""), QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).last());
#else
    path = AsemanDesktopTools::getOpenFileName();
#endif

    if(path.isEmpty())
        return false;

    Q_EMIT selectImageResult(path);
    return true;
#endif
}

QVariantList AsemanDevicesItem::getContactList(QJSValue asyncCallback)
{
    return AsemanDevices::getContactList([this, asyncCallback](const QVariantList &res){
        if (!asyncCallback.isCallable())
            return;

        QQmlEngine *engine = qmlEngine(this);

        if(!engine)
            return;

        QJSValueList args = { engine->toScriptValue(res) };

        QJSValue callback = asyncCallback;
        callback.call(args);
    });
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
