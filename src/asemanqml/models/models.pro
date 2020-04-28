TARGET  = asemanqmlmodels
TARGETPATH = AsemanQml/Models
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += core gui network asemanqml asemangui asemancore quick

HEADERS += \
    $$PWD/asemanmodelsplugin.h \
    $$PWD/asemanqttoolsitemmodels.h  \
    $$PWD/asemanquicklistmodel.h \
    $$PWD/asemanquicklistmodelsource.h \
    asemanabstractquicklistmodelhint.h \
    asemanquicklistmodelcopyhint.h

SOURCES += \
    $$PWD/asemanmodelsplugin.cpp \
    $$PWD/asemanqttoolsitemmodels.cpp  \
    $$PWD/asemanquicklistmodel.cpp \
    $$PWD/asemanquicklistmodelsource.cpp \
    asemanabstractquicklistmodelhint.cpp \
    asemanquicklistmodelcopyhint.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

load(qml_plugin)


