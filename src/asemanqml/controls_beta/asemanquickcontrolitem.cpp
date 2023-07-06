#include "asemanquickcontrolitem.h"
#include "asemanquicksceneitem.h"

#include <QKeyEvent>

AsemanQuickControlItem::AsemanQuickControlItem(QQuickItem *parent)
    : AsemanQuickStyledItem(parent)
{
    setSourceItem(this);
    connect(this, &AsemanQuickControlItem::focusChanged, this, [this](){
        if (!hasFocus())
            setFocusedInUsingKeyboard(false);
    });
}

AsemanQuickControlItem::~AsemanQuickControlItem()
{
}

void AsemanQuickControlItem::focusNextItem()
{
    auto next = mNextTabOrder;
    if (!next)
    {
        const auto scene = AsemanQuickSceneItem::findScene(this);
        const auto controls = findAllControls(scene, true, true);
        const auto index = controls.indexOf(this);
        if (index >= 0 && index < controls.size()-1)
            next = controls.at(index+1);
        else if (index > 0)
            next = controls.first();
    }

    if (next)
    {
        next->setFocus(true);
        next->forceActiveFocus();
        next->setFocusedInUsingKeyboard(true);
    }
}

void AsemanQuickControlItem::focusPreviousItem()
{
    auto prev = mPreviousTabOrder;
    if (!prev)
    {
        const auto scene = AsemanQuickSceneItem::findScene(this);
        const auto controls = findAllControls(scene, true, true);
        const auto index = controls.indexOf(this);
        if (index > 0)
            prev = controls.at(index-1);
        else if (index < controls.size()-1)
            prev = controls.last();
    }

    if (prev)
    {
        prev->setFocus(true);
        prev->forceActiveFocus();
        prev->setFocusedInUsingKeyboard(true);
    }

}

void AsemanQuickControlItem::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Tab:
        if (e->modifiers() & Qt::ShiftModifier)
            focusPreviousItem();
        else
            focusNextItem();
        break;

    default:
        QQuickItem::keyPressEvent(e);
        break;
    }

    e->accept();
}

bool AsemanQuickControlItem::focusableUsingKeyboard() const
{
    return mFocusableUsingKeyboard;
}

void AsemanQuickControlItem::setFocusableUsingKeyboard(bool newFocusableUsingKeyboard)
{
    if (mFocusableUsingKeyboard == newFocusableUsingKeyboard)
        return;
    mFocusableUsingKeyboard = newFocusableUsingKeyboard;
    Q_EMIT focusableUsingKeyboardChanged();
}

bool AsemanQuickControlItem::focusedInUsingKeyboard() const
{
    return mFocusedInUsingKeyboard;
}

void AsemanQuickControlItem::setFocusedInUsingKeyboard(bool newFocusedInUsingKeyboard)
{
    if (mFocusedInUsingKeyboard == newFocusedInUsingKeyboard)
        return;
    mFocusedInUsingKeyboard = newFocusedInUsingKeyboard;
    Q_EMIT focusedInUsingKeyboardChanged();
}

AsemanQuickControlItem *AsemanQuickControlItem::nextTabOrder() const
{
    return mNextTabOrder;
}

void AsemanQuickControlItem::setNextTabOrder(AsemanQuickControlItem *newNextTabOrder)
{
    if (mNextTabOrder == newNextTabOrder)
        return;

    if (mNextTabOrder)
    {
        mNextTabOrder->mPreviousTabOrder = nullptr;
        Q_EMIT mNextTabOrder->nextTabOrderChanged();
    }

    mNextTabOrder = newNextTabOrder;
    if (mNextTabOrder)
    {
        mNextTabOrder->mPreviousTabOrder = this;
        Q_EMIT mNextTabOrder->nextTabOrderChanged();
    }

    Q_EMIT nextTabOrderChanged();
}

QList<AsemanQuickControlItem *> AsemanQuickControlItem::findAllControls(const QQuickItem *item, bool recursive, bool focusablesOnly)
{
    QList<AsemanQuickControlItem*> res;
    if (!item)
        return res;

    for (auto obj: item->childItems())
    {
        auto scene = qobject_cast<AsemanQuickSceneItem*>(obj);
        if (scene)
            continue;

        auto child = qobject_cast<AsemanQuickControlItem*>(obj);
        if (child && (!focusablesOnly || child->mFocusableUsingKeyboard))
            res << child;
        if (recursive)
            res << findAllControls(obj, true, focusablesOnly);
    }

    return res;
}
