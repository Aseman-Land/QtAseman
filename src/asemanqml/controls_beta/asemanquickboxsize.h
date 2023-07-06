#ifndef ASEMANQUICKBOXSIZE_H
#define ASEMANQUICKBOXSIZE_H

#include <QObject>

class AsemanQuickBoxSize: public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(qint32 top READ top WRITE setTop NOTIFY topChanged)
    Q_PROPERTY(qint32 right READ right WRITE setRight NOTIFY rightChanged)
    Q_PROPERTY(qint32 bottom READ bottom WRITE setBottom NOTIFY bottomChanged)

public:
    AsemanQuickBoxSize(QObject *parent = nullptr);
    virtual ~AsemanQuickBoxSize();

    qint32 left() const;
    void setLeft(qint32 newLeft);

    qint32 top() const;
    void setTop(qint32 newTop);

    qint32 right() const;
    void setRight(qint32 newRight);

    qint32 bottom() const;
    void setBottom(qint32 newBottom);

    struct Padding {
        qint32 mLeft = 0;
        qint32 mTop = 0;
        qint32 mRight = 0;
        qint32 mBottom = 0;

        bool operator==(const Padding &b) const {
            return mLeft == b.mLeft &&
                   mRight == b.mRight &&
                   mTop == b.mTop &&
                   mBottom == b.mBottom;
        }
    };

    Padding padding() const;
    void setPadding(const Padding &newPadding);

Q_SIGNALS:
    void leftChanged();
    void topChanged();
    void rightChanged();
    void bottomChanged();

private:
    Padding mPadding;
};

#endif // ASEMANQUICKBOXSIZE_H
