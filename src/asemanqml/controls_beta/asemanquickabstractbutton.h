#ifndef ASEMANQUICKABSTRACTBUTTON_H
#define ASEMANQUICKABSTRACTBUTTON_H

#include "asemanquickcontrolitem.h"

#include <QPointF>

class AsemanQuickAbstractButton : public AsemanQuickControlItem
{
    Q_OBJECT
    Q_PROPERTY(bool pressed READ getPressedStatus NOTIFY pressedChanged)
    Q_PROPERTY(int acceptableButtons READ acceptableButtons WRITE setAcceptableButtons NOTIFY acceptableButtonsChanged)
    Q_PROPERTY(bool hoverEnabled READ hoverEnabled WRITE setHoverEnabled NOTIFY hoverEnabledChanged)
    Q_PROPERTY(bool containsMouse READ containsMouse NOTIFY containsMouseChanged)
    Q_PROPERTY(QPointF cursorPosition READ cursorPosition NOTIFY cursorPositionChanged)

public:
    AsemanQuickAbstractButton(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickAbstractButton();

    bool getPressedStatus() const;

    int acceptableButtons() const;
    void setAcceptableButtons(int newAcceptableButtons);

    bool hoverEnabled() const;
    void setHoverEnabled(bool newHoverEnabled);

    bool containsMouse() const;
    QPointF cursorPosition() const;

Q_SIGNALS:
    void clicked(int buttons, const QPointF &position);
    void pressed(int buttons, const QPointF &position);
    void released(int buttons, const QPointF &position);
    void pressedChanged();
    void acceptableButtonsChanged();
    void hoverEnabledChanged();
    void containsMouseChanged();
    void cursorPositionChanged();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseUngrabEvent() override;
    virtual void touchEvent(QTouchEvent *event) override;
    virtual void touchUngrabEvent() override;
    virtual void wheelEvent(QWheelEvent *event) override;

private:
    void setPressed(bool pressed);
    void setContainsMouse(bool containsMouse);
    void setCursorPosition(const QPointF &cursorPosition);

private:
    bool mPressed = false;
    Qt::MouseButtons mAcceptableButtons = Qt::LeftButton;
    bool mHoverEnabled = false;
    bool mContainsMouse = false;
    QPointF mCursorPosition;
};

#endif // ASEMANQUICKABSTRACTBUTTON_H
