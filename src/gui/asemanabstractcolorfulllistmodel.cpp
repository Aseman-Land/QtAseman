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

#include "asemanabstractcolorfulllistmodel.h"

AsemanAbstractColorfullListModel::AsemanAbstractColorfullListModel(QObject *parent) :
    AsemanAbstractListModel(parent)
{
    qRegisterMetaType<AsemanColorfullListItem*>("AsemanColorfullListItem*");
}

QHash<qint32, QByteArray> AsemanAbstractColorfullListModel::roleNames() const
{
    static QHash<qint32, QByteArray> *res = 0;
    if( res )
        return *res;

    res = new QHash<qint32, QByteArray>();
    res->insert( TitleRole    , "title"     );
    res->insert( ColorRole    , "color"     );
    res->insert( IsHeaderRole , "isHeader"  );
    res->insert( ModelItemRole, "modelItem" );

    return *res;
}

AsemanAbstractColorfullListModel::~AsemanAbstractColorfullListModel()
{
}


class AsemanColorfullListItemPrivate
{
public:
    QString title;
    QColor color;
    bool isHeader;
};

AsemanColorfullListItem::AsemanColorfullListItem(QObject *parent) :
    QObject(parent)
{
    p = new AsemanColorfullListItemPrivate;
    p->isHeader = false;
}

void AsemanColorfullListItem::setTitle(const QString &title)
{
    if( p->title == title )
        return;

    p->title = title;
    Q_EMIT titleChanged();
}

QString AsemanColorfullListItem::title() const
{
    return p->title;
}

void AsemanColorfullListItem::setColor(const QColor &color)
{
    if( p->color == color )
        return;

    p->color = color;
    Q_EMIT colorChanged();
}

QColor AsemanColorfullListItem::color() const
{
    return p->color;
}

void AsemanColorfullListItem::setIsHeader(bool header)
{
    if( p->isHeader == header )
        return;

    p->isHeader = header;
    Q_EMIT isHeaderChanged();
}

bool AsemanColorfullListItem::isHeader() const
{
    return p->isHeader;
}

AsemanColorfullListItem::~AsemanColorfullListItem()
{
    delete p;
}
