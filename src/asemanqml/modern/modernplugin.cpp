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

#include "modernplugin.h"
#include "asemanqttoolsitemmodern.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QtQml>

#ifdef QT_ASEMAN_EMBEDDED
bool asemanqml_modern_plugin_registered = AsemanModernPlugin::registerStaticTypes("AsemanQml.Modern");
#endif

bool AsemanModernPlugin::registerStaticTypes(const char *uri)
{
    Q_INIT_RESOURCE(qmake_asemanmodern);
    AsemanQtToolsItemModern::registerTypes(uri);
    AsemanQtToolsItemModern::registerFiles(QStringLiteral(":/AsemanQml/Modern"), uri);
    return true;
}

void AsemanModernPlugin::registerTypes(const char *uri)
{
    AsemanModernPlugin::registerStaticTypes(uri);
}

void AsemanModernPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}
