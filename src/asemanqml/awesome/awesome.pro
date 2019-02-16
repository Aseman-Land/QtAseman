TARGET  = asemanqmlawesome
TARGETPATH = AsemanQml/Awesome
IMPORT_VERSION = 2.0

QT += qml

HEADERS += \
    $$PWD/awesomeplugin.h

SOURCES += \
    $$PWD/awesomeplugin.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Awesome/*.*)

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES

asemanawesome.files = $$INCLUDED_RESOURCE_FILES
asemanawesome.prefix = /AsemanQml/
RESOURCES += asemanawesome

load(qml_plugin)
