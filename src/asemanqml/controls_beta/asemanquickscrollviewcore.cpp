#include "asemanquickscrollviewcore.h"

AsemanQuickScrollViewCore::AsemanQuickScrollViewCore(QQuickItem *parent)
    : AsemanQuickControlItem(parent)
{
}

AsemanQuickScrollViewCore::~AsemanQuickScrollViewCore()
{
}

QQuickItem *AsemanQuickScrollViewCore::flickArea() const
{
    return mFlickArea;
}

void AsemanQuickScrollViewCore::setFlickArea(QQuickItem *newFlickArea)
{
    if (mFlickArea == newFlickArea)
        return;
    if (mFlickArea)
        mFlickArea->removeEventFilter(this);

    mFlickArea = newFlickArea;
    if (mFlickArea)
        mFlickArea->installEventFilter(this);

    Q_EMIT flickAreaChanged();
}

bool AsemanQuickScrollViewCore::eventFilter(QObject *o, QEvent *e)
{
    if (o == mFlickArea)
    {
        switch (static_cast<int>(e->type()))
        {
        case QEvent::MouseMove:
            return true;
            break;

        case QEvent::Wheel:
            break;
        }
    }

    return AsemanQuickControlItem::eventFilter(o, e);
}
