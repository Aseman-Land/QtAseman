load(qt_build_config)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = QAsemanMultimedia
QT = core multimedia asemancore

MODULE = asemanmultimedia

load(qt_module)

DEFINES += LIBQTASEMAN_MULTIMEDIA_LIBRARY

HEADERS += \
    $$PWD/asemanaudioencodersettings.h \
    $$PWD/asemanaudiorecorder.h \
    $$PWD/asemancameracapture.h \
    $$PWD/asemanmultimedia_global.h \
    $$PWD/private/asemanabstractcameracapturecore.h \
    $$PWD/private/asemannullcameracapturecore.h \
    $$PWD/asemanmultimediadatabase.h

SOURCES += \
    $$PWD/asemanaudioencodersettings.cpp \
    $$PWD/asemanaudiorecorder.cpp \
    $$PWD/asemancameracapture.cpp \
    $$PWD/private/asemanabstractcameracapturecore.cpp \
    $$PWD/private/asemannullcameracapturecore.cpp \
    $$PWD/asemanmultimediadatabase.cpp

android: {
    QT += androidextras
    HEADERS += \
        $$PWD/private/asemanandroidcameracapturecore.h \
        $$PWD/asemanandroidmultimedia.h
    SOURCES += \
        $$PWD/private/asemanandroidcameracapturecore.cpp \
        $$PWD/asemanandroidmultimedia.cpp
}

