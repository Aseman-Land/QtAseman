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

#ifndef ASEMANREFRESHEROBJECT_H
#define ASEMANREFRESHEROBJECT_H

#include <QObject>
#include <QTimer>

#include "asemancore_global.h"

class LIBQTASEMAN_CORE_EXPORT AsemanRefresherObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool refreshing READ refreshing NOTIFY refreshingChanged)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(qint32 delay READ delay NOTIFY delayChanged)

public:
    AsemanRefresherObject(QObject *parent = nullptr);
    virtual ~AsemanRefresherObject();

    void setRefreshing(bool state);
    void setDelay(qint32 newDelay);

    bool refreshing() const;
    bool active() const;
    qint32 delay() const;

    bool forceActiveOnInitialize() const;
    void setForceActiveOnInitialize(bool newForceActiveOnInitialize);

Q_SIGNALS:
    void refreshingChanged();
    void activeChanged();
    void delayChanged();

private:
    bool mForceActiveOnInitialize = true;
    bool mInitialized = false;
    bool mRefreshing = false;

    qint32 mDelay = 0;
    QTimer *mDelayTimer;
};

typedef AsemanRefresherObject QAsemanRefresherObject;

#endif // ASEMANREFRESHEROBJECT_H
