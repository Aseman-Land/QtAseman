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

#ifndef ASEMANQTTOOLSITEMGRAPHICALEFFECTS_H
#define ASEMANQTTOOLSITEMGRAPHICALEFFECTS_H

#include <QtGlobal>
#include <QString>

#include <asemanqttools.h>

class QObject;
class QQmlEngine;
class QJSEngine;
class AsemanQtToolsItemGraphicalEffects: public AsemanQtTools
{
public:
    static void registerTypes(const char *uri, bool exportMode = false);
    static void registerFiles(const QString &filesLocation, const char *uri);

    template<typename T>
    static int registerType(const char *uri, int versionMajor, int versionMinor, const char *typeName, bool exportMode);

    template<typename T>
    static int registerModel(const char *uri, int versionMajor, int versionMinor, const char *typeName, bool exportMode);

    template <typename T>
    static int registerSingletonType(const char *uri, int versionMajor, int versionMinor, const char *typeName,
                                 QObject *(*callback)(QQmlEngine *, QJSEngine *), bool exportMode);

    template<typename T>
    static int registerUncreatableType(const char *uri, int versionMajor, int versionMinor, const char *qmlName, const QString& reason, bool exportMode);

    static void exportDocuments(const QString &destination);

protected:
    template<typename T>
    static QString exportItem(const QString &module, int major, int minor, const QString &component, bool store = true);
    template<typename T>
    static QString exportModel(const QString &module, int major, int minor, const QString &component);

    static QString fixType(const QString &type);
};

#endif // ASEMANQTTOOLSITEMGRAPHICALEFFECTS_H
