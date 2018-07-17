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

#include "asemannetworkmanageritem.h"

class AsemanNetworkManagerItemPrivate
{
public:
    QNetworkConfiguration config;
    QList<AsemanNetworkManagerItem *> children;
};

AsemanNetworkManagerItem::AsemanNetworkManagerItem(QObject *parent) :
    QObject(parent)
{
    p = new AsemanNetworkManagerItemPrivate;
}

int AsemanNetworkManagerItem::bearerType() const
{
    return p->config.bearerType();
}

int AsemanNetworkManagerItem::bearerTypeFamily() const
{
    return p->config.bearerTypeFamily();
}

QString AsemanNetworkManagerItem::bearerTypeName() const
{
    return p->config.bearerTypeName();
}

QList<AsemanNetworkManagerItem *> AsemanNetworkManagerItem::children() const
{
    return p->children;
}

void AsemanNetworkManagerItem::setChildrens(const QList<QNetworkConfiguration> &childs)
{
    if(childrenChanged_prv(childs)) Q_EMIT childrenChanged();
}

QString AsemanNetworkManagerItem::identifier() const
{
    return p->config.identifier();
}

bool AsemanNetworkManagerItem::isRoamingAvailable() const
{
    return p->config.isRoamingAvailable();
}

bool AsemanNetworkManagerItem::isValid() const
{
    return p->config.isValid();
}

QString AsemanNetworkManagerItem::name() const
{
    return p->config.name();
}

int AsemanNetworkManagerItem::purpose() const
{
    return p->config.purpose();
}

int AsemanNetworkManagerItem::state() const
{
    return p->config.state();
}

int AsemanNetworkManagerItem::type() const
{
    return p->config.type();
}

QObject &AsemanNetworkManagerItem::operator =(const QNetworkConfiguration &n)
{
    bool bearerTypeIsChanged = (n.bearerType() != p->config.bearerType());
    bool bearerTypeFamilyIsChanged = (n.bearerTypeFamily() != p->config.bearerTypeFamily());
    bool bearerTypeNameIsChanged = (n.bearerTypeName() != p->config.bearerTypeName());
    bool childrenIsChanged = childrenChanged_prv(n.children());
    bool identifierIsChanged = (n.identifier() != p->config.identifier());
    bool isRoamingAvailableIsChanged = (n.isRoamingAvailable() != p->config.isRoamingAvailable());
    bool isValidIsChanged = (n.isValid() != p->config.isValid());
    bool nameIsChanged = (n.name() != p->config.name());
    bool purposeIsChanged = (n.purpose() != p->config.purpose());
    bool stateIsChanged = (n.state() != p->config.state());
    bool typeIsChanged = (n.type() != p->config.type());

    p->config = n;

    if(bearerTypeIsChanged)
        Q_EMIT bearerTypeChanged();
    if(bearerTypeFamilyIsChanged)
        Q_EMIT bearerTypeFamilyChanged();
    if(bearerTypeNameIsChanged)
        Q_EMIT bearerTypeNameChanged();
    if(childrenIsChanged)
        Q_EMIT childrenChanged();
    if(identifierIsChanged)
        Q_EMIT identifierChanged();
    if(isRoamingAvailableIsChanged)
        Q_EMIT isRoamingAvailableChanged();
    if(isValidIsChanged)
        Q_EMIT isValidChanged();
    if(nameIsChanged)
        Q_EMIT nameChanged();
    if(purposeIsChanged)
        Q_EMIT purposeChanged();
    if(stateIsChanged)
        Q_EMIT stateChanged();
    if(typeIsChanged)
        Q_EMIT typeChanged();
    return *this;
}

bool AsemanNetworkManagerItem::childrenChanged_prv(const QList<QNetworkConfiguration> &children)
{
    bool result = false;
    for( int i=0 ; i<p->children.count() ; i++ )
    {
        AsemanNetworkManagerItem *item = p->children.at(i);
        if( childIndex(children,item)!=-1 )
            continue;

        p->children.takeAt(i)->deleteLater();
        i--;
        result = true;
    }


    QList<QNetworkConfiguration> temp_list = children;
    for( int i=0 ; i<temp_list.count() ; i++ )
    {
        const QNetworkConfiguration &item = temp_list.at(i);
        if( childIndex(p->children,item)!=-1 )
            continue;

        temp_list.removeAt(i);
        i--;
    }
    while( !isEqual(temp_list,p->children) )
        for( int i=0 ; i<p->children.count() ; i++ )
        {
            AsemanNetworkManagerItem *item = p->children.at(i);
            int nw = childIndex(temp_list,item);
            if( i == nw )
                continue;

            p->children.move( i, nw );
            result = true;
        }


    for( int i=0 ; i<children.count() ; i++ )
    {
        const QNetworkConfiguration &item = children.at(i);
        if( childIndex(p->children,item)!=-1 )
            continue;

        AsemanNetworkManagerItem *newItem = new AsemanNetworkManagerItem(this);
        newItem->operator =(item);

        p->children.insert( i, newItem);
        result = true;
    }

    for(int i=0; i<p->children.count(); i++)
        p->children.at(i)->operator =(children.at(i));

    return result;
}

int AsemanNetworkManagerItem::childIndex(const QList<QNetworkConfiguration> &childs, AsemanNetworkManagerItem *item)
{
    for(const QNetworkConfiguration &conf: childs)
        if(conf.name() == item->name())
            return childs.indexOf(conf);
    return -1;
}

int AsemanNetworkManagerItem::childIndex(const QList<AsemanNetworkManagerItem *> &childs, const QNetworkConfiguration &item)
{
    for(AsemanNetworkManagerItem *conf: childs)
        if(conf->name() == item.name())
            return childs.indexOf(conf);
    return -1;
}

bool AsemanNetworkManagerItem::isEqual(QList<QNetworkConfiguration> &a, const QList<AsemanNetworkManagerItem *> &b)
{
    if(a.length() != b.length())
        return false;
    for(int i=0; i<a.length(); i++)
        if(a.at(i).identifier() != b.at(i)->identifier())
            return false;
    return true;
}

AsemanNetworkManagerItem::~AsemanNetworkManagerItem()
{
    delete p;
}
