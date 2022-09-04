INCLUDEPATH += $$PWD
QT += core gui network quick

greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

HEADERS += \
    $$PWD/asemanmodelsplugin.h \
    $$PWD/asemanqttoolsitemmodels.h  \
    $$PWD/asemanquicklistmodel.h \
    $$PWD/asemanquicklistmodelsource.h \
    $$PWD/asemanabstractquicklistmodelhint.h \
    $$PWD/asemanquicklistmodelcamelcasehint.h \
    $$PWD/asemanquicklistmodelcopyhint.h \
    $$PWD/asemanquicklistmodeldeletehint.h \
    $$PWD/asemanquicklistmodelformathint.h

SOURCES += \
    $$PWD/asemanmodelsplugin.cpp \
    $$PWD/asemanqttoolsitemmodels.cpp  \
    $$PWD/asemanquicklistmodel.cpp \
    $$PWD/asemanquicklistmodelsource.cpp \
    $$PWD/asemanabstractquicklistmodelhint.cpp \
    $$PWD/asemanquicklistmodelcamelcasehint.cpp \
    $$PWD/asemanquicklistmodelcopyhint.cpp \
    $$PWD/asemanquicklistmodeldeletehint.cpp \
    $$PWD/asemanquicklistmodelformathint.cpp

static: !linux: !win32: DEFINES += ASEMAN_STATIC_BUILD


