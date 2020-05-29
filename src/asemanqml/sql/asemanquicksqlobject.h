#ifndef ASEMANQUICKSQLOBJECT_H
#define ASEMANQUICKSQLOBJECT_H

#include <asemansqlobject.h>

#include <QJSValue>

class AsemanQuickSqlObject : public AsemanSqlObject
{
    Q_OBJECT
public:
    AsemanQuickSqlObject(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickSqlObject();

public Q_SLOTS:
    void queryAsync(const QString &query, const QVariantMap &binds, const QJSValue &callback);
};

#endif // ASEMANQUICKSQLOBJECT_H
