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

#include "asemanmultimediadatabase.h"

#include <QJsonDocument>

#ifdef Q_OS_ANDROID
#include "asemanandroidmultimedia.h"
#endif

class AsemanMultimediaDatabase::Private
{
public:
};

AsemanMultimediaDatabase::AsemanMultimediaDatabase(QObject *parent) :
    QObject(parent)
{
    p = new Private;
}

QVariantList AsemanMultimediaDatabase::getAllMusics() const
{
#ifdef Q_OS_ANDROID
    return QJsonDocument::fromJson( AsemanAndroidMultimedia::instance()->getAllMusics().toUtf8() ).toVariant().toList();
#else
    return QVariantList();
#endif
}

QVariantList AsemanMultimediaDatabase::getAllAlbums() const
{
#ifdef Q_OS_ANDROID
    return QJsonDocument::fromJson( AsemanAndroidMultimedia::instance()->getAllAlbums().toUtf8() ).toVariant().toList();
#else
    return QVariantList();
#endif
}

AsemanMultimediaDatabase::~AsemanMultimediaDatabase()
{
    delete p;
}
