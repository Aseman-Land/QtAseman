#include "asemanquickboxsize.h"

AsemanQuickBoxSize::AsemanQuickBoxSize(QObject *parent)
    : QObject(parent)
{

}

AsemanQuickBoxSize::~AsemanQuickBoxSize()
{

}

qint32 AsemanQuickBoxSize::left() const
{
    return mPadding.mLeft;
}

void AsemanQuickBoxSize::setLeft(qint32 newLeft)
{
    if (mPadding.mLeft == newLeft)
        return;
    mPadding.mLeft = newLeft;
    Q_EMIT leftChanged();
}

qint32 AsemanQuickBoxSize::top() const
{
    return mPadding.mTop;
}

void AsemanQuickBoxSize::setTop(qint32 newTop)
{
    if (mPadding.mTop == newTop)
        return;
    mPadding.mTop = newTop;
    Q_EMIT topChanged();
}

qint32 AsemanQuickBoxSize::right() const
{
    return mPadding.mRight;
}

void AsemanQuickBoxSize::setRight(qint32 newRight)
{
    if (mPadding.mRight == newRight)
        return;
    mPadding.mRight = newRight;
    Q_EMIT rightChanged();
}

qint32 AsemanQuickBoxSize::bottom() const
{
    return mPadding.mBottom;
}

void AsemanQuickBoxSize::setBottom(qint32 newBottom)
{
    if (mPadding.mBottom == newBottom)
        return;
    mPadding.mBottom = newBottom;
    Q_EMIT bottomChanged();
}

AsemanQuickBoxSize::Padding AsemanQuickBoxSize::padding() const
{
    return mPadding;
}

void AsemanQuickBoxSize::setPadding(const Padding &newPadding)
{
    mPadding = newPadding;
}
