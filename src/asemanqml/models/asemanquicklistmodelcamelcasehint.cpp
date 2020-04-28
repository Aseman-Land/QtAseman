#include "asemanquicklistmodelcamelcasehint.h"

#include <QtQml>

class AsemanQuickListModelCamelCaseHint::Private
{
public:
    QString path;
};

AsemanQuickListModelCamelCaseHint::AsemanQuickListModelCamelCaseHint(QObject *parent) :
    AsemanAbstractQuickListModelHint(parent)
{
    p = new Private;
}

void AsemanQuickListModelCamelCaseHint::setPath(const QString &path)
{
    if (p->path == path)
        return;

    p->path = path;
    Q_EMIT pathChanged();
    Q_EMIT changeRequest();
}

QString AsemanQuickListModelCamelCaseHint::path() const
{
    return p->path;
}

QVariantMap AsemanQuickListModelCamelCaseHint::analyze(const QVariantMap &map)
{
    if (p->path.isEmpty())
    {
        qmlWarning(this) << "ModelCamelCaseHint.path is empty";
        return map;
    }

    QVariant data = AsemanAbstractQuickListModelHint::getPathValue(map, p->path);

    QStringList pathList = p->path.split(QStringLiteral("->"));
    QStringList parts = pathList.last().split('_', QString::SkipEmptyParts);
    for (int i=1; i<parts.size(); ++i)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    pathList[pathList.count()-1] = parts.join("");

    QVariantMap m = AsemanAbstractQuickListModelHint::deletePath(map, p->path).toMap();
    return AsemanAbstractQuickListModelHint::setPathValue(m, pathList.join("->"), data).toMap();
}

AsemanQuickListModelCamelCaseHint::~AsemanQuickListModelCamelCaseHint()
{
    delete p;
}
