#include "asemanquicklistmodelcopyhint.h"

#include <QtQml>

class AsemanQuickListModelCopyHint::Private
{
public:
    QString path;
    QString targetPath;
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
    Q_EMIT changeRequest();
}

QString AsemanQuickListModelCopyHint::targetPath() const
{
    return p->targetPath;
}

QVariantMap AsemanQuickListModelCopyHint::analyze(const QVariantMap &map)
{
    if (p->path.isEmpty())
    {
        qmlWarning(this) << "ModelCopyHint.path is empty";
        return map;
    }
    if (p->targetPath.isEmpty())
    {
        qmlWarning(this) << "ModelCopyHint.targetPath is empty";
        return map;
    }

    QVariant data = AsemanAbstractQuickListModelHint::getPathValue(map, p->path);

    return AsemanAbstractQuickListModelHint::setPathValue(map, p->targetPath, data).toMap();
}

AsemanQuickListModelCopyHint::~AsemanQuickListModelCopyHint()
{
    delete p;
}
