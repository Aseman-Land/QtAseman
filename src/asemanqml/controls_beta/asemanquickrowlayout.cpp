#include "asemanquickrowlayout.h"

AsemanQuickRowLayout::AsemanQuickRowLayout(QQuickItem *parent)
    : AsemanQuickLayout(parent)
{

}

AsemanQuickRowLayout::~AsemanQuickRowLayout()
{

}

void AsemanQuickRowLayout::relocateChilds()
{
    const bool mirrored = (mLayoutDirection == Qt::RightToLeft);

    const auto childs = childItems();

    qreal static_width = 0, w;
    int autoFillCount = 0;
    int visibleCount = 0;
    for (auto c: childs)
    {
        if (!c->isVisible())
            continue;

        visibleCount++;
        auto attached = qobject_cast<AsemanQuickLayoutProperty*>(qmlAttachedPropertiesObject<AsemanQuickLayout>(c, true));
        if (attached->mFillWidth)
        {
            autoFillCount++;
            continue;
        }

        w = c->implicitWidth();
        if (attached->mPreferredWidth > 0)
            w = attached->mPreferredWidth;

        c->setWidth(w);
        static_width += w + attached->mTopMargin + attached->mBottomMargin;
    }
    static_width += (visibleCount-1)*mSpacing;

    const qreal autoFillWidth = width() - static_width;
    const qreal standardAutoFillWidth = autoFillWidth / autoFillCount;

    for (auto c: childs)
    {
        if (!c->isVisible())
            continue;
        auto attached = qobject_cast<AsemanQuickLayoutProperty*>(qmlAttachedPropertiesObject<AsemanQuickLayout>(c, true));
        if (!attached->mFillWidth)
            continue;

        c->setWidth(standardAutoFillWidth);
    }

    qreal lastX = 0;
    qreal h, maxH = 0;
    for (auto c: childs)
    {
        if (!c->isVisible())
            continue;

        auto attached = qobject_cast<AsemanQuickLayoutProperty*>(qmlAttachedPropertiesObject<AsemanQuickLayout>(c, true));

        const auto newX = lastX + attached->mLeftMargin;
        if (mirrored)
            c->setX(width() - newX - c->width());
        else
            c->setX(newX);

        h = c->implicitHeight();
        if (attached->mFillHeight)
            h = height();
        else if (attached->mPreferredHeight > 0)
            h = attached->mPreferredHeight;

        c->setHeight(h);
        maxH = std::max(maxH, c->y() + c->height());

        switch (attached->mAlignment & Qt::AlignVertical_Mask)
        {
        case Qt::AlignTop:
            c->setY(0);
            break;
        case Qt::AlignBottom:
            c->setY(height() - c->height());
            break;
        case Qt::AlignVCenter:
            c->setY(height()/2 - c->height()/2);
            break;
        }

        if (c->width() > 0)
            lastX += c->width() + attached->mLeftMargin + attached->mRightMargin + mSpacing;
    }
    if (visibleCount)
        lastX -= mSpacing;

    setImplicitWidth(lastX);
    setImplicitHeight(maxH);
}

int AsemanQuickRowLayout::layoutDirection() const
{
    return mLayoutDirection;
}

void AsemanQuickRowLayout::setLayoutDirection(int newLayoutDirection)
{
    if (mLayoutDirection == newLayoutDirection)
        return;
    mLayoutDirection = newLayoutDirection;
    reloadDelayed();
    Q_EMIT layoutDirectionChanged();
}

qreal AsemanQuickRowLayout::spacing() const
{
    return mSpacing;
}

void AsemanQuickRowLayout::setSpacing(qreal newSpacing)
{
    if (qFuzzyCompare(mSpacing, newSpacing))
        return;
    mSpacing = newSpacing;
    reloadDelayed();
    Q_EMIT spacingChanged();
}