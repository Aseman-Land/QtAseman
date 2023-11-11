#ifndef ASEMAN_QML_GLOBAL_H
#define ASEMAN_QML_GLOBAL_H

#include <QtCore/qglobal.h>

#if !defined(QT_STATIC) && !defined(QASEMAN_STATIC)
#if defined(LIBQTASEMAN_QML_LIBRARY)
#  define LIBQTASEMAN_QML_EXPORT Q_DECL_EXPORT
#else
#  define LIBQTASEMAN_QML_EXPORT Q_DECL_IMPORT
#endif
#else
#define LIBQTASEMAN_QML_EXPORT
#endif

#endif // ASEMAN_QML_GLOBAL_H
