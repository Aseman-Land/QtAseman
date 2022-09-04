INCLUDEPATH += $$PWD
QT += core gui network quick widgets

HEADERS += \
    $$PWD/asemanqmlplugin.h \
    $$PWD/asemanqttoolsitembase.h \
    $$PWD/asemandelegateswitch.h

SOURCES += \
    $$PWD/asemanqmlplugin.cpp \
    $$PWD/asemanqttoolsitembase.cpp \
    $$PWD/asemandelegateswitch.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES = $$files($$PWD/Base/*.*) $$PWD/Base/qmldir
ASEMAN_QML_PRIVATES = $$files($$PWD/Base/private/*)
ASEMAN_QML_RESOURCES = $$files($$PWD/Base/files/*)

INCLUDED_RESOURCE_FILES = \
    $$ASEMAN_QML_FILES \
    $$ASEMAN_QML_PRIVATES \
    $$ASEMAN_QML_RESOURCES

asemanqml.files = $$INCLUDED_RESOURCE_FILES
asemanqml.prefix = /AsemanQml/

contains(DEFINES, QT_ASEMAN_EMBEDDED) {
    RESOURCES += $$PWD/qmake_asemanqml.qrc
} else {
    RESOURCES += asemanqml
}
