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

#include "asemanviewportcontroller.h"

#include <QSet>
#include <QPointer>
#include <QQmlInfo>
#include <QUrl>
#include <QUrlQuery>

class AsemanViewportController::Private
{
public:
    QPointer<AsemanViewport> viewport;
    QList<AsemanViewportControllerRoute*> routes;
    bool allowRecursiveTrigger;

    static QList<AsemanViewportController*> controllers;
};

QList<AsemanViewportController*> AsemanViewportController::Private::controllers;

AsemanViewportController::AsemanViewportController(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->allowRecursiveTrigger = false;

    Private::controllers << this;
}

QQmlListProperty<AsemanViewportControllerRoute> AsemanViewportController::routes()
{
    return QQmlListProperty<AsemanViewportControllerRoute>(this, &p->routes, QQmlListProperty<AsemanViewportControllerRoute>::AppendFunction(append),
                                                          QQmlListProperty<AsemanViewportControllerRoute>::CountFunction(count),
                                                          QQmlListProperty<AsemanViewportControllerRoute>::AtFunction(at),
                                                          QQmlListProperty<AsemanViewportControllerRoute>::ClearFunction(clear) );
}

void AsemanViewportController::setViewport(AsemanViewport *viewport)
{
    if (p->viewport == viewport)
        return;

    p->viewport = viewport;
    Q_EMIT viewportChanged();
}

AsemanViewport *AsemanViewportController::viewport() const
{
    return p->viewport;
}

bool AsemanViewportController::allowRecursiveTrigger() const
{
    return p->allowRecursiveTrigger;
}

void AsemanViewportController::setAllowRecursiveTrigger(bool allowRecursiveTrigger)
{
    if (p->allowRecursiveTrigger == allowRecursiveTrigger)
        return;

    p->allowRecursiveTrigger = allowRecursiveTrigger;
    Q_EMIT allowRecursiveTriggerChanged();
}

QVariantMap AsemanViewportController::lookup(const QString &url, QVariantMap properties, AsemanViewport *viewport)
{
    QVariantMap res;
    if (!viewport)
        viewport = p->viewport;

    if (!viewport)
    {
        qmlWarning(this) << "viewport property cannot be null.";
        return res;
    }

    for (AsemanViewportControllerRoute *r: p->routes)
    {
        QRegExp rx = r->route();
        rx.setPattern( "^" + rx.pattern() + "$" );
        rx.setMinimal(false);

        if (rx.indexIn(url) == 0)
        {
            properties["properties"] = properties;
            properties["url"] = url;

            QUrl urlObj(url);
            QUrlQuery query(urlObj);
            auto queryItems = query.queryItems();
            for (auto qi: queryItems)
                properties[qi.first] = qi.second;

            QVariant item;
            QVariant component = r->component();
            QVariant type = r->viewportType().length()? r->viewportType() : urlObj.scheme();
            QVariant props = properties;

            res["component"] = component;
            res["type"] = type;
            res["properties"] = props;
            res["viewport"] = QVariant::fromValue<QObject*>(viewport);

            return res;
        }
    }

    AsemanViewportAttechedProperty attachProperty(p->viewport);
    AsemanViewportController *parentController = static_cast<AsemanViewportController*>(attachProperty.controller());
    if (parentController && p->allowRecursiveTrigger)
        return parentController->lookup(url, properties, viewport);
    else
        qmlWarning(this) << "Cannot find any route to handle " << url;

    return res;
}

void AsemanViewportController::append(QQmlListProperty<AsemanViewportControllerRoute> *p, AsemanViewportControllerRoute *v)
{
    AsemanViewportController *aobj = static_cast<AsemanViewportController*>(p->object);
    aobj->p->routes.append(v);
    Q_EMIT aobj->routesChanged();
}

int AsemanViewportController::count(QQmlListProperty<AsemanViewportControllerRoute> *p)
{
    AsemanViewportController *aobj = static_cast<AsemanViewportController*>(p->object);
    return aobj->p->routes.count();
}

AsemanViewportControllerRoute *AsemanViewportController::at(QQmlListProperty<AsemanViewportControllerRoute> *p, int idx)
{
    AsemanViewportController *aobj = static_cast<AsemanViewportController*>(p->object);
    return aobj->p->routes.at(idx);
}

void AsemanViewportController::clear(QQmlListProperty<AsemanViewportControllerRoute> *p)
{
    AsemanViewportController *aobj = static_cast<AsemanViewportController*>(p->object);
    aobj->p->routes.clear();
    Q_EMIT aobj->routesChanged();
}

QList<AsemanViewportController *> AsemanViewportController::controllers(AsemanViewport *viewport)
{
    QList<AsemanViewportController *> res;
    for (AsemanViewportController *controller: Private::controllers)
        if (controller->p->viewport == viewport)
            res << controller;
    return res;
}

AsemanViewportController::~AsemanViewportController()
{
    Private::controllers.removeOne(this);
    delete p;
}
