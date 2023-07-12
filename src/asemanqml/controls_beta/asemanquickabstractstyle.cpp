#include "asemanquickabstractstyle.h"
#include "asemanquickstyleattachedproperty.h"

#include <QGuiApplication>

AsemanQuickAbstractStyle::AsemanQuickAbstractStyle(QQuickItem *parent)
    : QQuickItem(parent)
{
    mPadding = new AsemanQuickBoxSize(this);
}

AsemanQuickAbstractStyle::~AsemanQuickAbstractStyle()
{

}

AsemanQuickBoxSize *AsemanQuickAbstractStyle::padding() const
{
    return mPadding;
}

void AsemanQuickAbstractStyle::setPadding(AsemanQuickBoxSize *newPadding)
{
    if (mPadding->padding() == newPadding->padding())
        return;
    mPadding->setPadding(newPadding->padding());
    Q_EMIT paddingChanged();
}

QFont AsemanQuickAbstractStyle::font() const
{
    return mFont.value_or(qApp->font());
}

void AsemanQuickAbstractStyle::setFont(const QFont &newFont)
{
    if (mFont == newFont)
        return;
    mFont = newFont;
    Q_EMIT fontChanged();
}

QVariantMap AsemanQuickAbstractStyle::extra() const
{
    return mExtra;
}

void AsemanQuickAbstractStyle::setExtra(const QVariantMap &newExtra)
{
    if (mExtra == newExtra)
        return;
    mExtra = newExtra;
    Q_EMIT extraChanged();
}
