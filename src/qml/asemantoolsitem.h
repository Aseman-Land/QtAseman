#ifndef ASEMANTOOLSITEM_H
#define ASEMANTOOLSITEM_H

#include <QJSValue>
#include <QObject>

#include <asemantools.h>

#include "asemantools_global.h"

class AsemanToolsItemPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanToolsItem : public AsemanTools
{
    Q_OBJECT
public:
    AsemanToolsItem(QObject *parent = Q_NULLPTR);
    virtual ~AsemanToolsItem();

public Q_SLOTS:
    static QString variantToJson(QVariant value);
    static QVariant jsonToVariant(const QString &json);

    void jsDelayCall(int ms, const QJSValue &value);

    static void setInAppStoreProperty(QObject *store, const QString &propertyName, const QString &value);

protected:
    void timerEvent(QTimerEvent *e);

private:
    AsemanToolsItemPrivate *p;
};

#endif // ASEMANTOOLSITEM_H
