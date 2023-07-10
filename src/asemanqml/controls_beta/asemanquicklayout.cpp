#include "asemanquicklayout.h"

#include <QEvent>

AsemanQuickLayout::AsemanQuickLayout(QQuickItem *parent)
    : QQuickItem(parent)
{
    connect(this, &QQuickItem::widthChanged, this, &AsemanQuickLayout::reload);
    connect(this, &QQuickItem::heightChanged, this, &AsemanQuickLayout::reload);
}

AsemanQuickLayout::~AsemanQuickLayout()
{
}

AsemanQuickLayoutProperty *AsemanQuickLayout::qmlAttachedProperties(QObject *object)
{
    return new AsemanQuickLayoutProperty(object);
}

void AsemanQuickLayout::reload()
{
    relocateChilds();
}

void AsemanQuickLayout::reloadDelayed()
{
    if (!mReloadTimer)
    {
        mReloadTimer = new QTimer(this);
        mReloadTimer->setInterval(5);
        mReloadTimer->setSingleShot(true);

        connect(mReloadTimer, &QTimer::timeout, this, &AsemanQuickLayout::reload);
    }

    mReloadTimer->stop();
    mReloadTimer->start();
}

void AsemanQuickLayout::itemChange(ItemChange change, const ItemChangeData &value)
{
    switch (static_cast<int>(change))
    {
    case QQuickItem::ItemChildAddedChange:
    {
        auto attached = getAttached(value.item);

        connect(value.item, &QQuickItem::implicitWidthChanged, this, &AsemanQuickLayout::reload);
        connect(value.item, &QQuickItem::implicitHeightChanged, this, &AsemanQuickLayout::reload);
        connect(attached, &AsemanQuickLayoutProperty::changed, this, &AsemanQuickLayout::reload);

        reloadDelayed();
    }
        break;

    case QQuickItem::ItemChildRemovedChange:
    {
        auto attached = getAttached(value.item);

        disconnect(value.item, &QQuickItem::implicitWidthChanged, this, &AsemanQuickLayout::reload);
        disconnect(value.item, &QQuickItem::implicitHeightChanged, this, &AsemanQuickLayout::reload);
        disconnect(attached, &AsemanQuickLayoutProperty::changed, this, &AsemanQuickLayout::reload);

        reloadDelayed();
    }
        break;
    }

    QQuickItem::itemChange(change, value);
}

AsemanQuickLayoutProperty *AsemanQuickLayout::getAttached(QObject *object)
{
    return qobject_cast<AsemanQuickLayoutProperty*>(qmlAttachedPropertiesObject<AsemanQuickLayout>(object, true));
}
