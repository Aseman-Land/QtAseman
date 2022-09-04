INCLUDEPATH += $$PWD
QT += core gui network

HEADERS += \
    $$PWD/asemannetworkplugin.h \
    $$PWD/asemanqttoolsitemnetwork.h

SOURCES += \
    $$PWD/asemannetworkplugin.cpp \
    $$PWD/asemanqttoolsitemnetwork.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

