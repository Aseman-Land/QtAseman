TARGET  = asemanqmlviewport
TARGETPATH = AsemanQml/Viewport
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += core gui network asemanqml asemangui asemancore

HEADERS += \
    $$PWD/asemanviewportplugin.h \
    $$PWD/asemanqttoolsitemviewport.h

SOURCES += \
    $$PWD/asemanviewportplugin.cpp \
    $$PWD/asemanqttoolsitemviewport.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Viewport/*.*) $$PWD/Viewport/qmldir

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES

asemanviewport.files = $$INCLUDED_RESOURCE_FILES
asemanviewport.prefix = /AsemanQml/
RESOURCES += asemanviewport

load(qml_plugin)

