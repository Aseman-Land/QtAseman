#ifndef ASEMANQUICKRADIOBUTTONCONTROL_H
#define ASEMANQUICKRADIOBUTTONCONTROL_H

#include "asemanquickcontrolitem.h"

class AsemanQuickRadioButtonControl : public AsemanQuickControlItem
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)

public:
    AsemanQuickRadioButtonControl(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickRadioButtonControl();

    bool checked() const;
    void setChecked(bool newChecked);

Q_SIGNALS:
    void checkedChanged();

public Q_SLOTS:

protected:
    void uncheckOthers();

private:
    bool mChecked = false;
};

#endif // ASEMANQUICKRADIOBUTTONCONTROL_H
