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

#ifndef ASEMANABSTRACTLISTMODEL_H
#define ASEMANABSTRACTLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>

#include "asemancore_global.h"

class LIBQTASEMAN_CORE_EXPORT AsemanAbstractListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    AsemanAbstractListModel(QObject *parent = 0);
    virtual ~AsemanAbstractListModel();

    Q_INVOKABLE QStringList roles() const;

public Q_SLOTS:
    QVariant get(int index, int role) const;
    QVariant get(int index, const QString &roleName) const;
    QVariantMap get(int index) const;
};

#endif // ASEMANABSTRACTLISTMODEL_H
