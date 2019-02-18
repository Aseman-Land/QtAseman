CONFIG += no_app_extension_api_only
load(qt_build_config)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = QtAsemanGui
QT = core gui asemancore

MODULE = asemangui

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
    asemankeyhandler.h

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
    asemankeyhandler.cpp

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
