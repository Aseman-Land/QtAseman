#include "asemanquicksceneitem.h"

#include <QQuickWindow>
#include <QTimer>

AsemanQuickSceneItem::AsemanQuickSceneItem(QQuickItem *parent)
    : AsemanQuickStyledItem(parent)
{
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setSourceItem(this);

    connect(this, &QQuickItem::visibleChanged, this, &AsemanQuickSceneItem::checkAndCaptureFocus, Qt::QueuedConnection);
    QMetaObject::invokeMethod(this, &AsemanQuickSceneItem::checkAndCaptureFocus, Qt::QueuedConnection);
}

void AsemanQuickSceneItem::checkAndCaptureFocus()
{
    auto scene = this;
    QQuickItem *itemToFocus = nullptr;
    if (!isVisible())
    {
        itemToFocus = mPreviousFocused.item;
        scene = mPreviousFocused.scene;
    }
    if (!scene)
        return;

    const auto controls = AsemanQuickControlItem::findAllControls(scene, true, true);
    if (controls.isEmpty())
        return;

    auto win = window();
    if (win)
    {
        mPreviousFocused.item = win->activeFocusItem();
        mPreviousFocused.scene = findScene(mPreviousFocused.item);
    }

    auto c = itemToFocus? itemToFocus : controls.first();
    c->setFocus(true);
    c->forceActiveFocus();
}

AsemanQuickSceneItem::~AsemanQuickSceneItem()
{
}

QList<AsemanQuickControlItem *> AsemanQuickSceneItem::controls() const
{
    return AsemanQuickControlItem::findAllControls(this, true, false);
}

AsemanQuickSceneItem *AsemanQuickSceneItem::findScene(const QQuickItem *item)
{
    if (!item)
        return nullptr;

    auto parent = findParent(item);
    while (parent)
    {
        auto obj = qobject_cast<AsemanQuickSceneItem*>(parent);
        if (obj)
            return obj;

        parent = findParent(parent);
    }
    return nullptr;
}

void AsemanQuickSceneItem::mouseMoveEvent(QMouseEvent *e)
{
    e->accept();
}

void AsemanQuickSceneItem::mousePressEvent(QMouseEvent *e)
{
    e->accept();
}

void AsemanQuickSceneItem::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();
}

void AsemanQuickSceneItem::mouseUngrabEvent()
{
}

void AsemanQuickSceneItem::touchEvent(QTouchEvent *e)
{
    e->accept();
}

void AsemanQuickSceneItem::touchUngrabEvent()
{
}

void AsemanQuickSceneItem::wheelEvent(QWheelEvent *e)
{
    e->accept();
}

QObject *AsemanQuickSceneItem::findParent(const QObject *obj)
{
    auto *item = qobject_cast<const QQuickItem*>(obj);
    if (item && item->parentItem())
        return item->parentItem();
    else
        return obj->parent();
}

QFont AsemanQuickSceneItem::font() const
{
    return mFont;
}

void AsemanQuickSceneItem::setFont(const QFont &newFont)
{
    if (mFont == newFont)
        return;
    mFont = newFont;
    Q_EMIT fontChanged();
}
