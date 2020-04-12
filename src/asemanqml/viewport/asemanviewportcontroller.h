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

#ifndef ASEMANVIEWPORTCONTROLLER_H
#define ASEMANVIEWPORTCONTROLLER_H

#include <QObject>
#include <QQmlListProperty>

#include "asemanviewport.h"
#include "asemanviewportcontrollerroute.h"

class AsemanViewportController : public QObject
{
    Q_OBJECT
    class Private;
    Q_PROPERTY(QQmlListProperty<AsemanViewportControllerRoute> routes READ routes NOTIFY routesChanged)
    Q_PROPERTY(AsemanViewport* viewport READ viewport WRITE setViewport NOTIFY viewportChanged)

    Q_CLASSINFO("DefaultProperty", "routes")

public:
    AsemanViewportController(QObject *parent = Q_NULLPTR);
    virtual ~AsemanViewportController();

    QQmlListProperty<AsemanViewportControllerRoute> routes();

    void setViewport(AsemanViewport *viewport);
    AsemanViewport *viewport() const;

    static QList<AsemanViewportController *> controllers(AsemanViewport *viewport = Q_NULLPTR);

public Q_SLOTS:
    QQuickItem *trigger(const QString &url, QVariantMap properties = QVariantMap());

Q_SIGNALS:
    void routesChanged();
    void viewportChanged();

private:
    static void append(QQmlListProperty<AsemanViewportControllerRoute> *p, AsemanViewportControllerRoute *v);
    static int count(QQmlListProperty<AsemanViewportControllerRoute> *p);
    static AsemanViewportControllerRoute *at(QQmlListProperty<AsemanViewportControllerRoute> *p, int idx);
    static void clear(QQmlListProperty<AsemanViewportControllerRoute> *p);

private:
    Private *p;
};

typedef AsemanViewportController QAsemanViewportController;


#endif // ASEMANVIEWPORTCONTROLLER_H
