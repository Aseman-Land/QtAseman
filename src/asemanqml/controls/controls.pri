INCLUDEPATH += $$PWD
QT += qml core gui 

HEADERS += \
    $$PWD/controlsplugin.h \
    $$PWD/asemanqttoolsitemcontrols.h

SOURCES += \
    $$PWD/controlsplugin.cpp \
    $$PWD/asemanqttoolsitemcontrols.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES = $$files($$PWD/Controls/*.*) $$PWD/Controls/qmldir
ASEMAN_QML_PRIVATES = $$files($$PWD/Controls/private/*)
ASEMAN_QML_RESOURCES = $$files($$PWD/Controls/files/*)

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES \
    $$ASEMAN_QML_PRIVATES \
    $$ASEMAN_QML_RESOURCES

asemancontrols.files = $$INCLUDED_RESOURCE_FILES
asemancontrols.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemancontrols.qrc
} else {
    RESOURCES += asemancontrols
}
