#include "asemanabstractquicklistmodelhint.h"

#include <QRegularExpression>

AsemanAbstractQuickListModelHint::AsemanAbstractQuickListModelHint(QObject *parent) :
    QObject(parent)
{

}

QVariant AsemanAbstractQuickListModelHint::getPathValue(QVariant data, const QString &path)
{
    if (path.isEmpty())
        return data;

    QStringList pathList = path.split(QStringLiteral("->"));
    for (const QString &pt: pathList)
    {
        QRegularExpression rx(QStringLiteral("(\\w+)\\s*\\[\\s*(\\d+)\\s*\\]$"));
        auto i = rx.globalMatch(pt);
        if (i.hasNext())
        {
            auto m = i.next();
            QString key = m.captured(1);
            qint32 idx = m.captured(2).toInt();

            QVariantList list = data.toMap().value(key).toList();
            if (idx < list.count())
                data = list.at(idx);
            else
            {
                data = QVariant();
                break;
            }
        }
        else
            data = data.toMap().value(pt);
    }

    return data;
}

QVariant AsemanAbstractQuickListModelHint::setPathValue(const QVariant &data, const QString &path, const QVariant &value)
{
    if (path.isEmpty())
        return value;

    QStringList pathList = path.split(QStringLiteral("->"));
    return setPathValue(data, pathList, value);
}

QVariant AsemanAbstractQuickListModelHint::setPathValue(const QVariant &data, QStringList pathList, const QVariant &value)
{
    if (pathList.isEmpty())
        return value;

    QString pt = pathList.takeFirst();

    QVariantMap map = data.toMap();

    QRegularExpression rx(QStringLiteral("(\\w+)\\s*\\[\\s*(\\d+)\\s*\\]$"));
    auto i = rx.globalMatch(pt);
    if (i.hasNext())
    {
        auto m = i.next();
        QString key = m.captured(1);
        qint32 idx = m.captured(2).toInt();

        QVariantList list = map.value(key).toList();
        if (idx < list.count())
            list[idx] = setPathValue(list.at(idx), pathList, value);
        else
            list << setPathValue(QVariant(), pathList, value);

        map[key] = list;
    }
    else
        map[pt] = setPathValue(map.value(pt), pathList, value);

    return map;
}

QVariant AsemanAbstractQuickListModelHint::deletePath(const QVariant &data, const QString &path)
{
    if (path.isEmpty())
        return QVariantMap();

    QStringList pathList = path.split(QStringLiteral("->"));
    return deletePath(data, pathList);
}

QVariant AsemanAbstractQuickListModelHint::deletePath(const QVariant &data, QStringList pathList)
{
    if (pathList.isEmpty())
        return QVariant();

    QString pt = pathList.takeFirst();

    QVariantMap map = data.toMap();

    QRegularExpression rx(QStringLiteral("(\\w+)\\s*\\[\\s*(\\d+)\\s*\\]$"));
    auto i = rx.globalMatch(pt);
    if (i.hasNext())
    {
        auto m = i.next();
        QString key = m.captured(1);
        qint32 idx = m.captured(2).toInt();

        QVariantList list = map.value(key).toList();
        if (idx < list.count())
            list[idx] = deletePath(list.at(idx), pathList);

        map[key] = list;
    }
    else
    {
        if (pathList.isEmpty())
            map.remove(pt);
        else
            map[pt] = deletePath(map.value(pt), pathList);
    }

    return map;
}

AsemanAbstractQuickListModelHint::~AsemanAbstractQuickListModelHint()
{

}
