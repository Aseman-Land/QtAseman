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

#include "materialiconsplugin.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QtQml>

#ifdef QT_ASEMAN_EMBEDDED
bool asemanqml_materialicons_plugin_registered = AsemanMaterialIconsPlugin::registerStaticTypes("AsemanQml.MaterialIcons");
#endif

bool AsemanMaterialIconsPlugin::registerStaticTypes(const char *uri)
{
    Q_INIT_RESOURCE(qmake_asemanmaterialicons);
    qmlRegisterSingletonType(QUrl("qrc:/AsemanQml/MaterialIcons/MaterialIcons.qml"), uri, 2, 0, "MaterialIcons");
    return true;
}

void AsemanMaterialIconsPlugin::registerTypes(const char *uri)
{
    AsemanMaterialIconsPlugin::registerStaticTypes(uri);
}

void AsemanMaterialIconsPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}
