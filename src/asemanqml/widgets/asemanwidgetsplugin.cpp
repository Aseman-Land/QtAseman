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

#include "asemanwidgetsplugin.h"

#include "asemanqttoolsitemwidgets.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QtQml>

#ifdef ASEMAN_STATIC_BUILD
bool AsemanWidgetsPlugin::static_types_registered = AsemanWidgetsPlugin::registerStaticTypes("AsemanQml.Widgets");
#endif

bool AsemanWidgetsPlugin::registerStaticTypes(const char *uri)
{
#ifdef ASEMAN_STATIC_BUILD
    if(static_types_registered)
        return true;
#endif
    AsemanQtToolsItemWidgets::registerTypes(uri);
    AsemanQtToolsItemWidgets::registerFiles(QStringLiteral(":/AsemanQml/Widgets"), uri);
    return true;
}

void AsemanWidgetsPlugin::registerTypes(const char *uri)
{
#ifdef ASEMAN_STATIC_BUILD
    Q_UNUSED(uri)
#else
    AsemanWidgetsPlugin::registerStaticTypes(uri);
#endif
}

void AsemanWidgetsPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
    AsemanQtTools::initializeEngine(engine, uri);
}
