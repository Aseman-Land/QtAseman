TARGET  = asemanqmlmodels
TARGETPATH = AsemanQml/Models
IMPORT_VERSION = 2.0

INCLUDEPATH += $$PWD
QT += core gui network asemanqml asemangui asemancore quick

greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

HEADERS += \
    $$PWD/asemanmodelsplugin.h \
    $$PWD/asemanqttoolsitemmodels.h  \
    $$PWD/asemanquicklistmodel.h \
    $$PWD/asemanquicklistmodelsource.h \
    asemanabstractquicklistmodelhint.h \
    asemanquicklistmodelcamelcasehint.h \
    asemanquicklistmodelcopyhint.h \
    asemanquicklistmodeldeletehint.h \
    asemanquicklistmodelformathint.h

SOURCES += \
    $$PWD/asemanmodelsplugin.cpp \
    $$PWD/asemanqttoolsitemmodels.cpp  \
    $$PWD/asemanquicklistmodel.cpp \
    $$PWD/asemanquicklistmodelsource.cpp \
    asemanabstractquicklistmodelhint.cpp \
    asemanquicklistmodelcamelcasehint.cpp \
    asemanquicklistmodelcopyhint.cpp \
    asemanquicklistmodeldeletehint.cpp \
    asemanquicklistmodelformathint.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD

load(qml_plugin)


