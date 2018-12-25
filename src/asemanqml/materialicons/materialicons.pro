TARGET  = asemanqmlmaterialicons
TARGETPATH = AsemanQml/MaterialIcons
IMPORT_VERSION = 2.0

QT += qml

HEADERS += \
    $$PWD/materialiconsplugin.h

SOURCES += \
    $$PWD/materialiconsplugin.cpp

static: !linux: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/MaterialIcons/*.*)

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES

asemanmaterialicons.files = $$INCLUDED_RESOURCE_FILES
asemanmaterialicons.prefix = /AsemanQml/
RESOURCES += asemanmaterialicons

load(qml_plugin)
