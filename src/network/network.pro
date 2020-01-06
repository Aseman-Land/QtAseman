load(qt_build_config)

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

TARGET = QtAsemanNetwork
QT = core network asemancore asemangui

MODULE = asemannetwork

load(qt_module)

DEFINES += LIBQTASEMAN_NETWORK_LIBRARY

HEADERS += \
    $$PWD/asemandownloader.h \
    $$PWD/asemanfiledownloaderqueue.h \
    $$PWD/asemanfiledownloaderqueueitem.h \
    $$PWD/asemanhostchecker.h \
    $$PWD/asemannetworkmanager.h \
    $$PWD/asemannetworkmanageritem.h \
    $$PWD/asemannetworkproxy.h \
    $$PWD/asemannetworksleepmanager.h \
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
    $$PWD/asemannetworkmanager.cpp \
    $$PWD/asemannetworkmanageritem.cpp \
    $$PWD/asemannetworkproxy.cpp \
    $$PWD/asemannetworksleepmanager.cpp \
    $$PWD/asemansocketinterface.cpp \
    $$PWD/asemannetworkrequestobject.cpp \
    $$PWD/asemannetworkrequestmanager.cpp \
    $$PWD/asemannetworkrequestreply.cpp
