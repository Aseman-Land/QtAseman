#include "asemanabstractviewporttype.h"
#include "asemanviewport.h"

#include <QPointer>

class AsemanAbstractViewportType::Private
{
public:
    QPointer<QQuickItem> foregroundItem;
    QPointer<QQuickItem> backgroundItem;
    QPointer<AsemanViewport> viewport;
    QPointer<AsemanViewportTypeAttechedProperty> foregroundAttachedType;
    bool open;
};

AsemanAbstractViewportType::AsemanAbstractViewportType(QQuickItem *parent) :
    QQuickItem(parent)
{
    p = new Private;
    p->open = false;
}

QQuickItem *AsemanAbstractViewportType::foregroundItem() const
{
    return p->foregroundItem;
}

void AsemanAbstractViewportType::setForegroundItem(QQuickItem *foregroundItem)
{
    if (p->foregroundItem == foregroundItem)
        return;

    if (p->foregroundAttachedType)
    {
        disconnect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::gestureWidthChanged, this, &AsemanAbstractViewportType::gestureWidthChanged);
        disconnect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::maximumWidthChanged, this, &AsemanAbstractViewportType::maximumWidthChanged);
        disconnect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::touchToCloseChanged, this, &AsemanAbstractViewportType::touchToCloseChanged);
        disconnect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::blockBackChanged, this, &AsemanAbstractViewportType::blockBackChanged);
        disconnect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::typeTransformOriginChanged, this, &AsemanAbstractViewportType::typeTransformOriginChanged);
        disconnect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::openChanged, this, &AsemanAbstractViewportType::openChanged);
        disconnect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::sourceObjectChanged, this, &AsemanAbstractViewportType::sourceObjectChanged);
    }

    p->foregroundItem = foregroundItem;
    p->foregroundAttachedType = qobject_cast<AsemanViewportTypeAttechedProperty*>(qmlAttachedPropertiesObject<AsemanViewportType>(foregroundItem));

    if (p->foregroundAttachedType)
    {
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::gestureWidthChanged, this, &AsemanAbstractViewportType::gestureWidthChanged);
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::maximumWidthChanged, this, &AsemanAbstractViewportType::maximumWidthChanged);
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::touchToCloseChanged, this, &AsemanAbstractViewportType::touchToCloseChanged);
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::blockBackChanged, this, &AsemanAbstractViewportType::blockBackChanged);
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::typeTransformOriginChanged, this, &AsemanAbstractViewportType::typeTransformOriginChanged);
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::openChanged, this, &AsemanAbstractViewportType::openChanged);
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::sourceObjectChanged, this, &AsemanAbstractViewportType::sourceObjectChanged);
    }

    Q_EMIT foregroundItemChanged();
    Q_EMIT gestureWidthChanged();
    Q_EMIT maximumWidthChanged();
    Q_EMIT touchToCloseChanged();
    Q_EMIT openChanged();
    Q_EMIT blockBackChanged();
    Q_EMIT typeTransformOriginChanged();
    Q_EMIT sourceObjectChanged();
}

QQuickItem *AsemanAbstractViewportType::backgroundItem() const
{
    return p->backgroundItem;
}

void AsemanAbstractViewportType::setBackgroundItem(QQuickItem *backgroundItem)
{
    if (p->backgroundItem == backgroundItem)
        return;

    p->backgroundItem = backgroundItem;
    Q_EMIT backgroundItemChanged();
}

AsemanViewport *AsemanAbstractViewportType::viewport() const
{
    return p->viewport;
}

void AsemanAbstractViewportType::setViewport(AsemanViewport *viewport)
{
    if (p->viewport == viewport)
        return;

    p->viewport = viewport;
    Q_EMIT viewportChanged();
}

qreal AsemanAbstractViewportType::gestureWidth() const
{
    return p->foregroundAttachedType? p->foregroundAttachedType->gestureWidth() : 0;
}

bool AsemanAbstractViewportType::gestureWidthIsNull() const
{
    if (!p->foregroundAttachedType)
        return false;

    bool isNull;
    p->foregroundAttachedType->gestureWidth(&isNull);
    return isNull;
}

void AsemanAbstractViewportType::setGestureWidth(qreal gestureWidth)
{
    if (!p->foregroundAttachedType)
        return;

    p->foregroundAttachedType->setGestureWidth(gestureWidth);
}

qreal AsemanAbstractViewportType::maximumWidth() const
{
    return p->foregroundAttachedType? p->foregroundAttachedType->maximumWidth() : 0;
}

bool AsemanAbstractViewportType::maximumWidthIsNull() const
{
    if (!p->foregroundAttachedType)
        return false;

    bool isNull;
    p->foregroundAttachedType->maximumWidth(&isNull);
    return isNull;
}

void AsemanAbstractViewportType::setMaximumWidth(qreal maximumWidth)
{
    if (!p->foregroundAttachedType)
        return;

    p->foregroundAttachedType->setMaximumWidth(maximumWidth);
}

QPointF AsemanAbstractViewportType::typeTransformOrigin() const
{
    return p->foregroundAttachedType? p->foregroundAttachedType->typeTransformOrigin() : QPointF();
}

bool AsemanAbstractViewportType::typeTransformOriginIsNull() const
{
    if (!p->foregroundAttachedType)
        return false;

    bool isNull;
    p->foregroundAttachedType->typeTransformOrigin(&isNull);
    return isNull;
}

void AsemanAbstractViewportType::setTypeTransformOrigin(const QPointF &typeTransformOrigin)
{
    if (!p->foregroundAttachedType)
        return;

    p->foregroundAttachedType->setTypeTransformOrigin(typeTransformOrigin);
}

bool AsemanAbstractViewportType::touchToClose() const
{
    return p->foregroundAttachedType? p->foregroundAttachedType->touchToClose() : false;
}

bool AsemanAbstractViewportType::touchToCloseIsNull() const
{
    if (!p->foregroundAttachedType)
        return false;

    bool isNull;
    p->foregroundAttachedType->touchToClose(&isNull);
    return isNull;
}

void AsemanAbstractViewportType::setTouchToClose(bool touchToClose)
{
    if (!p->foregroundAttachedType)
        return;

    p->foregroundAttachedType->setTouchToClose(touchToClose);
}

bool AsemanAbstractViewportType::blockBack() const
{
    return p->foregroundAttachedType? p->foregroundAttachedType->blockBack() : false;
}

bool AsemanAbstractViewportType::blockBackIsNull() const
{
    if (!p->foregroundAttachedType)
        return false;

    bool isNull;
    p->foregroundAttachedType->blockBack(&isNull);
    return isNull;
}

void AsemanAbstractViewportType::setBlockBack(bool blockBack)
{
    if (!p->foregroundAttachedType)
        return;

    p->foregroundAttachedType->setBlockBack(blockBack);
}

QQuickItem *AsemanAbstractViewportType::sourceObject() const
{
    return p->foregroundAttachedType? p->foregroundAttachedType->sourceObject() : Q_NULLPTR;
}

bool AsemanAbstractViewportType::sourceObjectIsNull() const
{
    if (!p->foregroundAttachedType)
        return false;

    bool isNull;
    p->foregroundAttachedType->sourceObject(&isNull);
    return isNull;
}

void AsemanAbstractViewportType::setSourceObject(QQuickItem *item)
{
    if (!p->foregroundAttachedType)
        return;

    p->foregroundAttachedType->setSourceObject(item);
}

bool AsemanAbstractViewportType::open() const
{
    return p->foregroundAttachedType? p->foregroundAttachedType->open() : p->open;
}

void AsemanAbstractViewportType::setOpen(bool open)
{
    if (p->foregroundAttachedType)
        p->foregroundAttachedType->setOpen(open);

    if (p->open == open)
        return;

    p->open = open;
    Q_EMIT openChanged();
}

AsemanAbstractViewportType::~AsemanAbstractViewportType()
{
    delete p;
}

AsemanViewportTypeAttechedProperty *AsemanViewportType::qmlAttachedProperties(QObject *object)
{
    return new AsemanViewportTypeAttechedProperty(object);
}

AsemanViewportTypeAttechedProperty::AsemanViewportTypeAttechedProperty(QObject *parent) :
    QObject(parent),
    mSourceObject(Q_NULLPTR),
    mOpen(true)
{
}

qreal AsemanViewportTypeAttechedProperty::gestureWidth(bool *isNull) const
{
    if (isNull) *isNull = mGestureWidth.isNull();
    return mGestureWidth.toReal();
}

void AsemanViewportTypeAttechedProperty::setGestureWidth(qreal gestureWidth)
{
    if (mGestureWidth == gestureWidth)
        return;

    mGestureWidth = gestureWidth;
    Q_EMIT gestureWidthChanged();
}

qreal AsemanViewportTypeAttechedProperty::maximumWidth(bool *isNull) const
{
    if (isNull) *isNull = mMaximumWidth.isNull();
    return mMaximumWidth.toReal();

}

void AsemanViewportTypeAttechedProperty::setMaximumWidth(qreal maximumWidth)
{
    if (mMaximumWidth == maximumWidth)
        return;

    mMaximumWidth = maximumWidth;
    Q_EMIT maximumWidthChanged();
}

QPointF AsemanViewportTypeAttechedProperty::typeTransformOrigin(bool *isNull) const
{
    if (isNull) *isNull = mTypeTransformOrigin.isNull();
    return mTypeTransformOrigin;
}

void AsemanViewportTypeAttechedProperty::setTypeTransformOrigin(const QPointF &typeTransformOrigin)
{
    if (mTypeTransformOrigin == typeTransformOrigin)
        return;

    mTypeTransformOrigin = typeTransformOrigin;
    Q_EMIT typeTransformOriginChanged();
}

bool AsemanViewportTypeAttechedProperty::touchToClose(bool *isNull) const
{
    if (isNull) *isNull = mTouchToClose.isNull();
    return mTouchToClose.toBool();
}

void AsemanViewportTypeAttechedProperty::setTouchToClose(bool touchToClose)
{
    if (mTouchToClose == touchToClose)
        return;

    mTouchToClose = touchToClose;
    Q_EMIT touchToCloseChanged();
}

bool AsemanViewportTypeAttechedProperty::blockBack(bool *isNull) const
{
    if (isNull) *isNull = mBlockBack.isNull();
    return mBlockBack.toBool();
}

void AsemanViewportTypeAttechedProperty::setBlockBack(bool blockBack)
{
    if (mBlockBack == blockBack)
        return;

    mBlockBack = blockBack;
    Q_EMIT blockBackChanged();
}

QQuickItem *AsemanViewportTypeAttechedProperty::sourceObject(bool *isNull) const
{
    if (isNull) *isNull = mSourceObject.isNull();
    return mSourceObject;

}

void AsemanViewportTypeAttechedProperty::setSourceObject(QQuickItem *item)
{
    if (mSourceObject == item)
        return;

    mSourceObject = item;
    Q_EMIT sourceObjectChanged();
}

bool AsemanViewportTypeAttechedProperty::open() const
{
    return mOpen;
}

void AsemanViewportTypeAttechedProperty::setOpen(bool open)
{
    if (mOpen == open)
        return;

    mOpen = open;
    Q_EMIT openChanged();
}

AsemanViewportTypeAttechedProperty::~AsemanViewportTypeAttechedProperty()
{
}
