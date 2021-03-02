TARGET  = asemanqmlsql
TARGETPATH = AsemanQml/Sql
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += core gui asemanqml asemangui asemancore asemansql

qtHaveModule(sql): SUBDIRS += sql

HEADERS += \
    $$PWD/asemansqlplugin.h \
    $$PWD/asemanqttoolsitemsql.h \
    $$PWD/asemanquicksqlobject.h

SOURCES += \
    $$PWD/asemansqlplugin.cpp \
    $$PWD/asemanqttoolsitemsql.cpp \
    $$PWD/asemanquicksqlobject.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

load(qml_plugin)

