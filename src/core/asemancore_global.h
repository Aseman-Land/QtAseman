#ifndef ASEMAN_CORE_GLOBAL_H
#define ASEMAN_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if !defined(QT_STATIC) && !defined(QASEMAN_STATIC)
#if defined(LIBQTASEMAN_CORE_LIBRARY)
#  define LIBQTASEMAN_CORE_EXPORT Q_DECL_EXPORT
#else
#  define LIBQTASEMAN_CORE_EXPORT Q_DECL_IMPORT
#endif
#else
#define LIBQTASEMAN_CORE_EXPORT
#endif

#endif // ASEMAN_CORE_GLOBAL_H
