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

#ifndef ASEMANQMLSMARTCOMPONENT_H
#define ASEMANQMLSMARTCOMPONENT_H

#include <QObject>
#include <QQmlComponent>
#include <QJSValue>
#include <QUrl>

#include "asemantools_global.h"

class AsemanQmlSmartComponentPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanQmlSmartComponent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(QQmlComponent* component READ component NOTIFY componentChanged)
    Q_PROPERTY(int delayInterval READ delayInterval WRITE setDelayInterval NOTIFY delayIntervalChanged)

public:
    AsemanQmlSmartComponent(QObject *parent = 0);
    virtual ~AsemanQmlSmartComponent();

    void setSource(const QUrl &url);
    QUrl source() const;

    void setDelayInterval(int ms);
    int delayInterval() const;

    int status() const;
    QString error() const;

    QQmlComponent *component() const;

Q_SIGNALS:
    void delayIntervalChanged();
    void sourceChanged();
    void statusChanged();
    void errorChanged();
    void componentChanged();
    void ready();

private Q_SLOTS:
    void statusChangedSlt(QQmlComponent::Status status);

private:
    void recheckTimer();
    void createComponent();

protected:
    void timerEvent(QTimerEvent *e);

private:
    AsemanQmlSmartComponentPrivate *p;
};

#endif // ASEMANQMLSMARTCOMPONENT_H
