INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core positioning

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

