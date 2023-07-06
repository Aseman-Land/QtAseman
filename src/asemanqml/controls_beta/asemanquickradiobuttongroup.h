#ifndef ASEMANQUICKRADIOBUTTONGROUP_H
#define ASEMANQUICKRADIOBUTTONGROUP_H

#include <QObject>

#include "asemanquickradiobuttoncontrol.h"

class AsemanQuickRadioButtonGroup : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<AsemanQuickRadioButtonControl> items READ items NOTIFY itemsChanged)
    Q_CLASSINFO("DefaultProperty", "items")
public:
    AsemanQuickRadioButtonGroup(QObject *parent = nullptr);
    virtual ~AsemanQuickRadioButtonGroup();

    QQmlListProperty<AsemanQuickRadioButtonControl> items();

    QList<AsemanQuickRadioButtonControl*> buttons() const;

public Q_SLOTS:
    void addButton(AsemanQuickRadioButtonControl *radio);
    void removeButton(AsemanQuickRadioButtonControl *radio);

Q_SIGNALS:
    void itemsChanged();

private:
    static void append(QQmlListProperty<AsemanQuickRadioButtonControl> *p, AsemanQuickRadioButtonControl *v);
    static int count(QQmlListProperty<AsemanQuickRadioButtonControl> *p);
    static AsemanQuickRadioButtonControl *at(QQmlListProperty<AsemanQuickRadioButtonControl> *p, int idx);
    static void clear(QQmlListProperty<AsemanQuickRadioButtonControl> *p);

private:
    QList<AsemanQuickRadioButtonControl*> mButtons;
};


class AsemanQuickRadioButtonGroupAttachedProperty : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AsemanQuickRadioButtonGroup *group READ group WRITE setGroup NOTIFY groupChanged)

public:
    AsemanQuickRadioButtonGroupAttachedProperty(QObject *parent = nullptr);
    virtual ~AsemanQuickRadioButtonGroupAttachedProperty();

    AsemanQuickRadioButtonGroup *group() const;
    void setGroup(AsemanQuickRadioButtonGroup *newGroup);

Q_SIGNALS:
    void groupChanged();

private:
    QPointer<AsemanQuickRadioButtonGroup> mGroup;
};


class AsemanQuickRadioButtonGroupAttachedCreator : public QObject
{
    Q_OBJECT
public:
    static AsemanQuickRadioButtonGroupAttachedProperty *qmlAttachedProperties(QObject *object);
};

QML_DECLARE_TYPEINFO(AsemanQuickRadioButtonGroupAttachedCreator, QML_HAS_ATTACHED_PROPERTIES)

#endif // ASEMANQUICKRADIOBUTTONGROUP_H
