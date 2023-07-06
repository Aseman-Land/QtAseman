#include "asemanquickabstractbutton.h"

AsemanQuickAbstractButton::AsemanQuickAbstractButton(QQuickItem *parent)
    : AsemanQuickControlItem(parent)
{
    setAcceptedMouseButtons(mAcceptableButtons);
}

AsemanQuickAbstractButton::~AsemanQuickAbstractButton()
{
}

bool AsemanQuickAbstractButton::getPressedStatus() const
{
    return mPressed;
}

int AsemanQuickAbstractButton::acceptableButtons() const
{
    return mAcceptableButtons;
}

void AsemanQuickAbstractButton::setAcceptableButtons(int _acceptableButtons)
{
    auto acceptableButtons = static_cast<Qt::MouseButton>(_acceptableButtons);
    if (mAcceptableButtons == acceptableButtons)
        return;

    mAcceptableButtons = acceptableButtons;
    setAcceptedMouseButtons(mAcceptableButtons);
    Q_EMIT acceptableButtonsChanged();
}

bool AsemanQuickAbstractButton::hoverEnabled() const
{
    return mHoverEnabled;
}

void AsemanQuickAbstractButton::setHoverEnabled(bool newHoverEnabled)
{
    if (mHoverEnabled == newHoverEnabled)
        return;
    mHoverEnabled = newHoverEnabled;
    setAcceptHoverEvents(mHoverEnabled);
    Q_EMIT hoverEnabledChanged();
}

bool AsemanQuickAbstractButton::containsMouse() const
{
    return mContainsMouse;
}

QPointF AsemanQuickAbstractButton::cursorPosition() const
{
    return mCursorPosition;
}

void AsemanQuickAbstractButton::mouseMoveEvent(QMouseEvent *e)
{
    e->accept();
    setCursorPosition(e->pos());
}

void AsemanQuickAbstractButton::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    setCursorPosition(e->pos());
    setPressed(true);
}

void AsemanQuickAbstractButton::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();
    setCursorPosition(e->pos());
    setPressed(false);
}

void AsemanQuickAbstractButton::mouseUngrabEvent()
{
    setPressed(false);
}

void AsemanQuickAbstractButton::touchEvent(QTouchEvent *e)
{
    e->accept();
    if (e->touchPoints().count())
        setCursorPosition(e->touchPoints().first().pos());
    setPressed(true);
}

void AsemanQuickAbstractButton::touchUngrabEvent()
{
    setPressed(false);
}

void AsemanQuickAbstractButton::wheelEvent(QWheelEvent *e)
{
    e->accept();
    setCursorPosition(e->position());
}

void AsemanQuickAbstractButton::setPressed(bool pressed)
{
    if (mPressed == pressed)
        return;

    mPressed = pressed;
    Q_EMIT pressedChanged();
}

void AsemanQuickAbstractButton::setContainsMouse(bool containsMouse)
{
    if (mContainsMouse == containsMouse)
        return;

    mContainsMouse = containsMouse;
    Q_EMIT containsMouseChanged();
}

void AsemanQuickAbstractButton::setCursorPosition(const QPointF &cursorPosition)
{
    if (mCursorPosition == cursorPosition)
        return;

    mCursorPosition = cursorPosition;
    Q_EMIT cursorPositionChanged();
}
