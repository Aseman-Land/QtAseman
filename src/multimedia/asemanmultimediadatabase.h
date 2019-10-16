/*
    Copyright (C) 2019 Aseman Team
    http://aseman.io

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANMULTIMEDIADATABASE_H
#define ASEMANMULTIMEDIADATABASE_H

#include <QObject>
#include <QVariant>

#include "asemanmultimedia_global.h"

class LIBQTASEMAN_MULTIMEDIA_EXPORT AsemanMultimediaDatabase : public QObject
{
    Q_OBJECT
    class Private;

public:
    AsemanMultimediaDatabase(QObject *parent = Q_NULLPTR);
    virtual ~AsemanMultimediaDatabase();

Q_SIGNALS:

public Q_SLOTS:
    QVariantList getAllMusics() const;
    QVariantList getAllAlbums() const;

private:
    Private *p;
};

#endif // ASEMANMULTIMEDIADATABASE_H
