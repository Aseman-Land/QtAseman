/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemanmixedlistmodel.h"

#include <QTimer>
#include <QDebug>

class AsemanMixedListModelPrivate
{
public:
    QList<QAbstractListModel*> models;
    QVariantList cachedList;
    QTimer *initTimer;
    bool inited;
};

AsemanMixedListModel::AsemanMixedListModel(QObject *parent) :
    AsemanAbstractListModel(parent)
{
    p = new AsemanMixedListModelPrivate;
    p->inited = false;

    p->initTimer = new QTimer(this);
    p->initTimer->setInterval(200);
    p->initTimer->setSingleShot(true);

    connect(p->initTimer, &QTimer::timeout, this, &AsemanMixedListModel::reinit_prv);
}

int AsemanMixedListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return count();
}

QVariant AsemanMixedListModel::data(const QModelIndex &index, int role) const
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, index);
        if(!newIndex.isValid())
            continue;

        if(role == RolesModelObject)
            return QVariant::fromValue<QObject*>(model);
        else
        if(role == RolesModelIndex)
            return p->models.indexOf(model);
        else
        if(role == RolesModelName)
            return model? model->objectName() : QStringLiteral("");
        else
        if(role < Qt::UserRole)
            return model->data(newIndex, role);
        else
        if(model->roleNames().contains(role))
            return model->data(newIndex, role);
    }

    return QVariant();
}

bool AsemanMixedListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, index);
        if(!newIndex.isValid())
            continue;

        return model->setData(newIndex, value, role);
    }

    return false;
}

QHash<qint32, QByteArray> AsemanMixedListModel::roleNames() const
{
    QHash<qint32, QByteArray> roles;
    roles[RolesModelObject] = "modelObject";
    roles[RolesModelIndex] = "modelIndex";
    roles[RolesModelName] = "modelName";

    for(QAbstractListModel *model: p->models)
    {
        const auto &roleNames = model->roleNames();
        auto it = roleNames.begin();
        const auto end = roleNames.end();
        while (it != end)
        {
            roles[it.key()] = it.value();
            it++;
        }
    }

    return roles;
}

int AsemanMixedListModel::count() const
{
    int count = 0;
    for(QAbstractListModel *model: p->models)
        count += model->rowCount();
    return count;
}

void AsemanMixedListModel::setModels(const QVariantList &list)
{
    if(list == p->cachedList)
        return;

    p->cachedList = list;
    reinit();

    Q_EMIT modelsChanged();
    Q_EMIT countChanged();
}

QVariantList AsemanMixedListModel::models() const
{
    return p->cachedList;
}

Qt::ItemFlags AsemanMixedListModel::flags(const QModelIndex &index) const
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, index);
        if(!newIndex.isValid())
            continue;

        return model->flags(newIndex);
    }

    return Qt::NoItemFlags;
}

bool AsemanMixedListModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, parent);
        if(!newIndex.isValid())
            continue;

        return model->insertColumns(column, count, newIndex);
    }

    return false;
}

bool AsemanMixedListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, parent);
        if(!newIndex.isValid())
            continue;

        return model->insertRows(row, count, newIndex);
    }

    return false;
}

bool AsemanMixedListModel::moveColumns(const QModelIndex &sourceParent, int sourceColumn, int count, const QModelIndex &destinationParent, int destinationChild)
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, sourceParent);
        if(!newIndex.isValid())
            continue;

        return model->moveColumns(sourceParent, sourceColumn, count, destinationParent, destinationChild);
    }

    return false;
}

bool AsemanMixedListModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, sourceParent);
        if(!newIndex.isValid())
            continue;

        return model->moveRows(sourceParent, sourceRow, count, destinationParent, destinationChild);
    }

    return false;
}

bool AsemanMixedListModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, parent);
        if(!newIndex.isValid())
            continue;

        return model->removeColumns(column, count, newIndex);
    }

    return false;
}

bool AsemanMixedListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    for(QAbstractListModel *model: p->models)
    {
        QModelIndex newIndex = mapToModelIndex(model, parent);
        if(!newIndex.isValid())
            continue;

        return model->removeRows(row, count, newIndex);
    }

    return false;
}

void AsemanMixedListModel::columnsAboutToBeInserted_slt(const QModelIndex &parent, int first, int last)
{
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        beginInsertColumns( mapFromModelIndex(model, parent),
                            mapFromModel(model, first),
                            mapFromModel(model, last));
}

void AsemanMixedListModel::columnsAboutToBeMoved_slt(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destinationParent, int destinationColumn)
{
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        beginMoveColumns( mapFromModelIndex(model, sourceParent),
                          mapFromModel(model, sourceStart),
                          mapFromModel(model, sourceEnd),
                          mapFromModelIndex(model, destinationParent),
                          mapFromModel(model, destinationColumn));
}

void AsemanMixedListModel::columnsAboutToBeRemoved_slt(const QModelIndex &parent, int first, int last)
{
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        beginRemoveColumns( mapFromModelIndex(model, parent),
                            mapFromModel(model, first),
                            mapFromModel(model, last));
}

void AsemanMixedListModel::columnsInserted_slt(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    Q_UNUSED(first)
    Q_UNUSED(last)
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        endInsertColumns();
}

void AsemanMixedListModel::columnsMoved_slt(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int column)
{
    Q_UNUSED(parent)
    Q_UNUSED(start)
    Q_UNUSED(end)
    Q_UNUSED(destination)
    Q_UNUSED(column)
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        endMoveColumns();
}

void AsemanMixedListModel::columnsRemoved_slt(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    Q_UNUSED(first)
    Q_UNUSED(last)
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        endRemoveColumns();
}

void AsemanMixedListModel::dataChanged_slt(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        Q_EMIT dataChanged( mapFromModelIndex(model, topLeft),
                          mapFromModelIndex(model, bottomRight),
                          roles);
}

void AsemanMixedListModel::headerDataChanged_slt(Qt::Orientation orientation, int first, int last)
{
    Q_UNUSED(orientation)
    Q_UNUSED(first)
    Q_UNUSED(last)
}

void AsemanMixedListModel::layoutAboutToBeChanged_slt(const QList<QPersistentModelIndex> &parents, QAbstractItemModel::LayoutChangeHint hint)
{
    Q_UNUSED(parents)
    Q_UNUSED(hint)
}

void AsemanMixedListModel::layoutChanged_slt(const QList<QPersistentModelIndex> &parents, QAbstractItemModel::LayoutChangeHint hint)
{
    Q_UNUSED(parents)
    Q_UNUSED(hint)
}

void AsemanMixedListModel::modelAboutToBeReset_slt()
{
    beginResetModel();
}

void AsemanMixedListModel::modelReset_slt()
{
    endResetModel();
    Q_EMIT countChanged();
}

void AsemanMixedListModel::rowsAboutToBeInserted_slt(const QModelIndex &parent, int start, int end)
{
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        beginInsertRows( mapFromModelIndex(model, parent),
                         mapFromModel(model, start),
                         mapFromModel(model, end));
}

void AsemanMixedListModel::rowsAboutToBeMoved_slt(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destinationParent, int destinationRow)
{
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        beginMoveRows( mapFromModelIndex(model, sourceParent),
                       mapFromModel(model, sourceStart),
                       mapFromModel(model, sourceEnd),
                       mapFromModelIndex(model, destinationParent),
                       mapFromModel(model, destinationRow));
}

void AsemanMixedListModel::rowsAboutToBeRemoved_slt(const QModelIndex &parent, int first, int last)
{
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        beginRemoveRows( mapFromModelIndex(model, parent),
                         mapFromModel(model, first),
                         mapFromModel(model, last));
}

void AsemanMixedListModel::rowsInserted_slt(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    Q_UNUSED(first)
    Q_UNUSED(last)
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        endInsertRows();

    Q_EMIT countChanged();
}

void AsemanMixedListModel::rowsMoved_slt(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row)
{
    Q_UNUSED(parent)
    Q_UNUSED(start)
    Q_UNUSED(end)
    Q_UNUSED(destination)
    Q_UNUSED(row)
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        endMoveRows();

    Q_EMIT countChanged();
}

void AsemanMixedListModel::rowsRemoved_slt(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    Q_UNUSED(first)
    Q_UNUSED(last)
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(sender());
    if(model)
        endRemoveRows();

    Q_EMIT countChanged();
}

void AsemanMixedListModel::modelDestroyed(QObject *obj)
{
    QAbstractListModel *model = qobject_cast<QAbstractListModel*>(obj);
    if(!model)
        return;

    p->models.removeAll(model);
    p->cachedList.removeAll(QVariant::fromValue<QObject*>(obj));
    Q_EMIT modelsChanged();
}

void AsemanMixedListModel::reinit()
{
    p->inited = false;
    p->initTimer->stop();
    p->initTimer->start();
}

void AsemanMixedListModel::reinit_prv()
{
    for(QAbstractListModel *model: p->models)
    {
        disconnect(model, &QAbstractListModel::destroyed, this, &AsemanMixedListModel::modelDestroyed);
        disconnect(model, &QAbstractListModel::dataChanged, this, &AsemanMixedListModel::dataChanged_slt);
        disconnect(model, &QAbstractListModel::columnsAboutToBeInserted, this, &AsemanMixedListModel::columnsAboutToBeInserted_slt);
        disconnect(model, &QAbstractListModel::columnsAboutToBeMoved, this, &AsemanMixedListModel::columnsAboutToBeMoved_slt);
        disconnect(model, &QAbstractListModel::columnsAboutToBeRemoved, this, &AsemanMixedListModel::columnsAboutToBeRemoved_slt);
        disconnect(model, &QAbstractListModel::columnsInserted, this, &AsemanMixedListModel::columnsInserted_slt);
        disconnect(model, &QAbstractListModel::columnsMoved, this, &AsemanMixedListModel::columnsMoved_slt);
        disconnect(model, &QAbstractListModel::columnsRemoved, this, &AsemanMixedListModel::columnsRemoved_slt);
        disconnect(model, &QAbstractListModel::dataChanged, this, &AsemanMixedListModel::dataChanged_slt);
        disconnect(model, &QAbstractListModel::headerDataChanged, this, &AsemanMixedListModel::headerDataChanged_slt);
        disconnect(model, &QAbstractListModel::layoutAboutToBeChanged, this, &AsemanMixedListModel::layoutAboutToBeChanged_slt);
        disconnect(model, &QAbstractListModel::layoutChanged, this, &AsemanMixedListModel::layoutChanged_slt);
        disconnect(model, &QAbstractListModel::modelAboutToBeReset, this, &AsemanMixedListModel::modelAboutToBeReset_slt);
        disconnect(model, &QAbstractListModel::modelReset, this, &AsemanMixedListModel::modelReset_slt);
        disconnect(model, &QAbstractListModel::rowsAboutToBeInserted, this, &AsemanMixedListModel::rowsAboutToBeInserted_slt);
        disconnect(model, &QAbstractListModel::rowsAboutToBeMoved, this, &AsemanMixedListModel::rowsAboutToBeMoved_slt);
        disconnect(model, &QAbstractListModel::rowsAboutToBeRemoved, this, &AsemanMixedListModel::rowsAboutToBeRemoved_slt);
        disconnect(model, &QAbstractListModel::rowsInserted, this, &AsemanMixedListModel::rowsInserted_slt);
        disconnect(model, &QAbstractListModel::rowsMoved, this, &AsemanMixedListModel::rowsMoved_slt);
        disconnect(model, &QAbstractListModel::rowsRemoved, this, &AsemanMixedListModel::rowsRemoved_slt);
    }

    beginResetModel();
    p->models.clear();
    for(const QVariant &var: p->cachedList)
    {
        QAbstractListModel *model = qobject_cast<QAbstractListModel*>(var.value<QObject*>());
        if(!model)
            continue;

        p->models << model;
        connect(model, &QAbstractListModel::destroyed, this, &AsemanMixedListModel::modelDestroyed);
        connect(model, &QAbstractListModel::dataChanged, this, &AsemanMixedListModel::dataChanged_slt);
        connect(model, &QAbstractListModel::columnsAboutToBeInserted, this, &AsemanMixedListModel::columnsAboutToBeInserted_slt);
        connect(model, &QAbstractListModel::columnsAboutToBeMoved, this, &AsemanMixedListModel::columnsAboutToBeMoved_slt);
        connect(model, &QAbstractListModel::columnsAboutToBeRemoved, this, &AsemanMixedListModel::columnsAboutToBeRemoved_slt);
        connect(model, &QAbstractListModel::columnsInserted, this, &AsemanMixedListModel::columnsInserted_slt);
        connect(model, &QAbstractListModel::columnsMoved, this, &AsemanMixedListModel::columnsMoved_slt);
        connect(model, &QAbstractListModel::columnsRemoved, this, &AsemanMixedListModel::columnsRemoved_slt);
        connect(model, &QAbstractListModel::dataChanged, this, &AsemanMixedListModel::dataChanged_slt);
        connect(model, &QAbstractListModel::headerDataChanged, this, &AsemanMixedListModel::headerDataChanged_slt);
        connect(model, &QAbstractListModel::layoutAboutToBeChanged, this, &AsemanMixedListModel::layoutAboutToBeChanged_slt);
        connect(model, &QAbstractListModel::layoutChanged, this, &AsemanMixedListModel::layoutChanged_slt);
        connect(model, &QAbstractListModel::modelAboutToBeReset, this, &AsemanMixedListModel::modelAboutToBeReset_slt);
        connect(model, &QAbstractListModel::modelReset, this, &AsemanMixedListModel::modelReset_slt);
        connect(model, &QAbstractListModel::rowsAboutToBeInserted, this, &AsemanMixedListModel::rowsAboutToBeInserted_slt);
        connect(model, &QAbstractListModel::rowsAboutToBeMoved, this, &AsemanMixedListModel::rowsAboutToBeMoved_slt);
        connect(model, &QAbstractListModel::rowsAboutToBeRemoved, this, &AsemanMixedListModel::rowsAboutToBeRemoved_slt);
        connect(model, &QAbstractListModel::rowsInserted, this, &AsemanMixedListModel::rowsInserted_slt);
        connect(model, &QAbstractListModel::rowsMoved, this, &AsemanMixedListModel::rowsMoved_slt);
        connect(model, &QAbstractListModel::rowsRemoved, this, &AsemanMixedListModel::rowsRemoved_slt);
    }
    endResetModel();
    p->inited = true;
}

QModelIndex AsemanMixedListModel::mapFromModelIndex(QAbstractListModel *model, const QModelIndex &index) const
{
    if(index.parent().isValid())
        return index;

    const int mappedRow = mapFromModel(model, index.row());
    return model->index( mappedRow, index.column(), index.parent());
}

int AsemanMixedListModel::mapFromModel(QAbstractListModel *model, int row) const
{
    return row+modelPad(model);
}

QModelIndex AsemanMixedListModel::mapToModelIndex(QAbstractListModel *model, const QModelIndex &index) const
{
    if(index.parent().isValid())
        return index;

    const int mappedRow = mapToModel(model, index.row());
    if(mappedRow < 0)
        return QModelIndex();
    else
        return model->index(mappedRow, index.column(), index.parent());
}

int AsemanMixedListModel::mapToModel(QAbstractListModel *model, int row) const
{
    int newRow = row-modelPad(model);
    if(0 <= newRow && newRow < model->rowCount())
        return newRow;
    else
        return -1;
}

int AsemanMixedListModel::modelPad(QAbstractListModel *model) const
{
    int rowPad = 0;
    for(QAbstractListModel *mdl: p->models)
    {
        if(mdl == model)
            break;

        rowPad += mdl->rowCount();
    }

    return rowPad;
}

AsemanMixedListModel::~AsemanMixedListModel()
{
    delete p;
}
