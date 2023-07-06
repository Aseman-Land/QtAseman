#ifndef ASEMANQUICKSCENEITEM_H
#define ASEMANQUICKSCENEITEM_H

#include "asemanquickcontrolitem.h"
#include "asemanquickstyleditem.h"

class AsemanQuickSceneItem: public AsemanQuickStyledItem
{
    Q_OBJECT
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)

public:
    AsemanQuickSceneItem(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickSceneItem();

    QList<AsemanQuickControlItem*> controls() const;

    static AsemanQuickSceneItem *findScene(const QQuickItem *item);

    QFont font() const;
    void setFont(const QFont &newFont);

Q_SIGNALS:
    void fontChanged();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseUngrabEvent() override;
    virtual void touchEvent(QTouchEvent *event) override;
    virtual void touchUngrabEvent() override;
    virtual void wheelEvent(QWheelEvent *event) override;

    static QObject *findParent(const QObject *obj);
    void checkAndCaptureFocus();

private:
    QFont mFont;

    struct PreviousFocus {
        AsemanQuickSceneItem *scene = nullptr;
        QQuickItem *item = nullptr;
    };

    PreviousFocus mPreviousFocused;
};

#endif // ASEMANQUICKSCENEITEM_H
