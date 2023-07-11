#include "asemanquickcolumnlayout.h"

AsemanQuickColumnLayout::AsemanQuickColumnLayout(QQuickItem *parent)
    : AsemanQuickLayout(parent)
{
}

AsemanQuickColumnLayout::~AsemanQuickColumnLayout()
{

}

void AsemanQuickColumnLayout::relocateChilds()
{
    const auto childs = childItems();

    qreal static_height = 0, h;
    int autoFillCount = 0;
    int visibleCount = 0;
    for (auto c: childs)
    {
        if (!c->isVisible())
            continue;

        visibleCount++;
        auto attached = getAttached(c);
        if (attached->mFillHeight)
        {
            autoFillCount++;
            continue;
        }

        h = c->implicitHeight();
        if (attached->mPreferredHeight > 0)
            h = attached->mPreferredHeight;

        c->setHeight(h);
        static_height += h + attached->mTopMargin + attached->mBottomMargin;
    }
    static_height += (visibleCount-1)*mSpacing;

    const qreal autoFillHeight = height() - static_height;
    const qreal standardAutoFillHeight = autoFillHeight / autoFillCount;

    for (auto c: childs)
    {
        if (!c->isVisible())
            continue;
        auto attached = getAttached(c);
        if (!attached->mFillHeight)
            continue;

        c->setHeight(standardAutoFillHeight);
    }

    qreal lastY = 0;
    qreal w, maxW = 0;
    for (auto c: childs)
    {
        if (!c->isVisible())
            continue;

        auto attached = getAttached(c);

        c->setY(lastY + attached->mTopMargin);

        w = c->implicitWidth();
        if (attached->mFillWidth)
            w = width();
        else if (attached->mPreferredWidth > 0)
            w = attached->mPreferredWidth;

        c->setWidth(w);
        maxW = std::max(maxW, c->x() + c->width());

        switch (attached->mAlignment & Qt::AlignHorizontal_Mask)
        {
        case Qt::AlignLeft:
            c->setX(0);
            break;
        case Qt::AlignRight:
            c->setX(width() - c->width());
            break;
        case Qt::AlignHCenter:
            c->setX(width()/2 - c->width()/2);
            break;
        }

        if (c->height() > 0)
            lastY += c->height() + attached->mTopMargin + attached->mBottomMargin + mSpacing;
    }
    if (visibleCount)
        lastY -= mSpacing;

    setImplicitHeight(lastY);
    setImplicitWidth(maxW);
}

qreal AsemanQuickColumnLayout::spacing() const
{
    return mSpacing;
}

void AsemanQuickColumnLayout::setSpacing(qreal newSpacing)
{
    if (qFuzzyCompare(mSpacing, newSpacing))
        return;
    mSpacing = newSpacing;
    reloadDelayed();
    Q_EMIT spacingChanged();
}
