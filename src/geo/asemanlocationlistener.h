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

#ifndef ASEMANLOCATIONLISTENER_H
#define ASEMANLOCATIONLISTENER_H

#include <QObject>
#include <QGeoPositionInfo>

#include "asemangeo_global.h"

class AsemanLocationListenerPrivate;
class LIBQTASEMAN_GEO_EXPORT AsemanLocationListener : public QObject
{
    Q_OBJECT
public:
    AsemanLocationListener(QObject *parent = 0);
    virtual ~AsemanLocationListener();

    void requestLocationUpdates(int interval);
    void getLastKnownLocation();

Q_SIGNALS:
    void positionUpdated(const QGeoPositionInfo & update);

private:
    AsemanLocationListenerPrivate *p;
};

#endif // ASEMANLOCATIONLISTENER_H
