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

#include "controlsplugin.h"
#include "asemanqttoolsitemcontrols.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QtQml>

#ifdef ASEMAN_STATIC_BUILD
bool AsemanControlsPlugin::static_types_registered = AsemanControlsPlugin::registerStaticTypes("AsemanQml.Controls");
#endif

bool AsemanControlsPlugin::registerStaticTypes(const char *uri)
{
#ifdef ASEMAN_STATIC_BUILD
    if(static_types_registered)
        return true;
#endif
    Q_INIT_RESOURCE(qmake_asemancontrols);
    AsemanQtToolsItemControls::registerTypes(uri);
    AsemanQtToolsItemControls::registerFiles(QStringLiteral(":/AsemanQml/Controls"), uri);
    return true;
}

void AsemanControlsPlugin::registerTypes(const char *uri)
{
    AsemanControlsPlugin::registerStaticTypes(uri);
}

void AsemanControlsPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}
