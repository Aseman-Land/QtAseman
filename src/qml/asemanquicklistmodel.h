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

#include "asemanglobals.h"

#include "asemantools_global.h"

class LIBQTASEMAN_QML_EXPORT AsemanQuickListModel : public AsemanListModel
{
    Q_OBJECT
    class Private;

    Q_PROPERTY(QQmlListProperty<QObject> items READ items NOTIFY itemsChanged)
    Q_CLASSINFO("DefaultProperty", "items")

public:
    AsemanQuickListModel(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickListModel();

    QQmlListProperty<QObject> items();
    QList<QObject*> itemsList() const;

Q_SIGNALS:
    void itemsChanged();

private:
    static void append(QQmlListProperty<QObject> *p, QObject *v);
    static int count(QQmlListProperty<QObject> *p);
    static QObject *at(QQmlListProperty<QObject> *p, int idx);
    static void clear(QQmlListProperty<QObject> *p);

    void loadSources();
    void refreshSourceData();

private:
    Private *p;
};

typedef AsemanQuickListModel QAsemanQuickListModel;

#endif // ASEMANQUICKLISTMODEL_H
