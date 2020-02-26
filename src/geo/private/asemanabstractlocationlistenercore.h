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

#ifndef ASEMANABSTRACTLOCATIONLISTENERCORE_H
#define ASEMANABSTRACTLOCATIONLISTENERCORE_H

#include <QObject>
#include <QGeoPositionInfo>

#include "asemangeo_global.h"

class LIBQTASEMAN_GEO_EXPORT AsemanAbstractLocationListenerCore : public QObject
{
    Q_OBJECT
public:
    AsemanAbstractLocationListenerCore(QObject *parent = 0);
    virtual ~AsemanAbstractLocationListenerCore();

    virtual void requestLocationUpdates(int interval) = 0;
    virtual void getLastKnownLocation();
    virtual void stop();

Q_SIGNALS:
    void positionUpdated(const QGeoPositionInfo & update);

private Q_SLOTS:
    void updated(const QGeoPositionInfo & update);

private:
    QGeoPositionInfo _lastLocation;
};

#endif // ASEMANABSTRACTLOCATIONLISTENERCORE_H
