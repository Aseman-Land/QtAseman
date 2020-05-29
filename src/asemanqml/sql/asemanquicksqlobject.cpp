#include "asemanquicksqlobject.h"

#include <QtQml>

AsemanQuickSqlObject::AsemanQuickSqlObject(QObject *parent) : AsemanSqlObject(parent)
{

}

void AsemanQuickSqlObject::queryAsync(const QString &query, const QVariantMap &binds, const QJSValue &callback)
{
    AsemanSqlObject::queryAsync(query, binds, [this, callback](const QVariantList &result){
        QQmlEngine *engine = qmlEngine(this);
        if (!engine)
            return;

        QJSValue method = callback;

        QJSValueList args = { engine->toScriptValue(result) };
        method.call(args);
    });
}

AsemanQuickSqlObject::~AsemanQuickSqlObject()
{

}
