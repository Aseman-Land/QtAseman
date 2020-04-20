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
};

AsemanAbstractViewportType::AsemanAbstractViewportType(QQuickItem *parent) :
    QQuickItem(parent)
{
    p = new Private;
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
        disconnect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::touchToCloseChanged, this, &AsemanAbstractViewportType::touchToCloseChanged);
    }

    p->foregroundItem = foregroundItem;
    p->foregroundAttachedType = qobject_cast<AsemanViewportTypeAttechedProperty*>(qmlAttachedPropertiesObject<AsemanViewportType>(foregroundItem));

    if (p->foregroundAttachedType)
    {
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::gestureWidthChanged, this, &AsemanAbstractViewportType::gestureWidthChanged);
        connect(p->foregroundAttachedType, &AsemanViewportTypeAttechedProperty::touchToCloseChanged, this, &AsemanAbstractViewportType::touchToCloseChanged);
    }

    Q_EMIT foregroundItemChanged();
    Q_EMIT gestureWidthChanged();
    Q_EMIT touchToCloseChanged();
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

AsemanAbstractViewportType::~AsemanAbstractViewportType()
{
    delete p;
}

AsemanViewportTypeAttechedProperty *AsemanViewportType::qmlAttachedProperties(QObject *object)
{
    return new AsemanViewportTypeAttechedProperty(object);
}

AsemanViewportTypeAttechedProperty::AsemanViewportTypeAttechedProperty(QObject *parent) :
    QObject(parent)
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

AsemanViewportTypeAttechedProperty::~AsemanViewportTypeAttechedProperty()
{
}
