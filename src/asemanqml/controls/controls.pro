TARGET  = asemanqmlcontrols
TARGETPATH = AsemanQml/Controls
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += qml core gui asemanqml asemancore

HEADERS += \
    $$PWD/controlsplugin.h \
    $$PWD/asemanqttoolsitem.h

SOURCES += \
    $$PWD/controlsplugin.cpp \
    $$PWD/asemanqttoolsitem.cpp

static: !linux: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Controls/*.*) $$PWD/Controls/qmldir

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES

asemancontrols.files = $$INCLUDED_RESOURCE_FILES
asemancontrols.prefix = /AsemanQml/
RESOURCES += asemancontrols

load(qml_plugin)
