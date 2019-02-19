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

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Controls/*.*) $$PWD/Controls/qmldir
ASEMAN_QML_PRIVATES += $$files($$PWD/Controls/private/*)
ASEMAN_QML_RESOURCES += $$files($$PWD/Controls/files/*)

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES \
    $$ASEMAN_QML_PRIVATES \
    $$ASEMAN_QML_RESOURCES

asemancontrols.files = $$INCLUDED_RESOURCE_FILES
asemancontrols.prefix = /AsemanQml/
RESOURCES += asemancontrols

load(qml_plugin)
