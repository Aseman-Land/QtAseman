INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT += core gui

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
    lessThan(QT_MAJOR_VERSION, 6) QT += androidextras
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

    LIBS += -framework SafariServices -lobjc
    LIBS += -framework LocalAuthentication
    disable-ios-contacts-support {
        DEFINES += DISABLE_IOS_CONTACTS_SUPPORT
    } else {
        LIBS += -framework Contacts
    }
}

macx {
    HEADERS += \
        $$PWD/asemanmacmanager.h
    SOURCES += \
        $$PWD/asemanmacmanager.mm
    LIBS += -framework LocalAuthentication
}
