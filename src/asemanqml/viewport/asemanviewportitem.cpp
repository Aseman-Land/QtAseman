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

#include "asemanviewportitem.h"

class AsemanViewportItem::Private
{
public:
    QString name;
    QVariant component;
};

AsemanViewportItem::AsemanViewportItem(QObject *parent) :
    QObject(parent)
{
    p = new Private;
}

AsemanViewportItem::AsemanViewportItem(const QString &name, const QVariant &component, QObject *parent) :
    AsemanViewportItem(parent)
{
    p->name = name;
    p->component = component;
}

QString AsemanViewportItem::name() const
{
    return p->name;
}

void AsemanViewportItem::setName(const QString &name)
{
    if (p->name == name)
        return;

    p->name = name;
    Q_EMIT nameChanged();
}

QVariant AsemanViewportItem::component() const
{
    return p->component;
}

void AsemanViewportItem::setComponent(const QVariant &component)
{
    if (p->component == component)
        return;

    p->component = component;
    Q_EMIT componentChanged();
}

AsemanViewportItem::~AsemanViewportItem()
{
    delete p;
}
