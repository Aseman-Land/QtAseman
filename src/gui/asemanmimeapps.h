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

#ifndef ASEMANMIMEAPPS_H
#define ASEMANMIMEAPPS_H

#include <QObject>
#include <QStringList>

#include "asemangui_global.h"

class AsemanMimeAppsPrivate;
class LIBQTASEMAN_GUI_EXPORT AsemanMimeApps : public QObject
{
    Q_OBJECT
public:
    AsemanMimeApps( QObject *parent = 0 );
    virtual ~AsemanMimeApps();

    Q_INVOKABLE QStringList appsOfMime( const QString & mime );
    Q_INVOKABLE QStringList appsOfFile( const QString & file );

    Q_INVOKABLE QString appName( const QString & app ) const;
    Q_INVOKABLE QString appIcon( const QString & app ) const;
    Q_INVOKABLE QString appGenericName( const QString & app ) const;
    Q_INVOKABLE QString appComment( const QString & app ) const;
    Q_INVOKABLE QString appPath( const QString & app ) const;
    Q_INVOKABLE QString appCommand( const QString & app ) const;
    Q_INVOKABLE QStringList appMimes( const QString & app ) const;

public Q_SLOTS:
    void openFiles( const QString & app, const QStringList & files );

private:
    AsemanMimeAppsPrivate *p;
};

#endif // ASEMANMIMEAPPS_H
