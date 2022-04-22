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
    QVariant data = AsemanAbstractQuickListModelHint::getPathValue(map, p->path);
    QVariant camelCase = toCamelCase(data);

    return AsemanAbstractQuickListModelHint::setPathValue(map, p->path, camelCase.toMap()).toMap();
}

QVariant AsemanQuickListModelCamelCaseHint::toCamelCase(const QVariant &var)
{
    QVariant res;

    switch ( static_cast<int>(var.type()) )
    {
    case QVariant::List:
    {
        QVariantList listRes;
        const QVariantList &list = var.toList();
        for (const QVariant &l: list)
            listRes << toCamelCase(l);

        res = listRes;
    }
        break;

    case QVariant::Map:
    {
        QVariantMap map;
        QMapIterator<QString, QVariant> i(var.toMap());
        while (i.hasNext())
        {
            i.next();

            QStringList parts = i.key().split('_', Qt::SkipEmptyParts);
            for (int i=1; i<parts.size(); ++i)
                parts[i].replace(0, 1, parts[i][0].toUpper());

            map[ parts.join("") ] = toCamelCase(i.value());
        }

        res = map;
    }
        break;

    default:
        res = var;
        break;
    }

    return res;
}

AsemanQuickListModelCamelCaseHint::~AsemanQuickListModelCamelCaseHint()
{
    delete p;
}
