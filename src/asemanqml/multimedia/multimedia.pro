TARGET  = asemanqmlmultimedia
TARGETPATH = AsemanQml/Multimedia
IMPORT_VERSION = 2.0

QT += core gui network asemanqml asemangui asemancore asemanmultimedia

HEADERS += \
    $$PWD/asemanmultimediaplugin.h \
    $$PWD/asemanqttoolsitem.h

SOURCES += \
    $$PWD/asemanmultimediaplugin.cpp \
    $$PWD/asemanqttoolsitem.cpp

static: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Multimedia/*.*) $$PWD/Multimedia/qmldir

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES

asemanmultimedia.files = $$INCLUDED_RESOURCE_FILES
asemanmultimedia.prefix = /AsemanQml/
RESOURCES += asemanmultimedia

load(qml_plugin)

