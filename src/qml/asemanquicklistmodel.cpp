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

#include "asemanquicklistmodel.h"

class AsemanQuickListModel::Private
{
public:
    QList<QObject*> items;
};

AsemanQuickListModel::AsemanQuickListModel(QObject *parent) :
    AsemanListModel(parent)
{
    p = new Private;
}

QQmlListProperty<QObject> AsemanQuickListModel::items()
{
    return QQmlListProperty<QObject>(this, &p->items, QQmlListProperty<QObject>::AppendFunction(append),
                                                      QQmlListProperty<QObject>::CountFunction(count),
                                                      QQmlListProperty<QObject>::AtFunction(at),
                                                      QQmlListProperty<QObject>::ClearFunction(clear) );
}

QList<QObject *> AsemanQuickListModel::itemsList() const
{
    return p->items;
}

void AsemanQuickListModel::append(QQmlListProperty<QObject> *p, QObject *v)
{
    AsemanQuickListModel *aobj = static_cast<AsemanQuickListModel*>(p->object);
    aobj->p->items.append(v);
    Q_EMIT aobj->itemsChanged();
}

int AsemanQuickListModel::count(QQmlListProperty<QObject> *p)
{
    AsemanQuickListModel *aobj = static_cast<AsemanQuickListModel*>(p->object);
    return aobj->p->items.count();
}

QObject *AsemanQuickListModel::at(QQmlListProperty<QObject> *p, int idx)
{
    AsemanQuickListModel *aobj = static_cast<AsemanQuickListModel*>(p->object);
    return aobj->p->items.at(idx);
}

void AsemanQuickListModel::clear(QQmlListProperty<QObject> *p)
{
    AsemanQuickListModel *aobj = static_cast<AsemanQuickListModel*>(p->object);
    aobj->p->items.clear();
    Q_EMIT aobj->itemsChanged();
}

AsemanQuickListModel::~AsemanQuickListModel()
{
    delete p;
}
