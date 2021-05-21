#ifndef ASEMANHTTPSERVER_GLOBAL_H
#define ASEMANHTTPSERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef QT_STATIC
#if defined(LIBQTASEMAN_HTTPSERVER_LIBRARY)
#  define LIBQTASEMAN_HTTPSERVER_EXPORT Q_DECL_EXPORT
#else
#  define LIBQTASEMAN_HTTPSERVER_EXPORT Q_DECL_IMPORT
#endif
#else
#define LIBQTASEMAN_HTTPSERVER_EXPORT
#endif

#endif // ASEMANHTTPSERVER_GLOBAL_H