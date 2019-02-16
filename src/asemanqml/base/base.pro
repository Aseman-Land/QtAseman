TARGET  = asemanqmlbase
TARGETPATH = AsemanQml/Base
IMPORT_VERSION = 2.0
VERSION_REVISION = 2

INCLUDEPATH += $$PWD
QT += core gui network asemanqml asemangui asemancore asemannetwork asemanwidgets

HEADERS += \
    $$PWD/asemanqmlplugin.h \
    $$PWD/asemanqttoolsitem.h

SOURCES += \
    $$PWD/asemanqmlplugin.cpp \
    $$PWD/asemanqttoolsitem.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Base/*.*) $$PWD/Base/qmldir
ASEMAN_QML_PRIVATES += $$files($$PWD/Base/private/*)
ASEMAN_QML_RESOURCES += $$files($$PWD/Base/files/*)

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES \
    $$ASEMAN_QML_PRIVATES \
    $$ASEMAN_QML_RESOURCES

asemanqml.files = $$INCLUDED_RESOURCE_FILES
asemanqml.prefix = /AsemanQml/
RESOURCES += asemanqml

load(qml_plugin)
