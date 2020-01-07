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

#ifndef ASEMANNETWORKMANAGER_H
#define ASEMANNETWORKMANAGER_H

#include <QObject>
#include <QNetworkConfiguration>
#include <QVariantMap>

#include "asemannetwork_global.h"

class AsemanNetworkManagerItem;
class AsemanNetworkCheckerPrivate;
class LIBQTASEMAN_NETWORK_EXPORT AsemanNetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString defaultNetworkIdentifier READ defaultNetworkIdentifier NOTIFY defaultNetworkIdentifierChanged)
    Q_PROPERTY(QVariantMap configurations READ configurations NOTIFY configurationsChanged)
    Q_PROPERTY(AsemanNetworkManagerItem* defaultNetwork READ defaultNetwork NOTIFY defaultNetworkChanged)
    Q_PROPERTY(qint32  interval READ interval WRITE setInterval NOTIFY intervalChanged)

public:
    AsemanNetworkManager(QObject *parent = 0);
    virtual ~AsemanNetworkManager();

    QString defaultNetworkIdentifier() const;
    AsemanNetworkManagerItem *defaultNetwork() const;
    QVariantMap configurations() const;

    void setInterval(qint32 ms);
    qint32 interval() const;

Q_SIGNALS:
    void defaultNetworkIdentifierChanged();
    void defaultNetworkChanged();
    void configurationsChanged();
    void intervalChanged();

private Q_SLOTS:
    void configureChanged(const QNetworkConfiguration &config);
    void configureAdded(const QNetworkConfiguration &config);
    void configureRemoved(const QNetworkConfiguration &config);
    void updateCheck();

private:
    AsemanNetworkCheckerPrivate *p;
};

typedef AsemanNetworkManager QAsemanNetworkManager;

#endif // ASEMANNETWORKMANAGER_H
