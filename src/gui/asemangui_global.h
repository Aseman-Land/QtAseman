#ifndef ASEMAN_GUI_GLOBAL_H
#define ASEMAN_GUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef QT_STATIC
#if defined(LIBQTASEMAN_GUI_LIBRARY)
#  define LIBQTASEMAN_GUI_EXPORT Q_DECL_EXPORT
#else
#  define LIBQTASEMAN_GUI_EXPORT Q_DECL_IMPORT
#endif
#else
#define LIBQTASEMAN_GUI_EXPORT
#endif

#endif // ASEMAN_GUI_GLOBAL_H
