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

#ifndef ASEMANLISTMODEL_H
#define ASEMANLISTMODEL_H

#include <QObject>
#include <asemanabstractlistmodel.h>

#include "asemancore_global.h"

class LIBQTASEMAN_CORE_EXPORT AsemanListModel : public AsemanAbstractListModel
{
    Q_OBJECT
    class Private;
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString cachePath READ cachePath WRITE setCachePath NOTIFY cachePathChanged)
    Q_PROPERTY(QVariantList data READ data WRITE setData NOTIFY dataListChanged)

public:
    AsemanListModel(QObject *parent = Q_NULLPTR);
    virtual ~AsemanListModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QHash<qint32,QByteArray> roleNames() const;
    int count() const;

    void setCachePath(const QString &path);
    QString cachePath() const;

    QVariantList data() const;
    void setData(const QVariantList &data);

Q_SIGNALS:
    void countChanged();
    void cachePathChanged();
    void listChanged();
    void dataListChanged();

public Q_SLOTS:
    void insert(int row, const QVariantMap &map);
    void append(const QVariantMap &map);
    void remove(int row);
    void move(int from, int to);
    void clear();
    void change(const QVariantList &list);

private:
    void changed(const QList<QVariantMap> &list);
    void loadCache();
    void saveCache();

private:
    Private *p;
};

#endif // ASEMANLISTMODEL_H
