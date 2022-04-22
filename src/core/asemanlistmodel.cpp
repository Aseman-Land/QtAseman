#include "asemanlistmodel.h"

#include <QDataStream>
#include <QFile>
#include <QSet>
#include <QDebug>

class AsemanListModel::Private
{
public:
    QList< QVariantMap > list;
    QHash<qint32, QByteArray> roleNames;
    QString cachePath;
};

AsemanListModel::AsemanListModel(QObject *parent) :
    AsemanAbstractListModel(parent)
{
    p = new Private;
}

int AsemanListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return count();
}

QVariant AsemanListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= count())
        return QVariant();

    QString keyName = p->roleNames.value(role);
    QVariantMap map = p->list.value(index.row());
    return map.value(keyName);
}

bool AsemanListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() >= count())
        return false;

    QString keyName = p->roleNames.value(role);
    QVariantMap &map = p->list[index.row()];
    if(keyName.isEmpty())
        return false;

    map[keyName] = value;
    saveCache();
    return true;
}

QHash<qint32, QByteArray> AsemanListModel::roleNames() const
{
    QSet<QByteArray> inserteds;
    for (const auto &v: p->roleNames.values())
        inserteds.insert(v);

    for(const QVariantMap &map: p->list)
    {
        QStringList keys = map.keys();
        for(const QString &k: keys)
            if(!inserteds.contains(k.toUtf8()))
            {
                p->roleNames[ Qt::UserRole + p->roleNames.count() ] = k.toUtf8();
                inserteds.insert(k.toUtf8());
            }
    }

    return p->roleNames;
}

int AsemanListModel::count() const
{
    return p->list.count();
}

void AsemanListModel::setCachePath(const QString &path)
{
    if(p->cachePath == path)
        return;

    p->cachePath = path;
    loadCache();
    Q_EMIT cachePathChanged();
}

QString AsemanListModel::cachePath() const
{
    return p->cachePath;
}

QVariantList AsemanListModel::data() const
{
    QVariantList res;
    for (const QVariantMap &m: p->list)
        res << m;
    return res;
}

void AsemanListModel::setData(const QVariantList &data)
{
    if (data == AsemanListModel::data())
        return;

    QList<QVariantMap> list;
    for (const QVariant &d: data)
    {
        auto m = d.toMap();
        m[QStringLiteral("94d4191b6b08")] = list.count();

        list << m;
    }

    changed(list);
    Q_EMIT dataListChanged();
}

void AsemanListModel::insert(int row, const QVariantMap &map)
{
    if(p->list.count() < row || row < 0)
        return;

    beginInsertRows(QModelIndex(), row, row);
    p->list.insert(row, map);
    saveCache();
    endInsertRows();
    Q_EMIT countChanged();
    Q_EMIT listChanged();
}

void AsemanListModel::append(const QVariantMap &map)
{
    insert(count(), map);
}

void AsemanListModel::remove(int row)
{
    if(p->list.count() <= row || row < 0)
        return;

    beginRemoveRows(QModelIndex(), row, row);
    p->list.removeAt(row);
    saveCache();
    endRemoveRows();
    Q_EMIT countChanged();
    Q_EMIT listChanged();
}

void AsemanListModel::move(int from, int to)
{
    if(p->list.count() <= from || from < 0)
        return;
    if(p->list.count() < to || to < 0)
        return;

    QList<QVariantMap> newMap = p->list;
    newMap.move(from, to);

    changed(newMap);
    saveCache();
}

void AsemanListModel::clear()
{
    beginResetModel();
    p->list.clear();
    saveCache();
    endResetModel();
    Q_EMIT countChanged();
    Q_EMIT listChanged();
}

void AsemanListModel::change(const QVariantList &list)
{
    QList<QVariantMap> lst;
    for (const QVariant &v: list)
        lst << v.toMap();

    changed(lst);
    saveCache();
}

void AsemanListModel::changed(const QList<QVariantMap> &list)
{
    bool count_changed = (list.count()!=p->list.count());

    for( int i=0 ; i<p->list.count() ; i++ )
    {
        const QVariantMap &file = p->list.at(i);
        if( list.contains(file) )
            continue;

        beginRemoveRows(QModelIndex(), i, i);
        p->list.removeAt(i);
        i--;
        endRemoveRows();
    }

    QList<QVariantMap> temp_list = list;
    for( int i=0 ; i<temp_list.count() ; i++ )
    {
        const QVariantMap &file = temp_list.at(i);
        if( p->list.contains(file) )
            continue;

        temp_list.removeAt(i);
        i--;
    }
    while( p->list != temp_list )
        for( int i=0 ; i<p->list.count() ; i++ )
        {
            const QVariantMap &file = p->list.at(i);
            int nw = temp_list.indexOf(file);
            if( i == nw )
                continue;

            beginMoveRows( QModelIndex(), i, i, QModelIndex(), nw>i?nw+1:nw );
            p->list.move( i, nw );
            endMoveRows();
        }

    for( int i=0 ; i<list.count() ; i++ )
    {
        const QVariantMap &file = list.at(i);
        if( p->list.contains(file) )
            continue;

        beginInsertRows(QModelIndex(), i, i );
        p->list.insert( i, file );
        endInsertRows();
    }

    if(count_changed)
        Q_EMIT countChanged();

    Q_EMIT listChanged();
}

void AsemanListModel::loadCache()
{
    if(p->cachePath.isEmpty())
        return;

    QFile file(p->cachePath);
    if(!file.open(QFile::ReadOnly))
        return;

    QVariantList list;

    QDataStream stream(&file);
    stream >> list;

    file.close();

    QList<QVariantMap> newList;
    for(const QVariant &v: list)
        newList << v.toMap();

    changed(newList);
}

void AsemanListModel::saveCache()
{
    if(p->cachePath.isEmpty())
        return;

    QFile file(p->cachePath);
    if(!file.open(QFile::WriteOnly))
        return;

    QVariantList list;
    for(const QVariantMap &m: p->list)
        list << QVariant::fromValue<QVariantMap>(m);

    QDataStream stream(&file);
    stream << list;

    file.flush();
    file.close();
}

AsemanListModel::~AsemanListModel()
{
    delete p;
}
