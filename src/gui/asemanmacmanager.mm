#include "asemanmacmanager.h"

#include <QDebug>

#ifdef NONBLOCK_BIOMETRIC_METHOD
#include <QEventLoop>
#else
#include <QSemaphore>
#endif

#import <LocalAuthentication/LocalAuthentication.h>
#include <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject<NSApplicationDelegate>
@end

class AsemanMacManager::Private
{
public:
    AppDelegate *appDelegate;
    static QSet<AsemanMacManager*> objects;
};
QSet<AsemanMacManager*> AsemanMacManager::Private::objects;

@implementation AppDelegate

- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls {
    for (NSURL *url in urls) {
        // Handle the deep link URL here
        QString str = QString::fromNSString(url.absoluteString);

        for (auto o: AsemanMacManager::Private::objects)
            QMetaObject::invokeMethod(o, "deepLinkReceived", Qt::QueuedConnection, Q_ARG(QString, str));

        qDebug() << "Received deep link:" << str;
    }
}

@end

AsemanMacManager::AsemanMacManager(QObject *parent)
    : QObject(parent)
{
    Private::objects.insert(this);

    p = new Private;
    p->appDelegate = [[AppDelegate alloc] init];
    [[NSApplication sharedApplication] setDelegate:p->appDelegate];
}

AsemanMacManager::~AsemanMacManager()
{
    Private::objects.remove(this);
    delete p;
}

void AsemanMacManager::removeTitlebarFromWindow(double r, double g, double b)
{
    QWindowList windows = QGuiApplication::allWindows();
    QWindow* win = windows.first();
    long winId = win->winId();

    auto nativeView = reinterpret_cast<NSView *>(winId);
    auto nativeWindow = [nativeView window];

    nativeWindow.titlebarAppearsTransparent=YES;
    nativeWindow.titleVisibility = NSWindowTitleHidden;

    auto color = [NSColor colorWithRed:r green:g blue:b alpha:1.0f];
    nativeWindow.backgroundColor = color;

    [nativeWindow setStyleMask:[nativeWindow styleMask] | NSWindowTitleHidden];
    [nativeWindow setTitlebarAppearsTransparent:YES];
}

bool AsemanMacManager::hasBiometric()
{
    LAContext *context = [[LAContext alloc] init];
    NSError *error = nil;

    if ([context canEvaluatePolicy:LAPolicyDeviceOwnerAuthenticationWithBiometrics error:&error]) {
        return true;
    } else {
        return false;
    }
}

bool AsemanMacManager::biometricCheck()
{
    LAContext *context = [[LAContext alloc] init];
    NSError *error = nil;

    if (![context canEvaluatePolicy:LAPolicyDeviceOwnerAuthenticationWithBiometrics error:&error])
        return false;

    auto res = new bool;
#ifdef NONBLOCK_BIOMETRIC_METHOD
    auto loop = new QEventLoop;
#else
    auto semaphore = new QSemaphore;
#endif
    [context evaluatePolicy:LAPolicyDeviceOwnerAuthenticationWithBiometrics
              localizedReason:@"Authenticate with Touch ID"
                        reply:^(BOOL success, NSError *error) {
        if (success) {
            *res = true;
        } else {
            *res = false;
        }
#ifdef NONBLOCK_BIOMETRIC_METHOD
        loop->exit();
#else
        semaphore->release(1);
#endif
    }];

#ifdef NONBLOCK_BIOMETRIC_METHOD
    loop->exec();
    delete loop;
#else
    semaphore->acquire(1);
    delete semaphore;
#endif
    auto r = *res;
    delete res;
    return r;
}
