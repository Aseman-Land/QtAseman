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

#include "asemanlistrecord.h"
#include <iostream>

#include <QChar>

AsemanListRecord::AsemanListRecord()
{
    offsets.clear();
    offsets << 0;
}

AsemanListRecord::AsemanListRecord( const QByteArray & record )
{
    offsets.clear();
    offsets << 0;
    FromQByteArray( record );
}

void AsemanListRecord::operator<<( AsemanListRecord record )
{
    for( int i=0 ; record.count(); i++ )
        operator <<( record[i] );
}

void AsemanListRecord::operator<<( const QByteArray & str )
{
    list << strToRecord( str );
    offsets << offsets.last() + list.last().size();
}

void AsemanListRecord::operator<<( const QList<QByteArray> & list )
{
    for( int i=0 ; i<list.count() ; i++ )
        operator <<( list[i] );
}

QByteArray AsemanListRecord::operator[]( int index )
{
    QByteArray result = list.at(index);

    int cnt = result.size();
    for( int i=0 ; i<cnt ; i++ )
    {
        if( result.at(0)==',' )
        {
            result.remove(0,1);
            break;
        }
        if( !QString::fromUtf8(result).at(0).isNumber() )
        {
            break;
        }
        result.remove(0,1);
    }
    return result;
}

QByteArray AsemanListRecord::at( int i )
{
    return operator [](i);
}

QByteArray AsemanListRecord::last()
{
    return at( count()-1 );
}

QByteArray AsemanListRecord::first()
{
    return at(0);
}

QByteArray AsemanListRecord::takeLast()
{
    return takeAt( count()-1 );
}

QByteArray AsemanListRecord::takeFirst()
{
    return takeAt(0);
}

QList<QByteArray> AsemanListRecord::mid( int index , int len )
{
    QList<QByteArray> res;
    for( int i=index ; i<index+len ; i++ )
        res << operator [](i);

    return res;
}

QList<QByteArray> AsemanListRecord::toQByteArrayList()
{
    return mid( 0 , count() );
}

void AsemanListRecord::removeAt( int index )
{
    int shift_size = list.at(index).size();
    list.removeAt( index );

    for( int i=index+1 ; i<offsets.count() ; i++ )
        offsets[i] -= shift_size;
}

QByteArray AsemanListRecord::takeAt( int index )
{
    QByteArray tmp( at(index) );
    removeAt( index );
    return tmp;
}

void AsemanListRecord::FromQByteArray( const QByteArray & str )
{
    int data_size = str.size();
    bool ok;

    int ext = offsets.last();
    for( int i=0,j=0 ; i<data_size ; i++ )
    {
        if( str[i] == ',' )
        {
            QByteArray tmp = str.mid( j , i-j );
            j += tmp.toInt( &ok );
            offsets << j+ext;

            if( j > i )
                i=j;
        }
    }

    for( int i=0 ; i<offsets.count()-1 ; i++ )
        list << str.mid( offsets[i] , offsets[i+1]-offsets[i] );
}

QByteArray AsemanListRecord::toQByteArray()
{
    QByteArray result;
    for(const QByteArray &ba: list)
        result += ba;

    return result;
}

int AsemanListRecord::count()
{
    return list.count();
}

int AsemanListRecord::size()
{
    return count();
}

int AsemanListRecord::lenght()
{
    return count();
}

void AsemanListRecord::clear()
{
    list.clear();
    offsets.clear();
    offsets << 0;
}

QByteArray AsemanListRecord::strToRecord(const QByteArray &str )
{
    char str_size[13];
    QByteArray record("0," + str);
    int size;

    do
    {
        size = record.count();
        sprintf( str_size , "%d" , size  );
        record = "," + str;
        record.prepend( str_size );
    }while( size != record.count() );

    return record;
}
