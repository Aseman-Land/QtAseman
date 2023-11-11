#ifndef ASEMAN_WIDGETS_GLOBAL_H
#define ASEMAN_WIDGETS_GLOBAL_H

#include <QtCore/qglobal.h>

#if !defined(QT_STATIC) && !defined(QASEMAN_STATIC)
#if defined(LIBQTASEMAN_WIDGETS_LIBRARY)
#  define LIBQTASEMAN_WIDGETS_EXPORT Q_DECL_EXPORT
#else
#  define LIBQTASEMAN_WIDGETS_EXPORT Q_DECL_IMPORT
#endif
#else
#define LIBQTASEMAN_WIDGETS_EXPORT
#endif

#endif // ASEMAN_WIDGETS_GLOBAL_H
