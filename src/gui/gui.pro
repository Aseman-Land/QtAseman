CONFIG += no_app_extension_api_only
load(qt_build_config)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = QtAsemanGui
QT = core gui asemancore

MODULE = asemangui

static: DEFINES += ASEMAN_STATIC_BUILD

load(qt_module)

DEFINES += LIBQTASEMAN_GUI_LIBRARY

HEADERS += \
    $$PWD/asemanabstractcolorfulllistmodel.h \
    $$PWD/asemanapplication.h \
    $$PWD/asemandevices.h \
    $$PWD/asemanimagecoloranalizor.h \
    $$PWD/asemanmimeapps.h \
    $$PWD/asemanmimedata.h \
    $$PWD/asemantexttools.h \
    $$PWD/asemantitlebarcolorgrabber.h \
    $$PWD/asemantools.h \
    $$PWD/asemantranslationmanager.h \
    $$PWD/asemanwindowdetails.h \
    $$PWD/asemangui_global.h \
    $$PWD/asemankeyhandler.h

SOURCES += \
    $$PWD/asemanabstractcolorfulllistmodel.cpp \
    $$PWD/asemanapplication.cpp \
    $$PWD/asemandevices.cpp \
    $$PWD/asemanimagecoloranalizor.cpp \
    $$PWD/asemanmimeapps.cpp \
    $$PWD/asemanmimedata.cpp \
    $$PWD/asemantexttools.cpp \
    $$PWD/asemantitlebarcolorgrabber.cpp \
    $$PWD/asemantools.cpp \
    $$PWD/asemantranslationmanager.cpp \
    $$PWD/asemanwindowdetails.cpp \
    $$PWD/asemankeyhandler.cpp

android: {
    QT += androidextras
    SOURCES += \
        $$PWD/asemanjavalayer.cpp
    HEADERS += \
        $$PWD/asemanjavalayer.h
}

ios: {
    SOURCES += \
        $$PWD/asemanobjectiveclayer.mm
    HEADERS += \
        $$PWD/asemanobjectiveclayer.h
}
