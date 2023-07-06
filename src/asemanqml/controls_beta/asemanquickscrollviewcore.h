#ifndef ASEMANQUICKSCROLLVIEWCORE_H
#define ASEMANQUICKSCROLLVIEWCORE_H

#include "asemanquickcontrolitem.h"

class AsemanQuickScrollViewCore : public AsemanQuickControlItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *flickArea READ flickArea WRITE setFlickArea NOTIFY flickAreaChanged)
    Q_CLASSINFO("DefaultProperty", "flickArea")

public:
    AsemanQuickScrollViewCore(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickScrollViewCore();

    QQuickItem *flickArea() const;
    void setFlickArea(QQuickItem *newFlickArea);

    bool eventFilter(QObject *o, QEvent *e);

Q_SIGNALS:
    void flickAreaChanged();

private:
    QPointer<QQuickItem> mFlickArea;
};

#endif // ASEMANQUICKSCROLLVIEWCORE_H
