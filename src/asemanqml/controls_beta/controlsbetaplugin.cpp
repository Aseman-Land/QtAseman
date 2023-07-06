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

#include "controlsbetaplugin.h"
#include "asemanqttoolsitemcontrolsbeta.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QtQml>

#ifdef QT_ASEMAN_EMBEDDED
bool asemanqml_controls_beta_plugin_registered = AsemanControlsBetaPlugin::registerStaticTypes("AsemanQml.Controls.Beta");
#endif

bool AsemanControlsBetaPlugin::registerStaticTypes(const char *uri)
{
    Q_INIT_RESOURCE(qmake_asemancontrols_beta);
    AsemanQtToolsItemControlsBeta::registerTypes(uri);
    AsemanQtToolsItemControlsBeta::registerFiles(QStringLiteral(":/AsemanQml/Controls/Beta"), uri);
    return true;
}

void AsemanControlsBetaPlugin::registerTypes(const char *uri)
{
    AsemanControlsBetaPlugin::registerStaticTypes(uri);
}

void AsemanControlsBetaPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}
