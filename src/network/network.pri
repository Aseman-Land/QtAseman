INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core network qml

greaterThan(QT_MAJOR_VERSION, 5): DEFINES += ASEMAN_QT6

HEADERS += \
    $$PWD/asemandownloader.h \
    $$PWD/asemanfiledownloaderqueue.h \
    $$PWD/asemanfiledownloaderqueueitem.h \
    $$PWD/asemanhostchecker.h \
    $$PWD/asemannetworkproxy.h \
    $$PWD/asemannetwork_global.h \
    $$PWD/asemansocketinterface.h \
    $$PWD/asemannetworkrequestobject.h \
    $$PWD/asemannetworkrequestmanager.h \
    $$PWD/asemannetworkquickobject.h \
    $$PWD/asemannetworkrequestreply.h

SOURCES += \
    $$PWD/asemandownloader.cpp \
    $$PWD/asemanfiledownloaderqueue.cpp \
    $$PWD/asemanfiledownloaderqueueitem.cpp \
    $$PWD/asemanhostchecker.cpp \
    $$PWD/asemannetworkproxy.cpp \
    $$PWD/asemansocketinterface.cpp \
    $$PWD/asemannetworkrequestobject.cpp \
    $$PWD/asemannetworkrequestmanager.cpp \
    $$PWD/asemannetworkquickobject.cpp \
    $$PWD/asemannetworkrequestreply.cpp

!wasm: lessThan(QT_MAJOR_VERSION, 6) {
    HEADERS += \
        $$PWD/asemannetworkmanager.h \
        $$PWD/asemannetworksleepmanager.h \
        $$PWD/asemannetworkmanageritem.h

    SOURCES += \
        $$PWD/asemannetworkmanager.cpp \
        $$PWD/asemannetworksleepmanager.cpp \
        $$PWD/asemannetworkmanageritem.cpp
}
