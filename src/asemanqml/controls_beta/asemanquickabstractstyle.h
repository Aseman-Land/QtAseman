#ifndef ASEMANQUICKABSTRACTSTYLE_H
#define ASEMANQUICKABSTRACTSTYLE_H

#include <QQuickItem>
#include <QFont>

#include "asemanquickboxsize.h"

class AsemanQuickAbstractStyle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(AsemanQuickBoxSize *padding READ padding WRITE setPadding NOTIFY paddingChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QVariantMap extra READ extra WRITE setExtra NOTIFY extraChanged)

public:
    AsemanQuickAbstractStyle(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickAbstractStyle();

    AsemanQuickBoxSize *padding() const;
    void setPadding(AsemanQuickBoxSize *newPadding);

    QFont font() const;
    void setFont(const QFont &newFont);

    QVariantMap extra() const;
    void setExtra(const QVariantMap &newExtra);

Q_SIGNALS:
    void paddingChanged();
    void fontChanged();
    void extraChanged();

private:
    AsemanQuickBoxSize *mPadding;
    QFont mFont;
    QVariantMap mExtra;
};

#endif // ASEMANQUICKABSTRACTSTYLE_H
