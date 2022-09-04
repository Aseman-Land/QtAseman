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

#include "asemanviewportplugin.h"

#include "asemanqttoolsitemviewport.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QtQml>

#ifdef QT_ASEMAN_EMBEDDED
bool asemanqml_viewport_plugin_registered = AsemanViewportPlugin::registerStaticTypes("AsemanQml.Viewport");
#endif

bool AsemanViewportPlugin::registerStaticTypes(const char *uri)
{
    Q_INIT_RESOURCE(qmake_asemanviewport);
    AsemanQtToolsItemViewport::registerTypes(uri);
    AsemanQtToolsItemViewport::registerFiles(QStringLiteral(":/AsemanQml/Viewport"), uri);
    return true;
}

void AsemanViewportPlugin::registerTypes(const char *uri)
{
    AsemanViewportPlugin::registerStaticTypes(uri);
}

void AsemanViewportPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
    AsemanQtTools::initializeEngine(engine, uri);
}
