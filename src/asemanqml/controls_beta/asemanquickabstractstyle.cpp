#include "asemanquickabstractstyle.h"
#include "asemanquickstyleattachedproperty.h"

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
    if (mFont.has_value())
        return mFont.value();

    auto attached = qobject_cast<AsemanQuickStyleAttachedProperty*>(qmlAttachedPropertiesObject<AsemanQuickStyleProperty>(this, true));

    QFont font;
    font.setFamilies(attached->generalFontFamilies());
    qDebug() << font.families();
    return font;
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
