INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core gui 
!android: !ios: {
    QT += widgets
    linux: QT += dbus
}

HEADERS += \
    $$PWD/asemandesktoptools.h \
    $$PWD/asemanfonthandler.h \
    $$PWD/asemantaskbarbutton.h \
    $$PWD/asemanwidgets_global.h \
    $$PWD/private/asemanabstracttaskbarbuttonengine.h \
    $$PWD/asemannotification.h


SOURCES += \
    $$PWD/asemandesktoptools.cpp \
    $$PWD/asemanfonthandler.cpp \
    $$PWD/asemantaskbarbutton.cpp \
    $$PWD/private/asemanabstracttaskbarbuttonengine.cpp \
    $$PWD/asemannotification.cpp

!android: !ios: {
    HEADERS += \
        $$PWD/asemansystemtray.h \
        $$PWD/asemannativenotificationitem.h \
        $$PWD/asemannativenotification.h
    SOURCES += \
        $$PWD/asemansystemtray.cpp \
        $$PWD/asemannativenotificationitem.cpp \
        $$PWD/asemannativenotification.cpp
}

macx {
    lessThan(QT_MAJOR_VERSION, 6) QT += macextras
    DEFINES += MAC_NATIVE_ASEMAN_NOTIFICATION
    SOURCES += \
        $$PWD/asemanmacnativenotification.cpp \
        $$PWD/private/asemanmactaskbarbuttonengine.cpp
    HEADERS += \
        $$PWD/asemanmacnativenotification.h \
        $$PWD/private/asemanmactaskbarbuttonengine.h
}
!android: linux|openbsd {
    DEFINES += LINUX_NATIVE_ASEMAN_NOTIFICATION
    SOURCES += \
        $$PWD/asemanlinuxnativenotification.cpp \
        $$PWD/private/asemanunitytaskbarbuttonengine.cpp \
        $$PWD/asemankdewallet.cpp
    HEADERS += \
        $$PWD/asemanlinuxnativenotification.h \
        $$PWD/private/asemanunitytaskbarbuttonengine.h \
        $$PWD/asemankdewallet.h
}
android {
    DEFINES += ANDROID_NATIVE_ASEMAN_NOTIFICATION
    HEADERS += \
        $$PWD/asemanandroidnativenotification.h
    SOURCES += \
        $$PWD/asemanandroidnativenotification.cpp
}
win {
    QT += winextras
    SOURCES += \
        $$PWD/private/asemanwintaskbarbuttonengine.cpp
    HEADERS += \
        $$PWD/private/asemanwintaskbarbuttonengine.h
}
