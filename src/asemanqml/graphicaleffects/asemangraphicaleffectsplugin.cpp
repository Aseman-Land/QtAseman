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

#include "asemangraphicaleffectsplugin.h"

#include "asemanqttoolsitemgraphicaleffects.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QtQml>

#ifdef QT_ASEMAN_EMBEDDED
bool asemanqml_graphicaleffects_plugin_registered = AsemanGraphicalEffectsPlugin::registerStaticTypes("AsemanQml.GraphicalEffects");
#endif

bool AsemanGraphicalEffectsPlugin::registerStaticTypes(const char *uri)
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    AsemanQtToolsItemGraphicalEffects::registerFiles(QStringLiteral(":/AsemanQml/GraphicalEffects/Qt5"), uri);
#else
    AsemanQtToolsItemGraphicalEffects::registerFiles(QStringLiteral(":/AsemanQml/GraphicalEffects/Qt6"), uri);
#endif
    return true;
}

void AsemanGraphicalEffectsPlugin::registerTypes(const char *uri)
{
    AsemanGraphicalEffectsPlugin::registerStaticTypes(uri);
}

void AsemanGraphicalEffectsPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
    AsemanQtTools::initializeEngine(engine, uri);
}
