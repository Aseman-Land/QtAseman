/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANQTTOOLS_H
#define ASEMANQTTOOLS_H

#include <QtGlobal>
#include <QString>

#include "asemantools_global.h"

class QObject;
class QQmlEngine;
class QJSEngine;
class LIBQTASEMAN_QML_EXPORT AsemanQtTools
{
public:
    static void initializeEngine(QQmlEngine *engine, const char *uri);

    static class AsemanQuickViewWrapper *quickView(QQmlEngine *engine);
    static class AsemanApplicationItem *application(QQmlEngine *engine);
    static class AsemanDesktopTools *desktopTools();
    static class AsemanDevicesItem *devices();
    static class AsemanQtLogger *qtLogger();
#ifdef Q_OS_ANDROID
    static class AsemanJavaLayer *javaLayer();
#endif
    static class AsemanToolsItem *tools();
    static class AsemanTextTools *textTools();
    static class AsemanCalendarConverter *calendar(QQmlEngine *engine);
    static class AsemanBackHandler *backHandler(QQmlEngine *engine);
    static class AsemanGlobalTranslations *globalTranslations(QQmlEngine *engine);

protected:
    static QString fixType(const QString &type);
};

#endif // ASEMANQTTOOLS_H
