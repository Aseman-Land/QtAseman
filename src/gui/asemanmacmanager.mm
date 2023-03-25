#include "asemanmacmanager.h"
#include <Cocoa/Cocoa.h>

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
