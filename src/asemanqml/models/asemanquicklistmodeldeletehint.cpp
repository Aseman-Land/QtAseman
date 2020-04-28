#include "asemanquicklistmodeldeletehint.h"

#include <QtQml>

class AsemanQuickListModelDeleteHint::Private
{
public:
    QString path;
};

AsemanQuickListModelDeleteHint::AsemanQuickListModelDeleteHint(QObject *parent) :
    AsemanAbstractQuickListModelHint(parent)
{
    p = new Private;
}

void AsemanQuickListModelDeleteHint::setPath(const QString &path)
{
    if (p->path == path)
        return;

    p->path = path;
    Q_EMIT pathChanged();
    Q_EMIT changeRequest();
}

QString AsemanQuickListModelDeleteHint::path() const
{
    return p->path;
}

QVariantMap AsemanQuickListModelDeleteHint::analyze(const QVariantMap &map)
{
    if (p->path.isEmpty())
    {
        qmlWarning(this) << "ModelDeleteHint.path is empty";
        return map;
    }

    return AsemanAbstractQuickListModelHint::deletePath(map, p->path).toMap();
}

AsemanQuickListModelDeleteHint::~AsemanQuickListModelDeleteHint()
{
    delete p;
}
