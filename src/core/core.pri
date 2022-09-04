INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core

HEADERS += \
    $$PWD/asemanabstractlistmodel.h \
    $$PWD/asemanautostartmanager.h \
    $$PWD/asemancalendarconverter.h \
    $$PWD/asemancalendarconvertercore.h \
    $$PWD/asemancalendarmodel.h \
    $$PWD/asemancountriesmodel.h \
    $$PWD/asemandebugobjectcounter.h \
    $$PWD/asemanencrypter.h \
    $$PWD/asemanfilesystemmodel.h \
    $$PWD/asemanglobals.h \
    $$PWD/asemanhashobject.h \
    $$PWD/asemanlistobject.h \
    $$PWD/asemanlistrecord.h \
    $$PWD/asemanmixedlistmodel.h \
    $$PWD/asemanqtlogger.h \
    $$PWD/asemansettings.h \
    $$PWD/asemansimpleqtcryptor.h \
    $$PWD/asemancore_global.h \
    $$PWD/aseman_macros.h \
    $$PWD/private/serpent_sbox.h \
    $$PWD/asemanmapobject.h \
    $$PWD/asemanlistmodel.h

SOURCES += \
    $$PWD/asemanabstractlistmodel.cpp \
    $$PWD/asemanautostartmanager.cpp \
    $$PWD/asemancalendarconverter.cpp \
    $$PWD/asemancalendarconvertercore.cpp \
    $$PWD/asemancalendarmodel.cpp \
    $$PWD/asemancountriesmodel.cpp \
    $$PWD/asemandebugobjectcounter.cpp \
    $$PWD/asemanencrypter.cpp \
    $$PWD/asemanfilesystemmodel.cpp \
    $$PWD/asemanhashobject.cpp \
    $$PWD/asemanlistobject.cpp \
    $$PWD/asemanlistrecord.cpp \
    $$PWD/asemanmixedlistmodel.cpp \
    $$PWD/asemanqtlogger.cpp \
    $$PWD/asemansettings.cpp \
    $$PWD/asemansimpleqtcryptor.cpp \
    $$PWD/asemanmapobject.cpp \
    $$PWD/asemanlistmodel.cpp

RESOURCES += \
    $$PWD/asemancoreresource_lib.qrc

macx {
    !contains(DEFINES, DISABLE_CORE_SERVICES) {
        LIBS += -framework CoreServices
        INCLUDEPATH += /System/Library/Frameworks/CoreServices.framework/Headers/
        DEFINES += OSX_CORE_SERVICES_AVAILABLE
    }
    !contains(QMAKE_HOST.arch, x86_64) {
        LIBS +=  -framework CoreFoundation -framework Carbon -lobjc
    }
}
