#ifndef ASEMAN_SQL_GLOBAL_H
#define ASEMAN_SQL_GLOBAL_H

#include <QtCore/qglobal.h>

#if !defined(QT_STATIC) && !defined(QASEMAN_STATIC)
#if defined(LIBQTASEMAN_SQL_LIBRARY)
#  define LIBQTASEMAN_SQL_EXPORT Q_DECL_EXPORT
#else
#  define LIBQTASEMAN_SQL_EXPORT Q_DECL_IMPORT
#endif
#else
#define LIBQTASEMAN_SQL_EXPORT
#endif

#endif // ASEMAN_SQL_GLOBAL_H
