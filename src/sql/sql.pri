INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core

qtHaveModule(sql): QT += sql

HEADERS += \
    $$PWD/asemansql_global.h \
    $$PWD/asemansqlobject.h

SOURCES += \
    $$PWD/asemansqlobject.cpp
