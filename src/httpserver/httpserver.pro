load(qt_build_config)

INCLUDEPATH += $$PWD $$PWD/qhttp/src $$PWD/qhttp/3rdparty $$PWD/qhttp/src/private/
DEPENDPATH += $$PWD

QT += core network
QT -= gui

TARGET = QAsemanHttpServer
MODULE = asemanhttpserver

load(qt_module)

DEFINES *= QHTTP_MEMORY_LOG=0
DEFINES *= QHTTP_EXPORT
DEFINES *= LIBQTASEMAN_HTTPSERVER_LIBRARY

# Joyent http_parser
SOURCES  += $$PWD/qhttp/3rdparty/http-parser/http_parser.c
HEADERS  += $$PWD/qhttp/3rdparty/http-parser/http_parser.h \
    asemanhttpserver_global.h

SOURCES  += \
    qhttp/src/qhttpabstracts.cpp \
    qhttp/src/qhttpserverconnection.cpp \
    qhttp/src/qhttpserverrequest.cpp \
    qhttp/src/qhttpserverresponse.cpp \
    qhttp/src/qhttpserver.cpp \
    asemanhttpserver.cpp

HEADERS  += \
    qhttp/src/qhttpfwd.hpp \
    qhttp/src/qhttpabstracts.hpp \
    qhttp/src/qhttpserverconnection.hpp \
    qhttp/src/qhttpserverrequest.hpp \
    qhttp/src/qhttpserverresponse.hpp \
    qhttp/src/qhttpserver.hpp \
    asemanhttpserver.h
