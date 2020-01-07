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

#ifndef ASEMANJAVALAYER_H
#define ASEMANJAVALAYER_H

#include <QObject>

#include "asemanmultimedia_global.h"

class AsemanAndroidMultimediaPrivate;
class LIBQTASEMAN_MULTIMEDIA_EXPORT AsemanAndroidMultimedia : public QObject
{
    Q_OBJECT
public:
    AsemanAndroidMultimedia();
    virtual ~AsemanAndroidMultimedia();

    static AsemanAndroidMultimedia *instance();

public Q_SLOTS:
    QString getAllMusics();
    QString getAllAlbums();
    QString getAllArtists();
    QString getArtistAlbums(const QString &artistId);
    QString getArtistSongs(const QString &artistId);
    QString getAlbumSongs(const QString &albumId);

private Q_SLOTS:
    void registerObject();

protected:
    void setImplemented(bool stt);

private:
    AsemanAndroidMultimediaPrivate *p;
};

typedef AsemanAndroidMultimedia QAsemanAndroidMultimedia;

#endif // ASEMANJAVALAYER_H
