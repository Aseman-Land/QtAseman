#ifndef ASEMANABSTRACTVIEWPORTTYPE_H
#define ASEMANABSTRACTVIEWPORTTYPE_H

#include <QQuickItem>

class AsemanViewport;
class AsemanAbstractViewportType : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* backgroundItem READ backgroundItem WRITE setBackgroundItem NOTIFY backgroundItemChanged)
    Q_PROPERTY(QQuickItem* foregroundItem READ foregroundItem WRITE setForegroundItem NOTIFY foregroundItemChanged)
    Q_PROPERTY(AsemanViewport* viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(bool open READ open WRITE setOpen NOTIFY openChanged)

    Q_PROPERTY(qreal gestureWidth READ gestureWidth WRITE setGestureWidth NOTIFY gestureWidthChanged)
    Q_PROPERTY(bool gestureWidthIsNull READ gestureWidthIsNull NOTIFY gestureWidthChanged)

    Q_PROPERTY(bool touchToClose READ touchToClose WRITE setTouchToClose NOTIFY touchToCloseChanged)
    Q_PROPERTY(bool touchToCloseIsNull READ touchToCloseIsNull NOTIFY touchToCloseChanged)

    Q_PROPERTY(bool blockBack READ blockBack WRITE setBlockBack NOTIFY blockBackChanged)
    Q_PROPERTY(bool blockBackIsNull READ blockBackIsNull NOTIFY blockBackChanged)

    class Private;

public:
    AsemanAbstractViewportType(QQuickItem *parent = Q_NULLPTR);
    virtual ~AsemanAbstractViewportType();

    QQuickItem *foregroundItem() const;
    void setForegroundItem(QQuickItem *foregroundItem);

    QQuickItem *backgroundItem() const;
    void setBackgroundItem(QQuickItem *backgroundItem);

    AsemanViewport *viewport() const;
    void setViewport(AsemanViewport *viewport);

    qreal gestureWidth() const;
    bool gestureWidthIsNull() const;
    void setGestureWidth(qreal gestureWidth);

    bool touchToClose() const;
    bool touchToCloseIsNull() const;
    void setTouchToClose(bool touchToClose);

    bool blockBack() const;
    bool blockBackIsNull() const;
    void setBlockBack(bool blockBack);

    bool open() const;
    void setOpen(bool open);

Q_SIGNALS:
    void gestureWidthChanged();
    void touchToCloseChanged();
    void blockBackChanged();
    void foregroundItemChanged();
    void backgroundItemChanged();
    void viewportChanged();
    void openChanged();

private:
    Private *p;
};

class AsemanViewportTypeAttechedProperty;
class AsemanViewportType : public QObject
{
    Q_OBJECT
public:
    static AsemanViewportTypeAttechedProperty *qmlAttachedProperties(QObject *object);
};

class AsemanViewportTypeAttechedProperty : public QObject {
    Q_OBJECT
    Q_PROPERTY(qreal gestureWidth READ gestureWidth WRITE setGestureWidth NOTIFY gestureWidthChanged)
    Q_PROPERTY(bool touchToClose READ touchToClose WRITE setTouchToClose NOTIFY touchToCloseChanged)
    Q_PROPERTY(bool blockBack READ blockBack WRITE setBlockBack NOTIFY blockBackChanged)
    Q_PROPERTY(bool open READ open WRITE setOpen NOTIFY openChanged)

public:
    AsemanViewportTypeAttechedProperty(QObject *parent);
    virtual ~AsemanViewportTypeAttechedProperty();

    qreal gestureWidth(bool *isNull = Q_NULLPTR) const;
    void setGestureWidth(qreal gestureWidth);

    bool touchToClose(bool *isNull = Q_NULLPTR) const;
    void setTouchToClose(bool touchToClose);

    bool blockBack(bool *isNull = Q_NULLPTR) const;
    void setBlockBack(bool blockBack);

    bool open() const;
    void setOpen(bool open);

Q_SIGNALS:
    void gestureWidthChanged();
    void touchToCloseChanged();
    void blockBackChanged();
    void openChanged();

private:
    QVariant mGestureWidth;
    QVariant mTouchToClose;
    QVariant mBlockBack;
    bool mOpen;
};

QML_DECLARE_TYPEINFO(AsemanViewportType, QML_HAS_ATTACHED_PROPERTIES)

#endif // ASEMANABSTRACTVIEWPORTTYPE_H
