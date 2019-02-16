TARGET  = asemanqmlwidgets
TARGETPATH = AsemanQml/Widgets
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += core gui network asemanqml asemangui asemancore asemanwidgets

HEADERS += \
    $$PWD/asemanwidgetsplugin.h \
    $$PWD/asemanqttoolsitem.h

SOURCES += \
    $$PWD/asemanwidgetsplugin.cpp \
    $$PWD/asemanqttoolsitem.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

load(qml_plugin)

