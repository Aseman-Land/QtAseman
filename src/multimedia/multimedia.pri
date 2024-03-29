INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core multimedia

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
    lessThan(QT_MAJOR_VERSION, 6) QT += androidextras
    HEADERS += \
        $$PWD/private/asemanandroidcameracapturecore.h \
        $$PWD/asemanandroidmultimedia.h
    SOURCES += \
        $$PWD/private/asemanandroidcameracapturecore.cpp \
        $$PWD/asemanandroidmultimedia.cpp
}

