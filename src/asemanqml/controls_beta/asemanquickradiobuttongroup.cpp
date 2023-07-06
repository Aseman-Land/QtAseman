#include "asemanquickradiobuttongroup.h"

AsemanQuickRadioButtonGroup::AsemanQuickRadioButtonGroup(QObject *parent)
    : QObject(parent)
{
}

AsemanQuickRadioButtonGroup::~AsemanQuickRadioButtonGroup()
{
}

QQmlListProperty<AsemanQuickRadioButtonControl> AsemanQuickRadioButtonGroup::items()
{
    return QQmlListProperty<AsemanQuickRadioButtonControl>(this, &mButtons,
                                                           QQmlListProperty<AsemanQuickRadioButtonControl>::AppendFunction(append),
                                                           QQmlListProperty<AsemanQuickRadioButtonControl>::CountFunction(count),
                                                           QQmlListProperty<AsemanQuickRadioButtonControl>::AtFunction(at),
                                                           QQmlListProperty<AsemanQuickRadioButtonControl>::ClearFunction(clear) );
}

void AsemanQuickRadioButtonGroup::append(QQmlListProperty<AsemanQuickRadioButtonControl> *p, AsemanQuickRadioButtonControl *v)
{
    AsemanQuickRadioButtonGroup *aobj = static_cast<AsemanQuickRadioButtonGroup*>(p->object);
    aobj->addButton(v);
}

int AsemanQuickRadioButtonGroup::count(QQmlListProperty<AsemanQuickRadioButtonControl> *p)
{
    AsemanQuickRadioButtonGroup *aobj = static_cast<AsemanQuickRadioButtonGroup*>(p->object);
    return aobj->mButtons.count();
}

AsemanQuickRadioButtonControl *AsemanQuickRadioButtonGroup::at(QQmlListProperty<AsemanQuickRadioButtonControl> *p, int idx)
{
    AsemanQuickRadioButtonGroup *aobj = static_cast<AsemanQuickRadioButtonGroup*>(p->object);
    return aobj->mButtons.at(idx);
}

void AsemanQuickRadioButtonGroup::clear(QQmlListProperty<AsemanQuickRadioButtonControl> *p)
{
    AsemanQuickRadioButtonGroup *aobj = static_cast<AsemanQuickRadioButtonGroup*>(p->object);
    while (aobj->mButtons.count())
        aobj->removeButton(aobj->mButtons.takeFirst());

    Q_EMIT aobj->itemsChanged();
}

QList<AsemanQuickRadioButtonControl *> AsemanQuickRadioButtonGroup::buttons() const
{
    return mButtons;
}

void AsemanQuickRadioButtonGroup::addButton(AsemanQuickRadioButtonControl *r)
{
    if (mButtons.contains(r))
        return;

    auto attached = qobject_cast<AsemanQuickRadioButtonGroupAttachedProperty*>(qmlAttachedPropertiesObject<AsemanQuickRadioButtonGroupAttachedCreator>(r, true));
    attached->setGroup(this);
    mButtons << r;

    connect(r, &QObject::destroyed, this, [this, r](){
        mButtons.removeAll(r);
        Q_EMIT itemsChanged();
    });

    Q_EMIT itemsChanged();
}

void AsemanQuickRadioButtonGroup::removeButton(AsemanQuickRadioButtonControl *r)
{
    auto attached = qobject_cast<AsemanQuickRadioButtonGroupAttachedProperty*>(qmlAttachedPropertiesObject<AsemanQuickRadioButtonGroupAttachedCreator>(r, true));
    if (attached->group() == this)
        attached->setGroup(nullptr);

    if (mButtons.contains(r))
    {
        mButtons.removeAll(r);
        Q_EMIT itemsChanged();
    }
}


AsemanQuickRadioButtonGroupAttachedProperty::AsemanQuickRadioButtonGroupAttachedProperty(QObject *parent)
    : QObject(parent)
{
}

AsemanQuickRadioButtonGroupAttachedProperty::~AsemanQuickRadioButtonGroupAttachedProperty()
{
}

AsemanQuickRadioButtonGroup *AsemanQuickRadioButtonGroupAttachedProperty::group() const
{
    return mGroup;
}

void AsemanQuickRadioButtonGroupAttachedProperty::setGroup(AsemanQuickRadioButtonGroup *newGroup)
{
    if (mGroup == newGroup)
        return;

    auto radio = qobject_cast<AsemanQuickRadioButtonControl*>(parent());
    if (radio && mGroup)
        mGroup->removeButton(radio);

    mGroup = newGroup;
    if (radio && mGroup)
        mGroup->addButton(radio);

    Q_EMIT groupChanged();
}


AsemanQuickRadioButtonGroupAttachedProperty *AsemanQuickRadioButtonGroupAttachedCreator::qmlAttachedProperties(QObject *object)
{
    return new AsemanQuickRadioButtonGroupAttachedProperty(object);
}
