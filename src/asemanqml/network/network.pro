TARGET  = asemanqmlnetwork
TARGETPATH = AsemanQml/Network
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += core gui network asemanqml asemangui asemancore asemannetwork

HEADERS += \
    $$PWD/asemannetworkplugin.h \
    $$PWD/asemanqttoolsitemnetwork.h

SOURCES += \
    $$PWD/asemannetworkplugin.cpp \
    $$PWD/asemanqttoolsitemnetwork.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

load(qml_plugin)

