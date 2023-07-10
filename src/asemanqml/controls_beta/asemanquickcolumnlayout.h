#ifndef ASEMANQUICKCOLUMNLAYOUT_H
#define ASEMANQUICKCOLUMNLAYOUT_H

#include "asemanquicklayout.h"

class AsemanQuickColumnLayout : public AsemanQuickLayout
{
    Q_OBJECT
    Q_PROPERTY(qreal spacing READ spacing WRITE setSpacing NOTIFY spacingChanged)

public:
    AsemanQuickColumnLayout(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickColumnLayout();

    qreal spacing() const;
    void setSpacing(qreal newSpacing);

Q_SIGNALS:
    void spacingChanged();

protected:
    void relocateChilds() override;

private:
    qreal mSpacing = 4;
};

#endif // ASEMANQUICKCOLUMNLAYOUT_H
