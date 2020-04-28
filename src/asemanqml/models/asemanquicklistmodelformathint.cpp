#include "asemanquicklistmodelformathint.h"

#include <QtQml>

class AsemanQuickListModelFormatHint::Private
{
public:
    QString path;
    QJSValue method;
};

AsemanQuickListModelFormatHint::AsemanQuickListModelFormatHint(QObject *parent) :
    AsemanAbstractQuickListModelHint(parent)
{
    p = new Private;
}

void AsemanQuickListModelFormatHint::setPath(const QString &path)
{
    if (p->path == path)
        return;

    p->path = path;
    Q_EMIT pathChanged();
    Q_EMIT changeRequest();
}

QString AsemanQuickListModelFormatHint::path() const
{
    return p->path;
}

void AsemanQuickListModelFormatHint::setMethod(const QJSValue &method)
{
    p->method = method;
    Q_EMIT methodChanged();
    Q_EMIT changeRequest();
}

QJSValue AsemanQuickListModelFormatHint::method() const
{
    return p->method;
}

QVariantMap AsemanQuickListModelFormatHint::analyze(const QVariantMap &map)
{
    if (p->path.isEmpty())
    {
        qmlWarning(this) << "ModelFormatHint.path is empty";
        return map;
    }
    if (!p->method.isCallable())
    {
        qmlWarning(this) << "ModelFormatHint.method is empty";
        return map;
    }

    QQmlEngine *engine = qmlEngine(this);
    if (!engine)
        return map;

    QVariant data = AsemanAbstractQuickListModelHint::getPathValue(map, p->path);

    QJSValueList args = { engine->toScriptValue(data) };
    QJSValue result = p->method.call(args);

    return AsemanAbstractQuickListModelHint::setPathValue(map, p->path, result.toVariant()).toMap();
}

AsemanQuickListModelFormatHint::~AsemanQuickListModelFormatHint()
{
    delete p;
}
