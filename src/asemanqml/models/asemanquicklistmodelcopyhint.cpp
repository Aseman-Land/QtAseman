#include "asemanquicklistmodelcopyhint.h"
#include "asemanquicklistmodelsource.h"

#include <QtQml>

class AsemanQuickListModelCopyHint::Private
{
public:
    QString path;
    QString targetPath;
    QJSValue method;
};

AsemanQuickListModelCopyHint::AsemanQuickListModelCopyHint(QObject *parent) :
    AsemanAbstractQuickListModelHint(parent)
{
    p = new Private;
}

void AsemanQuickListModelCopyHint::setPath(const QString &path)
{
    if (p->path == path)
        return;

    p->path = path;
    Q_EMIT pathChanged();
    Q_EMIT changeRequest();
}

QString AsemanQuickListModelCopyHint::path() const
{
    return p->path;
}

void AsemanQuickListModelCopyHint::setTargetPath(const QString &targetPath)
{
    if (p->targetPath == targetPath)
        return;

    p->targetPath = targetPath;
    Q_EMIT targetPathChanged();
}

QString AsemanQuickListModelCopyHint::targetPath() const
{
    return p->targetPath;
}

void AsemanQuickListModelCopyHint::setMethod(const QJSValue &method)
{
    p->method = method;
    Q_EMIT methodChanged();
    Q_EMIT changeRequest();
}

QJSValue AsemanQuickListModelCopyHint::method() const
{
    return p->method;
}

QVariantMap AsemanQuickListModelCopyHint::analyze(const QVariantMap &map)
{
    if (!p->method.isCallable() || p->path.isEmpty())
        return map;

    QQmlEngine *engine = qmlEngine(this);
    if (!engine)
        return map;

    QVariant data = AsemanAbstractQuickListModelHint::getPathValue(map, p->path);

    QJSValueList args = { engine->toScriptValue(data) };
    QJSValue result = p->method.call(args);

    result.toVariant();

    return AsemanAbstractQuickListModelHint::setPathValue(map, (p->targetPath.length()? p->targetPath : p->path), result.toVariant()).toMap();
}

AsemanQuickListModelCopyHint::~AsemanQuickListModelCopyHint()
{
    delete p;
}
