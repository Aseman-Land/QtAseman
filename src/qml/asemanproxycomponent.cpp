#include "asemanproxycomponent.h"

#include <QPointer>
#include <QQuickItem>
#include <QDebug>

class AsemanProxyComponent::Private
{
public:
    QPointer<QQmlComponent> source;
    QPointer<QObject> object;
};

AsemanProxyComponent::AsemanProxyComponent(QObject *parent) :
    QObject(parent)
{
    p = new Private;
}

QQmlComponent *AsemanProxyComponent::source() const
{
    return p->source;
}

void AsemanProxyComponent::setSource(QQmlComponent *source)
{
    if(p->source == source)
        return;

    p->source = source;
    create();
    Q_EMIT sourceChanged();
}

QObject *AsemanProxyComponent::object() const
{
    return p->object;
}

void AsemanProxyComponent::setObject(QObject *object)
{
    if(p->object == object)
        return;
    if(p->object)
        p->object->deleteLater();

    p->object = object;
    Q_EMIT objectChanged();
}

void AsemanProxyComponent::create()
{
    if(!p->source)
    {
        setObject(Q_NULLPTR);
        return;
    }

    QObject *parent = AsemanProxyComponent::parent();

    QQmlContext *context = qmlContext(this);
    QObject *object = p->source->create(context);
    if(object)
    {
        object->setParent(parent);

        QQuickItem *parentItem = qobject_cast<QQuickItem*>(parent);
        QQuickItem *objectItem = qobject_cast<QQuickItem*>(object);
        if(parentItem && objectItem)
            objectItem->setParentItem(parentItem);
    }

    setObject(object);
}

AsemanProxyComponent::~AsemanProxyComponent()
{
    delete p;
}
