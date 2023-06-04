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

#define LINUX_DEFAULT_DPI 96
#define WINDOWS_DEFAULT_DPI 96
#define UTOUCH_DEFAULT_DPI 76

#define TABLET_RATIO 1.28
#define FONT_RATIO 1.28

#include "asemandevices.h"
#include "asemanapplication.h"
#include "asemanmimedata.h"

#ifdef Q_OS_ANDROID
#include "asemanjavalayer.h"
#endif
#ifdef Q_OS_IOS
#include "asemanobjectiveclayer.h"
#endif

#ifdef Q_OS_MACX
#include <IOKit/IOKitLib.h>
#include "asemanmacmanager.h"
#endif

#include <QTimerEvent>
#include <QGuiApplication>
#include <QMimeType>
#include <QMimeDatabase>
#include <QUrl>
#include <QDesktopServices>
#include <QDir>
#include <QImageWriter>
#include <QFileInfo>
#include <QFile>
#include <QClipboard>
#include <QtCore/qmath.h>
#include <QScreen>
#include <QDateTime>
#include <QDebug>
#include <QMimeData>
#include <QProcess>
#include <QGuiApplication>
#include <QCryptographicHash>
#include <QTimer>
#include <QVariantMap>
#include <QSysInfo>
#include <QJsonDocument>
#include <QThread>
#include <QStandardPaths>
#include <QInputMethodQueryEvent>

#ifdef ASEMAN_MULTIMEDIA
#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
#include <QBuffer>
#include <QCameraInfo>
#endif
#endif

class AsemanDevicesPrivate
{
public:
    int hide_keyboard_timer;
    bool keyboard_stt;

    QMimeDatabase mime_db;

#ifdef Q_OS_ANDROID
    AsemanJavaLayer *java_layer;
    qint32 androidKeyboardHeight;
#endif
#ifdef Q_OS_IOS
    AsemanObjectiveCLayer *objc_layer;
#endif
#ifdef Q_OS_MACX
    AsemanMacManager *mac_layer;
#endif

    bool transparentStatusBar;
    bool transparentNavigationBar;

    static QHash<int, bool> flags;
    static qreal fontScale;
    static QSet<AsemanDevices*> devicesObjs;
};

QHash<int, bool> AsemanDevicesPrivate::flags;
qreal AsemanDevicesPrivate::fontScale = 1;
QSet<AsemanDevices*> AsemanDevicesPrivate::devicesObjs;

AsemanDevices::AsemanDevices(QObject *parent) :
    QObject(parent)
{
    p = new AsemanDevicesPrivate;
    p->hide_keyboard_timer = 0;
    p->keyboard_stt = false;
    p->transparentStatusBar = false;
    p->transparentNavigationBar = false;

    refreshTransparentStatusBar();
    refreshTransparentNavigationBar();

#ifdef Q_OS_ANDROID
    p->androidKeyboardHeight = 0;
    p->java_layer = AsemanJavaLayer::instance();

    connect( p->java_layer, &AsemanJavaLayer::incomingShare, this, &AsemanDevices::incoming_share, Qt::QueuedConnection );
    connect( p->java_layer, &AsemanJavaLayer::incomingImage, this, &AsemanDevices::incomingImage, Qt::QueuedConnection );
    connect( p->java_layer, &AsemanJavaLayer::deepLinkReceived, this, &AsemanDevices::deepLinkReceived, Qt::QueuedConnection);
    connect( p->java_layer, &AsemanJavaLayer::selectImageResult, this, &AsemanDevices::selectImageResult, Qt::QueuedConnection );
    connect( p->java_layer, &AsemanJavaLayer::activityPaused, this, &AsemanDevices::activity_paused, Qt::QueuedConnection );
    connect( p->java_layer, &AsemanJavaLayer::activityResumed, this, &AsemanDevices::activity_resumed, Qt::QueuedConnection );
    connect( p->java_layer, &AsemanJavaLayer::keyboardVisiblityChanged, this, [this](qint32 height){
        height = height/deviceDensity();
        if(p->androidKeyboardHeight == height)
            return;

        p->androidKeyboardHeight = height;
        Q_EMIT geometryChanged();
    });
#endif
#ifdef Q_OS_IOS
   p->objc_layer = new AsemanObjectiveCLayer(this);
   connect(p->objc_layer, &AsemanObjectiveCLayer::keyboardHeightChanged, this, &AsemanDevices::keyboard_changed);
   connect(p->objc_layer, &AsemanObjectiveCLayer::deepLinkReceived, this, &AsemanDevices::deepLinkReceived);

   QTimer *intervalChecks = new QTimer(this);
   intervalChecks->setInterval(1000);
   intervalChecks->setSingleShot(false);
   intervalChecks->connect(intervalChecks, &QTimer::timeout, this, [this](){
       static qreal lastStatusBarHeight = AsemanObjectiveCLayer::statusBarHeight();
       qreal newStatusBarHeight = AsemanObjectiveCLayer::statusBarHeight();
       if (lastStatusBarHeight == newStatusBarHeight)
           return;

       lastStatusBarHeight = newStatusBarHeight;
       Q_EMIT statusBarHeightChanged();
   });
   intervalChecks->start();
#endif
#ifdef Q_OS_MACX
   p->mac_layer = new AsemanMacManager(this);
   connect(p->mac_layer, &AsemanMacManager::deepLinkReceived, this, &AsemanDevices::deepLinkReceived);
#endif

    connect( QGuiApplication::inputMethod(), &QInputMethod::visibleChanged, this, &AsemanDevices::keyboard_changed);
    connect( static_cast<QGuiApplication*>(QCoreApplication::instance())->clipboard(), &QClipboard::dataChanged, this, &AsemanDevices::clipboardChanged);

    QScreen *scr = screen();
    if( scr )
        connect( scr, &QScreen::geometryChanged, this, &AsemanDevices::geometryChanged);

    AsemanDevicesPrivate::devicesObjs.insert(this);
}

bool AsemanDevices::isMobile()
{
    return isTouchDevice() && !isTablet();
}

bool AsemanDevices::isTablet()
{
#ifdef Q_OS_ANDROID
    return isTouchDevice() && AsemanJavaLayer::instance()->isTablet();
#else
    return isTouchDevice() && lcdPhysicalSize() >= 6;
#endif
}

bool AsemanDevices::isLargeTablet()
{
#ifdef Q_OS_ANDROID
    return isTablet() && AsemanJavaLayer::instance()->getSizeName() == 3;
#else
    return isTouchDevice() && lcdPhysicalSize() >= 9;
#endif
}

bool AsemanDevices::isTouchDevice()
{
    return isAndroid() || isIOS() || isWindowsPhone() || isUbuntuTouch();
}

bool AsemanDevices::isDesktop()
{
    return !isTouchDevice();
}

bool AsemanDevices::isMacX()
{
#ifdef Q_OS_MACX
    return true;
#else
    return false;
#endif
}

bool AsemanDevices::isWindows()
{
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}

bool AsemanDevices::isLinux()
{
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
    return true;
#else
    return false;
#endif
}

bool AsemanDevices::isAndroid()
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

bool AsemanDevices::isIOS()
{
#ifdef Q_OS_IOS
    return true;
#else
    return false;
#endif
}

bool AsemanDevices::isUbuntuTouch()
{
#ifdef Q_OS_UBUNTUTOUCH
    return true;
#else
    return false;
#endif
}

bool AsemanDevices::isWindowsPhone()
{
#ifdef Q_OS_WINPHONE
    return true;
#else
    return false;
#endif
}

bool AsemanDevices::isWindows8()
{
#ifdef Q_OS_WIN
    return QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS8 ||
           QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS8_1;
#else
    return false;
#endif
}

bool AsemanDevices::isWebAssembly()
{
#ifdef Q_OS_WASM
    return true;
#else
    return false;
#endif
}

bool AsemanDevices::isQt6()
{
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    return true;
#else
    return false;
#endif
}

QScreen *AsemanDevices::screen()
{
    const QList<QScreen*> & screens = QGuiApplication::screens();
    if( screens.isEmpty() )
        return 0;

    return screens.first();
}

QObject *AsemanDevices::screenObj() const
{
    return screen();
}

qreal AsemanDevices::lcdPhysicalSize()
{
    qreal w = lcdPhysicalWidth();
    qreal h = lcdPhysicalHeight();

    return qSqrt( h*h + w*w );
}

qreal AsemanDevices::lcdPhysicalWidth()
{
    if( QGuiApplication::screens().isEmpty() )
        return 0;

    return (qreal)screenSize().width()/lcdDpiX();
}

qreal AsemanDevices::lcdPhysicalHeight()
{
    if( QGuiApplication::screens().isEmpty() )
        return 0;

    return (qreal)screenSize().height()/lcdDpiY();
}

qreal AsemanDevices::lcdDpiX()
{
#ifdef Q_OS_ANDROID
    return AsemanJavaLayer::instance()->densityDpi();
#else
    if( QGuiApplication::screens().isEmpty() )
        return 0;

    QScreen *scr = QGuiApplication::screens().first();
    return scr->physicalDotsPerInchX();
#endif
}

qreal AsemanDevices::lcdDpiY()
{
#ifdef Q_OS_ANDROID
    return AsemanJavaLayer::instance()->densityDpi();
#else
    if( QGuiApplication::screens().isEmpty() )
        return 0;

    QScreen *scr = QGuiApplication::screens().first();
    return scr->physicalDotsPerInchY();
#endif
}

QSize AsemanDevices::screenSize()
{
#ifdef Q_OS_ANDROID
    return QSize(AsemanJavaLayer::instance()->screenSizeWidth(),
                 AsemanJavaLayer::instance()->screenSizeHeight());
#else
    if( QGuiApplication::screens().isEmpty() )
        return QSize();

    QScreen *scr = QGuiApplication::screens().first();
    return scr->size();
#endif
}

qreal AsemanDevices::keyboardHeight() const
{
#ifdef Q_OS_ANDROID
    return p->androidKeyboardHeight*density();
#else
#ifdef Q_OS_UBUNTUTOUCH
    return screenSize().height()*0.5;
#else
#ifdef DESKTOP_DEVICE
    return 0;
#else
#ifdef Q_OS_IOS
    return p->objc_layer->keyboardHeight();
#else
    const QSize & scr_size = screenSize();
    bool portrait = scr_size.width()<scr_size.height();
    if( portrait )
    {
        if( isMobile() )
            return screenSize().height()*0.6;
        else
            return screenSize().height()*0.4;
    }
    else
    {
        if( isMobile() )
            return screenSize().height()*0.7;
        else
            return screenSize().height()*0.5;
    }
#endif
#endif
#endif
#endif
}

QString AsemanDevices::deviceName()
{
    if(isDesktop())
        return QSysInfo::prettyProductName() + " " + QSysInfo::currentCpuArchitecture();
#ifdef Q_OS_ANDROID
    else
        return AsemanJavaLayer::instance()->deviceName();
#else
    else
        return QStringLiteral("mobile");
#endif
}

QString AsemanDevices::deviceId()
{
#if defined(Q_OS_ANDROID)
    return AsemanJavaLayer::instance()->deviceId();
#elif defined(Q_OS_IOS)
    return AsemanObjectiveCLayer::deviceId();
#elif defined(Q_OS_MACX)
    io_registry_entry_t ioRegistryRoot = IORegistryEntryFromPath(kIOMasterPortDefault, "IOService:/");
    CFStringRef uuidCf = (CFStringRef) IORegistryEntryCreateCFProperty(ioRegistryRoot, CFSTR(kIOPlatformUUIDKey), kCFAllocatorDefault, 0);
    IOObjectRelease(ioRegistryRoot);
    char buf[128];
    CFStringGetCString(uuidCf, buf, sizeof(buf), kCFStringEncodingMacRoman);
    CFRelease(uuidCf);
    return QString::fromUtf8( QByteArray(buf, sizeof(buf)) );
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN32)
    static QString cg_hostId;
    if(!cg_hostId.isEmpty())
        return cg_hostId;

    QProcess prc;
#ifdef Q_OS_WIN
    prc.start(QStringLiteral("wmic"), {QStringLiteral("csproduct"), QStringLiteral("get"), QStringLiteral("UUID")});
#else
    prc.start(QStringLiteral("hostid"));
#endif
    prc.waitForStarted();
    prc.waitForReadyRead();
    prc.waitForFinished();

    cg_hostId = QString::fromUtf8(prc.readAll());
    cg_hostId = cg_hostId.remove(QStringLiteral("UUID")).trimmed();
    if(cg_hostId.isEmpty())
        cg_hostId = QStringLiteral("noid");
    return cg_hostId;
#else
    return QStringLiteral("noid");
#endif
}

QString AsemanDevices::deviceShortId()
{
    QString hash = QString::fromUtf8(QCryptographicHash::hash(deviceId().toUtf8(), QCryptographicHash::Md5).toHex());
    return hash.remove(QStringLiteral("-")).left(8);
}

QString AsemanDevices::platformVersion()
{
    return QSysInfo::productVersion();
}

QString AsemanDevices::platformType()
{
    return QSysInfo::productType();
}

QString AsemanDevices::platformName()
{
    return QSysInfo::prettyProductName();
}

QString AsemanDevices::platformKernel()
{
    return QSysInfo::kernelType();
}

QString AsemanDevices::platformKernelVersion()
{
    return QSysInfo::kernelVersion();
}

QString AsemanDevices::platformCpuArchitecture()
{
    return QSysInfo::currentCpuArchitecture();
}

QString AsemanDevices::qtVersion()
{
    return QStringLiteral(QT_VERSION_STR);
}

qreal AsemanDevices::qtMajorVersion()
{
    static qreal result = 0;
    if(result != 0.0)
        return result;

    const QString &qv = qtVersion();
    int idx0 = qv.indexOf(QStringLiteral("."));
    int idx1 = qv.indexOf(QStringLiteral("."), idx0+1);
    result = qv.left(idx1).toDouble();
    return result;
}

bool AsemanDevices::transparentStatusBar()
{
    return p->transparentStatusBar;
}

void AsemanDevices::setTransparentStatusBar(bool stt)
{
    if(p->transparentStatusBar == stt)
        return;

#ifdef Q_OS_ANDROID
    AsemanJavaLayer::instance()->setTransparentStatusBar(stt);
#else
    Q_UNUSED(stt)
#endif
    p->transparentStatusBar = stt;
    Q_EMIT transparentStatusBarChanged();

    QTimer::singleShot(100, this, [this](){
        refreshTransparentStatusBar();
        Q_EMIT statusBarHeightChanged();
    });
}

bool AsemanDevices::transparentNavigationBar()
{
    return p->transparentNavigationBar;
}

void AsemanDevices::setTransparentNavigationBar(bool stt)
{
    if(p->transparentNavigationBar == stt)
        return;

#ifdef Q_OS_ANDROID
    AsemanJavaLayer::instance()->setTransparentNavigationBar(stt);
#else
    Q_UNUSED(stt)
#endif
    p->transparentNavigationBar = stt;
    Q_EMIT transparentNavigationBarChanged();

    QTimer::singleShot(100, this, [this](){
        refreshTransparentNavigationBar();
        Q_EMIT navigationBarHeightChanged();
    });
}

qreal AsemanDevices::standardTitleBarHeight() const
{
    static qreal res = 0;
    if(res)
        return res;

    if(isDesktop())
        res = 54*density();
    else
    if(isMobile())
        res = 56*density();
    else
        res = 54*density();

    return res;
}

qreal AsemanDevices::statusBarHeight()
{
    if(!transparentStatusBar())
        return 0;

#ifdef Q_OS_IOS
    return AsemanObjectiveCLayer::statusBarHeight();
#else
    static qreal result = 0;
    if(result == 0.0)
    {
#ifdef Q_OS_ANDROID
        result = density()*(AsemanJavaLayer::instance()->statusBarHeight()/deviceDensity());
#else
        result = 20*density();
#endif
    }
    return result;
#endif
}

qreal AsemanDevices::navigationBarHeight()
{
    if(!transparentNavigationBar())
        return 0;

    static qreal result = 0;
    if(result == 0.0)
    {
#ifdef Q_OS_ANDROID
        result = density()*(AsemanJavaLayer::instance()->navigationBarHeight()/deviceDensity());
#else
#ifdef Q_OS_IOS
        result = AsemanObjectiveCLayer::navigationBarHeight();
#else
        result = 44*density();
#endif
#endif
    }
    return result;
}

void AsemanDevices::setFlag(int flag, bool state)
{
    AsemanDevicesPrivate::flags[flag] = state;
}

bool AsemanDevices::flag(int flag)
{
    return AsemanDevicesPrivate::flags.value(flag);
}

int AsemanDevices::densityDpi()
{
#ifdef Q_OS_ANDROID
    return AsemanJavaLayer::instance()->densityDpi();
#else
    return lcdDpiX();
#endif
}

qreal AsemanDevices::density()
{
    const bool disabled = AsemanDevices::flag(DisableDensities);
    if(AsemanDevices::flag(AsemanScaleFactorEnable))
        return qgetenv("ASEMAN_SCALE_FACTOR").toDouble();
    else
    if(disabled)
        return 1;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)) && !defined(Q_OS_IOS) && !defined (Q_OS_MAC)
    else
    if(QGuiApplication::testAttribute(Qt::AA_EnableHighDpiScaling))
        return deviceDensity()/screen()->devicePixelRatio();
#endif
    else
        return deviceDensity();
}

qreal AsemanDevices::deviceDensity()
{
#ifdef Q_OS_ANDROID
    qreal ratio = isTablet()? TABLET_RATIO : 1;
//    if( isLargeTablet() )
//        ratio = 1.6;

    return AsemanJavaLayer::instance()->density()*ratio;
#else
#ifdef Q_OS_IOS
    qreal ratio = isTablet()? TABLET_RATIO : 1;
    return ratio*densityDpi()/180.0;
#else
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
#ifdef Q_OS_UBUNTUTOUCH
    return screen()->logicalDotsPerInch()/UTOUCH_DEFAULT_DPI;
#else
    return screen()->logicalDotsPerInch()/LINUX_DEFAULT_DPI;
#endif
#else
#ifdef Q_OS_WIN32
    return 0.95*screen()->logicalDotsPerInch()/WINDOWS_DEFAULT_DPI;
#else
    return 1;
#endif
#endif
#endif
#endif
}

qreal AsemanDevices::fontDensity()
{
#ifdef Q_OS_ANDROID
    const qreal ratio = AsemanDevicesPrivate::fontScale*(isMobile()? FONT_RATIO*1.25 : FONT_RATIO*1.35);
    if(AsemanDevices::flag(AsemanScaleFactorEnable))
        return density()*ratio;
    else
    if(AsemanDevices::flag(DisableDensities))
        return ratio;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    else
    if(QGuiApplication::testAttribute(Qt::AA_EnableHighDpiScaling))
        return AsemanJavaLayer::instance()->density()*ratio/screen()->devicePixelRatio();
#endif
    else
        return AsemanJavaLayer::instance()->density()*ratio;
#else
#ifdef Q_OS_IOS
    return AsemanDevicesPrivate::fontScale * 1.4;
#else
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
#ifdef Q_OS_UBUNTUTOUCH
    qreal ratio = AsemanDevicesPrivate::fontScale * 1.3;
    return ratio*density();
#else
    qreal ratio = AsemanDevicesPrivate::fontScale * 1.4;
    return ratio*density();
#endif
#else
#ifdef Q_OS_WIN32
    qreal ratio = AsemanDevicesPrivate::fontScale * 1.4;
    return ratio*density();
#else
    qreal ratio = AsemanDevicesPrivate::fontScale * 1.3;
    return ratio*density();
#endif
#endif
#endif
#endif
}

void AsemanDevices::setFontScale(qreal fontScale)
{
    if(AsemanDevicesPrivate::fontScale == fontScale)
        return;

    AsemanDevicesPrivate::fontScale = fontScale;
    for(AsemanDevices *dvc: AsemanDevicesPrivate::devicesObjs)
    {
        Q_EMIT dvc->fontScaleChanged();
        Q_EMIT dvc->fontDensityChanged();
    }
}

qreal AsemanDevices::fontScale()
{
    return AsemanDevicesPrivate::fontScale;
}

bool AsemanDevices::cameraIsAvailable() const
{
#ifdef ASEMAN_MULTIMEDIA
#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
    return QCameraInfo::availableCameras().count();
#else
    return false;
#endif
#else
    return false;
#endif
}

QString AsemanDevices::localFilesPrePath()
{
#ifdef Q_OS_WIN
    return QStringLiteral("file:///");
#else
    return QStringLiteral("file://");
#endif
}

QString AsemanDevices::clipboard() const
{
    return QGuiApplication::clipboard()->text();
}

bool AsemanDevices::keyboard() const
{
    return p->keyboard_stt;
}

QList<QUrl> AsemanDevices::clipboardUrl() const
{
    return QGuiApplication::clipboard()->mimeData()->urls();
}

void AsemanDevices::setClipboardUrl(const QList<QUrl> &urls)
{
    QString data = QStringLiteral("copy");

    for( const QUrl &url: urls )
        data += QStringLiteral("\nfile://") + url.toLocalFile();

    QMimeData *mime = new QMimeData();
    mime->setUrls(urls);
    mime->setData( QStringLiteral("x-special/gnome-copied-files"), data.toUtf8() );

    QGuiApplication::clipboard()->setMimeData(mime);
}

QString AsemanDevices::cameraLocation()
{
    return AsemanApplication::cameraPath();
}

QString AsemanDevices::picturesLocation()
{
    QStringList probs;
    probs = QStandardPaths::standardLocations( QStandardPaths::PicturesLocation );

#ifdef Q_OS_ANDROID
    probs << "/sdcard/Pictures";
#else
#ifdef Q_OS_IOS
    probs << QStandardPaths::standardLocations(QStandardPaths::QStandardPaths::AppDataLocation).first() + "/Pictures";
#else
    probs << QDir::homePath() + "/Pictures";
#endif
#endif

    for(const QString & prob: probs)
        if( QFile::exists(prob) )
            return prob;

    return probs.last();
}

QString AsemanDevices::musicsLocation()
{
    QStringList probs;
    probs = QStandardPaths::standardLocations( QStandardPaths::MusicLocation );

#ifdef Q_OS_ANDROID
    probs << "/sdcard/Music";
#else
#ifdef Q_OS_IOS
    probs << QStandardPaths::standardLocations(QStandardPaths::QStandardPaths::AppDataLocation).first() + "/Music";
#else
    probs << QDir::homePath() + "/Music";
#endif
#endif

    for(const QString & prob: probs)
        if( QFile::exists(prob) )
            return prob;

    return probs.last();
}

QString AsemanDevices::documentsLocation()
{
    QStringList probs;
    probs = QStandardPaths::standardLocations( QStandardPaths::DocumentsLocation );

#ifdef Q_OS_ANDROID
    probs << "/sdcard/documents";
    probs << "/sdcard/Documents";
#else
#ifdef Q_OS_IOS
    probs << QStandardPaths::standardLocations(QStandardPaths::QStandardPaths::AppDataLocation).first() + "/Documents";
#else
    probs << QDir::homePath() + "/Documents";
#endif
#endif

    for(const QString & prob: probs)
        if( QFile::exists(prob) )
            return prob;

    return probs.last();
}

QString AsemanDevices::downloadsLocation()
{
    QStringList probs;
    probs = QStandardPaths::standardLocations( QStandardPaths::DownloadLocation );

#ifdef Q_OS_ANDROID
    probs << "/sdcard/downloads";
    probs << "/sdcard/Downloads";
#else
#ifdef Q_OS_IOS
    probs << QStandardPaths::standardLocations(QStandardPaths::QStandardPaths::AppDataLocation).first() + "/Downloads";
#else
    probs << QDir::homePath() + "/Downloads";
#endif
#endif

    for(const QString & prob: probs)
        if( QFile::exists(prob) )
            return prob;

    return probs.last();
}

QString AsemanDevices::resourcePath()
{
#ifdef Q_OS_ANDROID
    return "assets:";
#else
#ifndef Q_OS_MAC
    QString result = QCoreApplication::applicationDirPath() + "/../share/" + QCoreApplication::applicationName().toLower();
    QFileInfo file(result);
    if(file.exists() && file.isDir())
        return file.filePath();
    else
        return QCoreApplication::applicationDirPath() + "/";
#else
#ifdef Q_OS_IOS
    return QCoreApplication::applicationDirPath() + "/";
#else
    return QCoreApplication::applicationDirPath() + "/../Resources/";
#endif
#endif
#endif
}

QString AsemanDevices::resourcePathQml()
{
#ifdef Q_OS_ANDROID
    return resourcePath();
#else
    return localFilesPrePath() + resourcePath();
#endif
}

QString AsemanDevices::libsPath()
{
#ifndef Q_OS_MAC
    QString result = QCoreApplication::applicationDirPath() + "/../lib/" + QCoreApplication::applicationName().toLower();
    QFileInfo file(result);
    if(file.exists() && file.isDir())
        return file.filePath();
    else
        return QCoreApplication::applicationDirPath() + "/";
#else
#ifdef Q_OS_IOS
    return QCoreApplication::applicationDirPath() + "/";
#else
    return QCoreApplication::applicationDirPath() + "/../Resources/";
#endif
#endif
}

QVariantMap AsemanDevices::deviceDetails()
{
    QVariantMap map;
    map[QStringLiteral("device.name")] = AsemanDevices::deviceName();
    map[QStringLiteral("device.id")] = AsemanDevices::deviceId();
    map[QStringLiteral("device.shortId")] = AsemanDevices::deviceShortId();

    map[QStringLiteral("platform.version")] = AsemanDevices::platformVersion();
    map[QStringLiteral("platform.type")] = AsemanDevices::platformType();
    map[QStringLiteral("platform.name")] = AsemanDevices::platformName();
    map[QStringLiteral("platform.kernel")] = AsemanDevices::platformKernel();
    map[QStringLiteral("platform.kernelVersion")] = AsemanDevices::platformKernelVersion();
    map[QStringLiteral("platform.cpuArchitecture")] = AsemanDevices::platformCpuArchitecture();

    map[QStringLiteral("qt.version")] = AsemanDevices::qtVersion();
    map[QStringLiteral("qt.majorVersion")] = AsemanDevices::qtMajorVersion();

    map[QStringLiteral("screen.size")] = AsemanDevices::screenSize();
    map[QStringLiteral("screen.keyboardHeight")] = AsemanDevices::keyboardHeight();
    map[QStringLiteral("screen.density")] = AsemanDevices::density();
    map[QStringLiteral("screen.dpi")] = AsemanDevices::densityDpi();
    map[QStringLiteral("screen.deviceDensity")] = AsemanDevices::deviceDensity();
    map[QStringLiteral("screen.fontDensity")] = AsemanDevices::fontDensity();

    map[QStringLiteral("lcd.physicalSize")] = AsemanDevices::lcdPhysicalSize();
    map[QStringLiteral("lcd.physicalWidth")] = AsemanDevices::lcdPhysicalWidth();
    map[QStringLiteral("lcd.physicalHeight")] = AsemanDevices::lcdPhysicalHeight();
    map[QStringLiteral("lcd.dpiX")] = AsemanDevices::lcdDpiX();
    map[QStringLiteral("lcd.dpiY")] = AsemanDevices::lcdDpiY();

    map[QStringLiteral("os.mobile")] = AsemanDevices::isMobile();
    map[QStringLiteral("os.tablet")] = AsemanDevices::isTablet();
    map[QStringLiteral("os.largeTablet")] = AsemanDevices::isLargeTablet();
    map[QStringLiteral("os.touchDevice")] = AsemanDevices::isTouchDevice();
    map[QStringLiteral("os.desktop")] = AsemanDevices::isDesktop();
    map[QStringLiteral("os.macX")] = AsemanDevices::isMacX();
    map[QStringLiteral("os.windows")] = AsemanDevices::isWindows();
    map[QStringLiteral("os.linux")] = AsemanDevices::isLinux();
    map[QStringLiteral("os.android")] = AsemanDevices::isAndroid();
    map[QStringLiteral("os.iOS")] = AsemanDevices::isIOS();
    map[QStringLiteral("os.ubuntuTouch")] = AsemanDevices::isUbuntuTouch();
    map[QStringLiteral("os.windowsPhone")] = AsemanDevices::isWindowsPhone();
    map[QStringLiteral("os.windows8")] = AsemanDevices::isWindows8();

    map[QStringLiteral("ui.transparentStatusBar")] = AsemanDevices::transparentStatusBar();
    map[QStringLiteral("ui.transparentNavigationBar")] = AsemanDevices::transparentNavigationBar();
    map[QStringLiteral("ui.standardTitleBarHeight")] = AsemanDevices::standardTitleBarHeight();
    map[QStringLiteral("ui.statusBarHeight")] = AsemanDevices::statusBarHeight();
    map[QStringLiteral("ui.navigationBarHeight")] = AsemanDevices::navigationBarHeight();

    map[QStringLiteral("path.cameraLocation")] = AsemanDevices::cameraLocation();
    map[QStringLiteral("path.picturesLocation")] = AsemanDevices::picturesLocation();
    map[QStringLiteral("path.musicsLocation")] = AsemanDevices::musicsLocation();
    map[QStringLiteral("path.documentsLocation")] = AsemanDevices::downloadsLocation();
    map[QStringLiteral("path.resourcePath")] = AsemanDevices::resourcePath();
    map[QStringLiteral("path.resourcePathQml")] = AsemanDevices::resourcePathQml();
    map[QStringLiteral("path.libsPath")] = AsemanDevices::libsPath();

    map[QStringLiteral("app.path.homePath")] = AsemanApplication::homePath();
    map[QStringLiteral("app.path.startPath")] = AsemanApplication::startPath();
    map[QStringLiteral("app.path.appPath")] = AsemanApplication::appPath();
    map[QStringLiteral("app.path.appFilePath")] = AsemanApplication::appFilePath();
    map[QStringLiteral("app.path.confsPath")] = AsemanApplication::confsPath();
    map[QStringLiteral("app.path.tempPath")] = AsemanApplication::tempPath();
    map[QStringLiteral("app.path.backupsPath")] = AsemanApplication::backupsPath();
    map[QStringLiteral("app.path.cameraPath")] = AsemanApplication::cameraPath();
    map[QStringLiteral("app.path.dirPath")] = AsemanApplication::applicationDirPath();
    map[QStringLiteral("app.path.filePath")] = AsemanApplication::applicationFilePath();
    map[QStringLiteral("app.path.logPath")] = AsemanApplication::logPath();

    map[QStringLiteral("app.pid")] = AsemanApplication::applicationPid();
    map[QStringLiteral("app.organizationDomain")] = AsemanApplication::organizationDomain();
    map[QStringLiteral("app.organizationName")] = AsemanApplication::organizationName();
    map[QStringLiteral("app.name")] = AsemanApplication::applicationName();
    map[QStringLiteral("app.version")] = AsemanApplication::applicationVersion();
    map[QStringLiteral("app.displayName")] = AsemanApplication::applicationDisplayName();
    map[QStringLiteral("app.platformName")] = AsemanApplication::platformName();

    map[QStringLiteral("app.appType")] = AsemanApplication::appType();
    map[QStringLiteral("app.isDebug")] = AsemanApplication::isDebug();
    map[QStringLiteral("app.font")] = AsemanApplication::font();

    QMapIterator<QString, QVariant> i(map);
    while(i.hasNext())
    {
        i.next();
        if(i.key().left(5) != QStringLiteral("path.") && i.key().left(9) != QStringLiteral("app.path."))
            continue;

        QString path = i.value().toString();
        QFileInfo inf(path);

        map[i.key() + QStringLiteral(".exists")] = inf.exists();
        map[i.key() + QStringLiteral(".isDir")] = inf.isDir();
        map[i.key() + QStringLiteral(".isFile")] = inf.isFile();
        map[i.key() + QStringLiteral(".isWritable")] = inf.isWritable();
        map[i.key() + QStringLiteral(".isReadable")] = inf.isReadable();
        map[i.key() + QStringLiteral(".isExecutable")] = inf.isExecutable();
        map[i.key() + QStringLiteral(".isSymLink")] = inf.isSymLink();
    }

    return map;
}

bool AsemanDevices::hasBiometric()
{
#if defined(Q_OS_IOS)
    return p->objc_layer->hasBiometric();
#elif defined(Q_OS_MACOS)
    return AsemanMacManager::hasBiometric();
#else
    return false;
#endif
}

bool AsemanDevices::biometricCheck()
{
#if defined(Q_OS_IOS)
    return p->objc_layer->biometricCheck();
#elif defined(Q_OS_MACOS)
    return AsemanMacManager::biometricCheck();
#else
    return false;
#endif
}

QStringList AsemanDevices::getLastImages(qint32 offset, qint32 count)
{
#ifdef Q_OS_ANDROID
    return p->java_layer->getLastImages(offset, count).split(QStringLiteral("\n"), Qt::SkipEmptyParts);
#else
    return QStringList();
#endif
}

void AsemanDevices::setupImEventFilter(QObject *item)
{
    class ImFixer: public QObject {
    protected:
        bool eventFilter(QObject *obj, QEvent *event) override {
            if (event->type() == QEvent::InputMethodQuery) {
                QInputMethodQueryEvent *imEvt = static_cast<QInputMethodQueryEvent *>(event);
                if (imEvt->queries() == Qt::InputMethodQuery::ImCursorRectangle) {
                    imEvt->setValue(Qt::InputMethodQuery::ImCursorRectangle, QRectF());
                    return true;
                }
            }
            return QObject::eventFilter(obj, event);
        }
    };
    static thread_local ImFixer imf;
    item->installEventFilter(&imf);
}

void AsemanDevices::setupWindowColor(QColor color)
{
#ifdef Q_OS_MACX
    QTimer::singleShot(100, [color, this](){
        p->mac_layer->removeTitlebarFromWindow(color.redF(), color.greenF(), color.blueF());
    });
#else
    Q_UNUSED(color)
#endif
}

void AsemanDevices::hideKeyboard()
{
    if( p->hide_keyboard_timer )
        killTimer(p->hide_keyboard_timer);

    p->hide_keyboard_timer = startTimer(250);
}

void AsemanDevices::showKeyboard()
{
    if( p->hide_keyboard_timer )
    {
        killTimer(p->hide_keyboard_timer);
        p->hide_keyboard_timer = 0;
    }

    QGuiApplication::inputMethod()->show();
    p->keyboard_stt = true;

    Q_EMIT keyboardChanged();
}

void AsemanDevices::share(const QString &subject, const QString &message)
{
#ifdef Q_OS_ANDROID
    p->java_layer->sharePaper( subject, message );
#else
#ifdef Q_OS_IOS
    AsemanObjectiveCLayer::sharePaper((subject.length()? subject + '\n' : QString()) + message);
#else
    QString adrs = QStringLiteral("mailto:%1?subject=%2&body=%3").arg(QString(),subject,message);
    QDesktopServices::openUrl( adrs );
#endif
#endif
}

bool AsemanDevices::openFile(const QString &address)
{
#ifdef Q_OS_ANDROID
    const QMimeType & t = p->mime_db.mimeTypeForFile(address);
    return p->java_layer->openFile( address, t.name() );
#else
    return QDesktopServices::openUrl( QUrl(address) );
#endif
}

bool AsemanDevices::shareFile(const QString &address)
{
#ifdef Q_OS_ANDROID
    const QMimeType & t = p->mime_db.mimeTypeForFile(address);
    return p->java_layer->shareFile( address, t.name() );
#else
    return QDesktopServices::openUrl( QUrl(address) );
#endif
}

bool AsemanDevices::saveToGallery(const QString &filePath)
{
#ifdef Q_OS_IOS
    AsemanObjectiveCLayer::saveToCameraRoll(filePath);
#else
    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + QStringLiteral("/") + QCoreApplication::applicationName();
    QDir().mkpath(path);

    QImageWriter writer(path + "/" + filePath.mid(filePath.lastIndexOf(QStringLiteral("/"))+1));
    writer.write(QImage(filePath));
#endif
    return true;
}

void AsemanDevices::callNumber(const QString &number)
{
    Q_UNUSED(number)
#ifdef Q_OS_ANDROID
    p->java_layer->callNumber(number);
#else
#endif
}

void AsemanDevices::setClipboard(const QString &text)
{
    QGuiApplication::clipboard()->setText( text );
}

void AsemanDevices::setClipboardData(AsemanMimeData *mime)
{
    QMimeData *data = new QMimeData();
    if(mime)
    {
        data->setText(mime->text());
        data->setHtml(mime->html());
        data->setUrls(mime->urls());

        const QVariantMap &map = mime->dataMap();
        QMapIterator<QString,QVariant> i(map);
        while(i.hasNext())
        {
            i.next();
            QByteArray bytes;
            QDataStream stream(&bytes, QIODevice::WriteOnly);
            stream << i.value();

            data->setData(i.key(), bytes);
        }
    }
    QGuiApplication::clipboard()->setMimeData(data);
}

QString AsemanDevices::startCameraPicture()
{
#ifdef Q_OS_ANDROID
    QString output = cameraLocation() + "/aseman_" + QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch()) + ".jpg";
    if(!p->java_layer->startCamera(output))
        output.clear();

    return output;
#else
    return QString();
#endif
}

bool AsemanDevices::getOpenPictures()
{
#ifdef Q_OS_ANDROID
    return p->java_layer->getOpenPictures();
#else
    return false;
#endif
}

void AsemanDevices::triggerVibrateFeedback()
{
#ifdef Q_OS_IOS
    p->objc_layer->triggerVibrateFeedback();
#endif
}

QVariantList AsemanDevices::getContactList(std::function<void(const QVariantList &)> asyncCallback)
{
    QVariantList res;
#ifdef Q_OS_ANDROID
    if (asyncCallback)
    {
        class ContactThreaded: public QThread
        {
        protected:
            void run() {
                result = QJsonDocument::fromJson(AsemanJavaLayer::instance()->getContactList().toUtf8()).toVariant().toList();
            }

        public:
            ContactThreaded(QObject *parent = Q_NULLPTR): QThread(parent) {}
            virtual ~ContactThreaded() {}
            QVariantList result;
        };

        auto currentThread = QThread::currentThread();
        ContactThreaded *thread = new ContactThreaded;
        connect(thread, &ContactThreaded::finished, currentThread, [thread, asyncCallback](){
            asyncCallback(thread->result);
            thread->deleteLater();
        },  Qt::QueuedConnection);
        thread->start();

        return res;
    }
    else
        res = QJsonDocument::fromJson(AsemanJavaLayer::instance()->getContactList().toUtf8()).toVariant().toList();
#endif
#ifdef Q_OS_IOS
    if (asyncCallback)
        AsemanObjectiveCLayer::getContactList(asyncCallback);
    return res;
#endif

    if (asyncCallback)
        asyncCallback(res);

    return res;
}

void AsemanDevices::incoming_share(const QString &title, const QString &msg)
{
    Q_EMIT incomingShare(title,msg);
}

void AsemanDevices::activity_paused()
{
    Q_EMIT activityPaused();
}

void AsemanDevices::activity_resumed()
{
    Q_EMIT activityResumed();
}

void AsemanDevices::keyboard_changed()
{
    Q_EMIT keyboardChanged();
    Q_EMIT geometryChanged();
}

void AsemanDevices::timerEvent(QTimerEvent *e)
{
    if( e->timerId() == p->hide_keyboard_timer )
    {
        killTimer(p->hide_keyboard_timer);
        p->hide_keyboard_timer = 0;

        QGuiApplication::inputMethod()->hide();
        p->keyboard_stt = false;

        Q_EMIT keyboardChanged();
    }
}

void AsemanDevices::refreshTransparentStatusBar()
{
#ifdef Q_OS_ANDROID
    p->transparentStatusBar = AsemanJavaLayer::instance()->transparentStatusBar();
#else
#ifdef Q_OS_IOS
    p->transparentStatusBar = true;
#else
    p->transparentStatusBar = false;
#endif
#endif
}

void AsemanDevices::refreshTransparentNavigationBar()
{
#ifdef Q_OS_ANDROID
    p->transparentNavigationBar = AsemanJavaLayer::instance()->transparentNavigationBar();
#else
#ifdef Q_OS_IOS
    p->transparentNavigationBar = (AsemanObjectiveCLayer::navigationBarHeight() > 0.1);
#else
    p->transparentNavigationBar = false;
#endif
#endif
}

AsemanDevices::~AsemanDevices()
{
    AsemanDevicesPrivate::devicesObjs.remove(this);
    delete p;
}
