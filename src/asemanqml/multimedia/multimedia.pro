TARGET  = asemanqmlmultimedia
TARGETPATH = AsemanQml/Multimedia
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += core gui network asemanqml asemangui asemancore

lessThan(QT_MAJOR_VERSION, 6): QT += asemanmultimedia

HEADERS += \
    $$PWD/asemanmultimediaplugin.h \
    $$PWD/asemanqttoolsitemmultimedia.h

SOURCES += \
    $$PWD/asemanmultimediaplugin.cpp \
    $$PWD/asemanqttoolsitemmultimedia.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Multimedia/*.*) $$PWD/Multimedia/qmldir

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES

asemanmultimedia.files = $$INCLUDED_RESOURCE_FILES
asemanmultimedia.prefix = /AsemanQml/
RESOURCES += asemanmultimedia

load(qml_plugin)

