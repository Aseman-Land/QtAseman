TARGET  = asemanqmlviewport
TARGETPATH = AsemanQml/Viewport
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += core gui network asemanqml asemangui asemancore

HEADERS += \
    $$PWD/asemanviewportplugin.h \
    $$PWD/asemanqttoolsitemviewport.h \
    $$PWD/asemanviewport.h \
    $$PWD/asemanviewportcontroller.h \
    $$PWD/asemanviewportcontrollerroute.h \
    $$PWD/asemanviewportitem.h

SOURCES += \
    $$PWD/asemanviewportplugin.cpp \
    $$PWD/asemanqttoolsitemviewport.cpp \
    $$PWD/asemanviewport.cpp \
    $$PWD/asemanviewportcontroller.cpp \
    $$PWD/asemanviewportcontrollerroute.cpp \
    $$PWD/asemanviewportitem.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Viewport/*.*) $$PWD/Viewport/qmldir

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES

asemanviewport.files = $$INCLUDED_RESOURCE_FILES
asemanviewport.prefix = /AsemanQml/
RESOURCES += asemanviewport

load(qml_plugin)

