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

#include "asemanviewport.h"
#include "asemanviewportcontroller.h"

#include <QtQml>

class AsemanViewport::Private
{
public:
    QList<AsemanViewportItem*> items;
    QList<AsemanViewportItem*> defaultItems;
    QHash<QUrl, QQmlComponent*> components;
};

AsemanViewport::AsemanViewport(QQuickItem *parent) :
    QQuickItem(parent)
{
    p = new Private;

    p->defaultItems << new AsemanViewportItem("android-page", "AndroidDefaultPagesViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("android-activity", "AndroidActivityViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("android-bottomdrawer", "AndroidBottomDrawerViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("android-dialog", "AndroidDialogViewport.qml", this);

    p->defaultItems << new AsemanViewportItem("ios-page", "IOSNormalViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("ios-popup", "IOSPopupViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("ios-bottomdrawer", "IOSBottomDrawerViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("ios-dialog", "IOSDialogViewport.qml", this);

#ifdef Q_OS_ANDROID
    p->defaultItems << new AsemanViewportItem("page", "AndroidDefaultPagesViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("popup", "IOSPopupViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("activity", "AndroidActivityViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("bottomdrawer", "AndroidBottomDrawerViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("dialog", "AndroidDialogViewport.qml", this);
#else
    p->defaultItems << new AsemanViewportItem("page", "IOSNormalViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("popup", "IOSPopupViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("activity", "AndroidActivityViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("bottomdrawer", "IOSBottomDrawerViewport.qml", this);
    p->defaultItems << new AsemanViewportItem("dialog", "IOSDialogViewport.qml", this);
#endif

    p->defaultItems << new AsemanViewportItem("none", "NoneViewport.qml", this);
}

QQmlListProperty<AsemanViewportItem> AsemanViewport::items()
{
    return QQmlListProperty<AsemanViewportItem>(this, &p->items, QQmlListProperty<AsemanViewportItem>::AppendFunction(append),
                                                QQmlListProperty<AsemanViewportItem>::CountFunction(count),
                                                QQmlListProperty<AsemanViewportItem>::AtFunction(at),
                                                QQmlListProperty<AsemanViewportItem>::ClearFunction(clear) );
}

QList<AsemanViewportItem *> AsemanViewport::itemsList() const
{
    return p->items;
}

QStringList AsemanViewport::keys() const
{
    QList<AsemanViewportItem*> list = p->defaultItems;
    list << p->items;

    QStringList result;
    for (AsemanViewportItem *i: list)
        result << i->name().toLower();

    return result;
}

AsemanViewportAttechedType *AsemanViewport::qmlAttachedProperties(QObject *object)
{
    return new AsemanViewportAttechedType(object);
}

QVariant AsemanViewport::getComponent(const QString &name)
{
    QList<AsemanViewportItem*> list = p->defaultItems;
    list << p->items;

    for (AsemanViewportItem *i: list)
        if (i->name().toLower() == name.toLower())
            return i->component();

    return QVariant();
}

QQmlComponent *AsemanViewport::createComponent(const QUrl &url, bool asyn)
{
    QQmlComponent *component = p->components.value(url);
    if (component)
        return component;

    QQmlEngine *engine = qmlEngine(this);
    if (!engine)
    {
        qmlWarning(this) << "Could not find engine of the object";
        return Q_NULLPTR;
    }

    component = new QQmlComponent(engine, url, (asyn? QQmlComponent::Asynchronous : QQmlComponent::PreferSynchronous), this);
    p->components[url] = component;

    connect(component, &QObject::destroyed, this, [this, url](){
        p->components.remove(url);
    });

    return component;
}

void AsemanViewport::append(QQmlListProperty<AsemanViewportItem> *p, AsemanViewportItem *v)
{
    AsemanViewport *aobj = static_cast<AsemanViewport*>(p->object);
    aobj->p->items.append(v);
    Q_EMIT aobj->itemsChanged();
}

int AsemanViewport::count(QQmlListProperty<AsemanViewportItem> *p)
{
    AsemanViewport *aobj = static_cast<AsemanViewport*>(p->object);
    return aobj->p->items.count();
}

AsemanViewportItem *AsemanViewport::at(QQmlListProperty<AsemanViewportItem> *p, int idx)
{
    AsemanViewport *aobj = static_cast<AsemanViewport*>(p->object);
    return aobj->p->items.at(idx);
}

void AsemanViewport::clear(QQmlListProperty<AsemanViewportItem> *p)
{
    AsemanViewport *aobj = static_cast<AsemanViewport*>(p->object);
    aobj->p->items.clear();
    Q_EMIT aobj->itemsChanged();
}

AsemanViewport::~AsemanViewport()
{
    delete p;
}



AsemanViewportAttechedType::AsemanViewportAttechedType(QObject *parent) :
    QObject(parent)
{
}

AsemanViewportController *AsemanViewportAttechedType::controller() const
{
    QList<AsemanViewportController*> controllers = allControllers();
    if (controllers.isEmpty())
    {
        qmlWarning(this) << "There is no controller attached to the viewport.";
        return Q_NULLPTR;
    }
    return controllers.first();
}

QList<AsemanViewportController*> AsemanViewportAttechedType::allControllers() const
{
    return AsemanViewportController::controllers( AsemanViewportAttechedType::viewport() );
}

AsemanViewport *AsemanViewportAttechedType::viewport() const
{
    return AsemanViewportAttechedType::viewport( parent() );
}

AsemanViewport *AsemanViewportAttechedType::viewport(QObject *obj)
{
    AsemanViewport *viewport = Q_NULLPTR;
    do
    {
        QQuickItem *item = qobject_cast<QQuickItem*>(obj);
        obj = item? item->parentItem() : obj->parent();

        viewport = qobject_cast<AsemanViewport*>(obj);
        if (viewport)
            return viewport;

    } while(obj);

    return viewport;
}

AsemanViewportAttechedType::~AsemanViewportAttechedType()
{
}
