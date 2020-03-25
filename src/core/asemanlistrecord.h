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

#ifndef ASEMANLISTRECORD_H
#define ASEMANLISTRECORD_H

#include <QByteArray>
#include <QList>
#include <cstdio>

#include "asemancore_global.h"

class LIBQTASEMAN_CORE_EXPORT AsemanListRecord
{
public:
    AsemanListRecord();
    AsemanListRecord( const QByteArray & record );

    void operator<<( AsemanListRecord record );
    void operator<<( const QByteArray & str );
    void operator<<( const QList<QByteArray> & list );

    QByteArray operator[]( int index );
    QByteArray at( int index );
    QByteArray last();
    QByteArray first();
    QByteArray takeLast();
    QByteArray takeFirst();
    QList<QByteArray> mid( int i , int len );
    QList<QByteArray> toQByteArrayList();

    void removeAt( int index );
    QByteArray takeAt( int index );

    void FromQByteArray( const QByteArray & str );
    QByteArray toQByteArray();

    int count();
    int size();
    int lenght();

    void clear();

private:
    QList<QByteArray> list;
    QList<int> offsets;

    QByteArray strToRecord( const QByteArray & str );
};

typedef AsemanListRecord QAsemanListRecord;

#endif // ASEMANLISTRECORD_H
