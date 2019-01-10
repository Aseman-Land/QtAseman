load(qt_build_config)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = QtAsemanGeo
QT = core positioning asemancore

MODULE = asemangeo

load(qt_module)

DEFINES += LIBQTASEMAN_GEO_LIBRARY

HEADERS += \
    $$PWD/asemanlocationlistener.h \
    $$PWD/asemangeo_global.h \
    $$PWD/private/asemanabstractlocationlistenercore.h \
    $$PWD/private/asemanqtlocationlistenercore.h

SOURCES += \
    $$PWD/asemanlocationlistener.cpp \
    $$PWD/private/asemanabstractlocationlistenercore.cpp \
    $$PWD/private/asemanqtlocationlistenercore.cpp

android: {
    QT += androidextras
    HEADERS += \
        $$PWD/private/asemanandroidlocationlistenercore.h
    SOURCES += \
        $$PWD/private/asemanandroidlocationlistenercore.cpp
}

