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

#ifndef ASEMANVIEWPORTCONTROLLERROUTE_H
#define ASEMANVIEWPORTCONTROLLERROUTE_H

#include <QObject>
#include <QVariant>
#include <QUrl>
#include <QQmlComponent>
#include <QRegularExpression>

class AsemanViewportControllerRoute : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QRegularExpression route READ route WRITE setRoute NOTIFY routeChanged)
    Q_PROPERTY(QQmlComponent* sourceComponent READ sourceComponent WRITE setSourceComponent NOTIFY componentChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY componentChanged)
    Q_PROPERTY(QString viewportType READ viewportType WRITE setViewportType NOTIFY viewportTypeChanged)
    Q_CLASSINFO("DefaultProperty", "sourceComponent")

    class Private;

public:
    AsemanViewportControllerRoute(QObject *parent = Q_NULLPTR);
    virtual ~AsemanViewportControllerRoute();

    QRegularExpression route() const;
    void setRoute(const QRegularExpression &route);

    QVariant component() const;
    void setComponent(const QVariant &component);

    QQmlComponent *sourceComponent() const;
    void setSourceComponent(QQmlComponent *sourceComponent);

    QUrl source() const;
    void setSource(const QUrl &sourceComponent);

    QString viewportType() const;
    void setViewportType(const QString &viewportType);

Q_SIGNALS:
    void routeChanged();
    void componentChanged();
    void viewportTypeChanged();

private:
    Private *p;
};

typedef AsemanViewportControllerRoute QAsemanViewportControllerRoute;

#endif // ASEMANVIEWPORTCONTROLLERROUTE_H
