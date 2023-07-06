#include "asemanquickradiobuttoncontrol.h"
#include "asemanquickradiobuttongroup.h"

AsemanQuickRadioButtonControl::AsemanQuickRadioButtonControl(QQuickItem *parent)
    : AsemanQuickControlItem(parent)
{
}

AsemanQuickRadioButtonControl::~AsemanQuickRadioButtonControl()
{
}

bool AsemanQuickRadioButtonControl::checked() const
{
    return mChecked;
}

void AsemanQuickRadioButtonControl::setChecked(bool newChecked)
{
    if (mChecked == newChecked)
        return;
    mChecked = newChecked;
    if (mChecked)
        uncheckOthers();
    Q_EMIT checkedChanged();
}

void AsemanQuickRadioButtonControl::uncheckOthers()
{
    QList<QQuickItem*> childs;
    auto attached = qobject_cast<AsemanQuickRadioButtonGroupAttachedProperty*>(qmlAttachedPropertiesObject<AsemanQuickRadioButtonGroupAttachedCreator>(this, false));
    if (attached && attached->group())
    {
        for (auto b: attached->group()->buttons())
            childs << b;
    }
    else
    {
        auto parent = parentItem();
        if (!parent)
            return;

        childs = parent->childItems();
    }

    for (auto c: childs)
    {
        auto radio = qobject_cast<AsemanQuickRadioButtonControl*>(c);
        if (!radio)
            continue;
        if (radio == this)
            continue;

        radio->mChecked = false;
        Q_EMIT radio->checkedChanged();
    }
}
