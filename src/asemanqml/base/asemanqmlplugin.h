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

#ifndef ASEMANQMLPLUGIN_H
#define ASEMANQMLPLUGIN_H

#include <QQmlExtensionPlugin>

class AsemanQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT

#ifndef QT_ASEMAN_EMBEDDED
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
#endif

public:
    static bool registerStaticTypes(const char *uri);

    void registerTypes(const char *uri);
    void initializeEngine(QQmlEngine *engine, const char *uri);
};

#endif // ASEMANQMLPLUGIN_H
