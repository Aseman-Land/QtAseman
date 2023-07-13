#ifndef ASEMANQUICKCONTROLITEM_H
#define ASEMANQUICKCONTROLITEM_H

#include "asemanquickstyleditem.h"

class AsemanQuickControlItem : public AsemanQuickStyledItem
{
    Q_OBJECT
    Q_PROPERTY(AsemanQuickControlItem *nextTabOrder READ nextTabOrder WRITE setNextTabOrder NOTIFY nextTabOrderChanged)
    Q_PROPERTY(bool focusedInUsingKeyboard READ focusedInUsingKeyboard NOTIFY focusedInUsingKeyboardChanged)
    Q_PROPERTY(bool focusableUsingKeyboard READ focusableUsingKeyboard WRITE setFocusableUsingKeyboard NOTIFY focusableUsingKeyboardChanged)
    Q_PROPERTY(bool focusable READ focusable WRITE setFocusable NOTIFY focusableChanged)

public:
    AsemanQuickControlItem(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickControlItem();

    static QList<AsemanQuickControlItem*> findAllControls(const QQuickItem *item, bool recursive = true, bool focusablesOnly = false);

    AsemanQuickControlItem *nextTabOrder() const;
    void setNextTabOrder(AsemanQuickControlItem *newNextTabOrder);

    bool focusedInUsingKeyboard() const;

    bool focusableUsingKeyboard() const;
    void setFocusableUsingKeyboard(bool newFocusableUsingKeyboard);

    bool focusable() const;
    void setFocusable(bool newFocusable);

public Q_SLOTS:
    void focusNextItem();
    void focusPreviousItem();

Q_SIGNALS:
    void nextTabOrderChanged();
    void focusedInUsingKeyboardChanged();
    void focusableUsingKeyboardChanged();
    void focusableChanged();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void setFocusedInUsingKeyboard(bool newFocusedInUsingKeyboard);

private:
    QPointer<AsemanQuickControlItem> mNextTabOrder;
    QPointer<AsemanQuickControlItem> mPreviousTabOrder;
    bool mFocusedInUsingKeyboard = false;
    bool mFocusableUsingKeyboard = true;
    bool mFocusable = true;
};

#endif // ASEMANQUICKCONTROLITEM_H
