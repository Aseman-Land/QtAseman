INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

static: DEFINES += ASEMAN_STATIC_BUILD

HEADERS += \
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
    $$PWD/asemankeyhandler.h \
    $$PWD/asemanglobaltranslations.h

SOURCES += \
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
    $$PWD/asemankeyhandler.cpp \
    $$PWD/asemanglobaltranslations.cpp

android: {
    QT += androidextras
    SOURCES += \
        $$PWD/asemanjavalayer.cpp
    HEADERS += \
        $$PWD/asemanjavalayer.h
}

ios {
    SOURCES += \
        $$PWD/asemanobjectiveclayer.mm
    HEADERS += \
        $$PWD/asemanobjectiveclayer.h

    disable-ios-contacts-support {
        DEFINES += DISABLE_IOS_CONTACTS_SUPPORT
    } else {
        LIBS +=  -framework Contacts -lobjc
    }
}
