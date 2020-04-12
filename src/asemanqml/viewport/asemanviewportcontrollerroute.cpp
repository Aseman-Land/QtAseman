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

#include "asemanviewportcontrollerroute.h"

class AsemanViewportControllerRoute::Private
{
public:
    QRegExp route;
    QVariant component;
    QString viewportType;
};

AsemanViewportControllerRoute::AsemanViewportControllerRoute(QObject *parent) :
    QObject(parent)
{
    p = new Private;
}

QRegExp AsemanViewportControllerRoute::route() const
{
    return p->route;
}

void AsemanViewportControllerRoute::setRoute(const QRegExp &route)
{
    if (p->route == route)
        return;

    p->route = route;
    Q_EMIT routeChanged();
}

QVariant AsemanViewportControllerRoute::component() const
{
    return p->component;
}

void AsemanViewportControllerRoute::setComponent(const QVariant &component)
{
    if (p->component == component)
        return;

    p->component = component;
    Q_EMIT componentChanged();
}

QQmlComponent *AsemanViewportControllerRoute::sourceComponent() const
{
    return component().value<QQmlComponent*>();
}

void AsemanViewportControllerRoute::setSourceComponent(QQmlComponent *sourceComponent)
{
    setComponent( QVariant::fromValue(sourceComponent) );
}

QUrl AsemanViewportControllerRoute::source() const
{
    return component().toUrl();
}

void AsemanViewportControllerRoute::setSource(const QUrl &sourceComponent)
{
    setComponent( QVariant::fromValue(sourceComponent) );
}

QString AsemanViewportControllerRoute::viewportType() const
{
    return p->viewportType;
}

void AsemanViewportControllerRoute::setViewportType(const QString &viewportType)
{
    if (p->viewportType == viewportType)
        return;

    p->viewportType = viewportType;
    Q_EMIT viewportTypeChanged();
}

AsemanViewportControllerRoute::~AsemanViewportControllerRoute()
{
    delete p;
}
