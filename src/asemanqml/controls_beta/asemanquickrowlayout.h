#ifndef ASEMANQUICKROWLAYOUT_H
#define ASEMANQUICKROWLAYOUT_H

#include "asemanquicklayout.h"

class AsemanQuickRowLayout : public AsemanQuickLayout
{
    Q_OBJECT
    Q_PROPERTY(int layoutDirection READ layoutDirection WRITE setLayoutDirection NOTIFY layoutDirectionChanged)
    Q_PROPERTY(qreal spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)

public:
    AsemanQuickRowLayout(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickRowLayout();

    qreal spacing() const;
    void setSpacing(qreal newSpacing);

    int layoutDirection() const;
    void setLayoutDirection(int newLayoutDirection);

Q_SIGNALS:
    void spacingChanged();
    void layoutDirectionChanged();

protected:
    void relocateChilds() override;

private:
    qreal mSpacing = 4;
    int mLayoutDirection = Qt::LeftToRight;
};

#endif // ASEMANQUICKROWLAYOUT_H
