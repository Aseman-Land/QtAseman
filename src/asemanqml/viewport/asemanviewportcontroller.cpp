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
    static QList<AsemanViewportController*> controllers;
};

QList<AsemanViewportController*> AsemanViewportController::Private::controllers;

AsemanViewportController::AsemanViewportController(QObject *parent) :
    QObject(parent)
{
    p = new Private;
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

QQuickItem *AsemanViewportController::trigger(const QString &url, QVariantMap properties)
{
    if (!p->viewport)
    {
        qmlWarning(this) << "viewport property cannot be null.";
        return Q_NULLPTR;
    }

    for (AsemanViewportControllerRoute *r: p->routes)
    {
        QRegExp rx = r->route();
        rx.setPattern( "^" + rx.pattern() + "$" );
        rx.setMinimal(false);

        if (rx.indexIn(url) == 0)
        {
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

            QMetaObject::invokeMethod(p->viewport.data(), "append", Q_RETURN_ARG(QVariant, item), Q_ARG(QVariant, component),
                                      Q_ARG(QVariant, props), Q_ARG(QVariant, type));

            QQuickItem *res = item.value<QQuickItem*>();
            if (!res)
                qmlWarning(this) << "Cannot append page to viewport.";

            return res;
        }
    }

    qmlWarning(this) << "Cannot find any route to handle " << url;
    return Q_NULLPTR;
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
    if (!viewport)
        return Private::controllers;

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
