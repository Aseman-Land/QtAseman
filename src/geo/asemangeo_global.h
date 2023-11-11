#ifndef ASEMAN_GEO_GLOBAL_H
#define ASEMAN_GEO_GLOBAL_H

#include <QtCore/qglobal.h>

#if !defined(QT_STATIC) && !defined(QASEMAN_STATIC)
#if defined(LIBQTASEMAN_GEO_LIBRARY)
#  define LIBQTASEMAN_GEO_EXPORT Q_DECL_EXPORT
#else
#  define LIBQTASEMAN_GEO_EXPORT Q_DECL_IMPORT
#endif
#else
#define LIBQTASEMAN_GEO_EXPORT
#endif

#endif // ASEMAN_GEO_GLOBAL_H
