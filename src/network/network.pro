load(qt_build_config)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = QAsemanNetwork
QT = core network asemancore asemangui asemanqml qml

MODULE = asemannetwork

load(qt_module)

DEFINES += LIBQTASEMAN_NETWORK_LIBRARY

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
    $$PWD/asemannetworkrequestreply.cpp

!wasm {
    HEADERS += \
        $$PWD/asemannetworkmanager.h \
        $$PWD/asemannetworksleepmanager.h \
        $$PWD/asemannetworkmanageritem.h

    SOURCES += \
        $$PWD/asemannetworkmanager.cpp \
        $$PWD/asemannetworksleepmanager.cpp \
        $$PWD/asemannetworkmanageritem.cpp
}
