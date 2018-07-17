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

#include "asemannetworkmanager.h"
#include "asemannetworkmanageritem.h"

#include <QNetworkConfigurationManager>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QMap>
#include <QPointer>

class AsemanNetworkCheckerPrivate
{
public:
    QPointer<AsemanNetworkManagerItem> defaultItem;
    QVariantMap map;
    QNetworkConfigurationManager *network;
    QNetworkConfiguration lastConfig;

    QTimer *updateTimer;
};

AsemanNetworkManager::AsemanNetworkManager(QObject *parent) :
    QObject(parent)
{
    p = new AsemanNetworkCheckerPrivate;
    p->network = new QNetworkConfigurationManager(this);
    p->defaultItem = new AsemanNetworkManagerItem(this);

    p->updateTimer = new QTimer(this);
    p->updateTimer->setInterval(1000);
    p->updateTimer->start();

    p->lastConfig = p->network->defaultConfiguration();

    connect(p->network, &QNetworkConfigurationManager::configurationAdded, this, &AsemanNetworkManager::configureAdded);
    connect(p->network, &QNetworkConfigurationManager::configurationChanged, this, &AsemanNetworkManager::configureChanged);
    connect(p->network, &QNetworkConfigurationManager::configurationRemoved, this, &AsemanNetworkManager::configureRemoved);

    connect(p->network, &QNetworkConfigurationManager::updateCompleted, this, &AsemanNetworkManager::updateCheck);
    connect(p->updateTimer, &QTimer::timeout, this, &AsemanNetworkManager::updateCheck);

    for(const QNetworkConfiguration &config: p->network->allConfigurations())
        configureAdded(config);

    updateCheck();
}

QString AsemanNetworkManager::defaultNetworkIdentifier() const
{
    return p->lastConfig.identifier();
}

AsemanNetworkManagerItem *AsemanNetworkManager::defaultNetwork() const
{
    return p->defaultItem;
}

QVariantMap AsemanNetworkManager::configurations() const
{
    return p->map;
}

void AsemanNetworkManager::setInterval(qint32 ms)
{
    if(p->updateTimer->interval() == ms)
        return;

    p->updateTimer->setInterval(ms);
    p->updateTimer->stop();
    p->updateTimer->start();

    Q_EMIT intervalChanged();
}

qint32 AsemanNetworkManager::interval() const
{
    return p->updateTimer->interval();
}

void AsemanNetworkManager::configureChanged(const QNetworkConfiguration &config)
{
    AsemanNetworkManagerItem *item = p->map.value(config.identifier()).value<AsemanNetworkManagerItem*>();
    if(item)
        item->operator =(config);
}

void AsemanNetworkManager::configureAdded(const QNetworkConfiguration &config)
{
    AsemanNetworkManagerItem *item = new AsemanNetworkManagerItem(this);
    item->operator =(config);
    p->map[config.identifier()] = QVariant::fromValue<AsemanNetworkManagerItem*>(item);

    Q_EMIT configurationsChanged();
}

void AsemanNetworkManager::configureRemoved(const QNetworkConfiguration &config)
{
    AsemanNetworkManagerItem *item = p->map.take(config.identifier()).value<AsemanNetworkManagerItem*>();
    if(item)
        item->deleteLater();

    Q_EMIT configurationsChanged();
}

void AsemanNetworkManager::updateCheck()
{
    p->defaultItem->operator =(p->network->defaultConfiguration());

    if(p->lastConfig.identifier() == p->network->defaultConfiguration().identifier())
    {
        p->lastConfig = p->network->defaultConfiguration();
        return;
    }

    p->lastConfig = p->network->defaultConfiguration();
    Q_EMIT defaultNetworkIdentifierChanged();
}

AsemanNetworkManager::~AsemanNetworkManager()
{
    delete p;
}
