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

#ifndef ASEMANCOUNTRIESMODEL_H
#define ASEMANCOUNTRIESMODEL_H

#include <QObject>
#include <QStringList>
#include "asemanabstractlistmodel.h"

#include "asemancore_global.h"

class AsemanCountriesModelPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanCountriesModel : public AsemanAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(ColorfullListModelRoles)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
    Q_PROPERTY(QString systemCountry READ systemCountry NOTIFY systemCountryChanged)

public:
    enum ColorfullListModelRoles {
        NameRole = Qt::UserRole,
        NativeNameRole,
        TldRole,
        Cca2Role,
        Ccn3Role,
        Cca3Role,
        CurrencyRole,
        CallingCodeRole,
        CapitalRole,
        AltSpellingsRole,
        RelevanceRole,
        RegionRole,
        SubregionRole,
        LanguageRole,
        LanguageCodesRole,
        TranslationsRole,
        LatlngRole,
        DemonymRole,
        BordersRole,
        AreaRole,
        KeyRole
    };

    AsemanCountriesModel(QObject *parent = Q_NULLPTR);
    virtual ~AsemanCountriesModel();

#ifndef ASEMAN_OXYGEN_SKIP
    QString id( const QModelIndex &index ) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    QHash<qint32,QByteArray> roleNames() const Q_DECL_OVERRIDE;

    int count() const;
#endif

    Q_INVOKABLE int indexOf(const QString &name);

    void setFilter(const QString &filter);
#ifndef ASEMAN_OXYGEN_SKIP
    QString filter() const;

    QString systemCountry() const;
#endif

Q_SIGNALS:
    void countChanged();
    void filterChanged();
    void systemCountryChanged();

private:
    void init_buff();
    void changed(const QStringList &list);

private:
    AsemanCountriesModelPrivate *p;
};

typedef AsemanCountriesModel QAsemanCountriesModel;

#endif // ASEMANCOUNTRIESMODEL_H
