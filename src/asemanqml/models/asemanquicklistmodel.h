/*
    Copyright (C) 2019 Aseman Team
    http://aseman.io

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANQUICKLISTMODEL_H
#define ASEMANQUICKLISTMODEL_H

#include <asemanlistmodel.h>
#include <QQmlListProperty>

class AsemanQuickListModel : public AsemanListModel
{
    Q_OBJECT
    class Private;

    Q_PROPERTY(QString sortField READ sortField WRITE setSortField NOTIFY sortFieldChanged)
    Q_PROPERTY(bool sortDescending READ sortDescending WRITE setSortDescending NOTIFY sortDescendingChanged)
    Q_PROPERTY(QQmlListProperty<QObject> items READ items NOTIFY itemsChanged)
    Q_CLASSINFO("DefaultProperty", "items")

public:
    AsemanQuickListModel(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickListModel();

    QQmlListProperty<QObject> items();
    QList<QObject*> itemsList() const;

    void setSortField(const QString &sortField);
    QString sortField() const;

    void setSortDescending(bool sortDescending);
    bool sortDescending() const;

Q_SIGNALS:
    void itemsChanged();
    void sortFieldChanged();
    void sortDescendingChanged();

public Q_SLOTS:
    void reload();

private:
    static void append(QQmlListProperty<QObject> *p, QObject *v);
    static int count(QQmlListProperty<QObject> *p);
    static QObject *at(QQmlListProperty<QObject> *p, int idx);
    static void clear(QQmlListProperty<QObject> *p);

    void reloadItems();
    void refreshData();

protected:
    virtual void changed(const QList<QVariantMap> &list);

private:
    Private *p;
};

typedef AsemanQuickListModel QAsemanQuickListModel;

#endif // ASEMANQUICKLISTMODEL_H
