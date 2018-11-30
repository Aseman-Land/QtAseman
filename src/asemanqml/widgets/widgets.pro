TARGET  = asemanqmlwidgets
TARGETPATH = AsemanQml/Widgets
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD $$PWD/../../core $$PWD/../../gui $$PWD/../../qml $$PWD/../../widgets
QT += core gui network asemanqml asemangui asemancore asemanwidgets

HEADERS += \
    $$PWD/asemanwidgetsplugin.h \
    $$PWD/asemanqttoolsitem.h

SOURCES += \
    $$PWD/asemanwidgetsplugin.cpp \
    $$PWD/asemanqttoolsitem.cpp

static: DEFINES += ASEMAN_STATIC_BUILD

ASEMAN_QML_FILES += $$files($$PWD/Widgets/*.*) $$PWD/Widgets/qmldir

INCLUDED_RESOURCE_FILES += \
    $$ASEMAN_QML_FILES

asemanwidgets.files = $$INCLUDED_RESOURCE_FILES
asemanwidgets.prefix = /AsemanQml/
RESOURCES += asemanwidgets

load(qml_plugin)

