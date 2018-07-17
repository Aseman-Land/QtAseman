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

#include "asemannetworksleepmanager.h"
#include "asemanhostchecker.h"
#include "asemannetworkmanager.h"
#include "asemannetworkmanageritem.h"

#include <QPointer>
#include <QTimer>
#include <QDebug>

class AsemanNetworkSleepManagerPrivate
{
public:
    AsemanHostChecker *hostCheker;
    AsemanNetworkManager *networkManager;
    QPointer<AsemanNetworkManagerItem> defaultNetwork;
    bool available;
    bool forceDisable;
    bool networkManagerState;

    QTimer *resetTimer;
};

AsemanNetworkSleepManager::AsemanNetworkSleepManager(QObject *parent) :
    QObject(parent)
{
    p = new AsemanNetworkSleepManagerPrivate;
    p->hostCheker = new AsemanHostChecker(this);
    p->available = false;
    p->forceDisable = false;
    p->networkManagerState = true;

    p->networkManager = new AsemanNetworkManager(this);

    p->resetTimer = new QTimer(this);
    p->resetTimer->setInterval(2000);
    p->resetTimer->setSingleShot(true);

    connect(p->hostCheker, &AsemanHostChecker::hostChanged, this, &AsemanNetworkSleepManager::hostChanged);
    connect(p->hostCheker, &AsemanHostChecker::portChanged,this, &AsemanNetworkSleepManager::portChanged);
    connect(p->hostCheker, &AsemanHostChecker::intervalChanged, this, &AsemanNetworkSleepManager::intervalChanged);
    connect(p->hostCheker, &AsemanHostChecker::availableChanged, this, &AsemanNetworkSleepManager::updateAvailablity);

    connect(p->resetTimer, &QTimer::timeout, this, &AsemanNetworkSleepManager::finishResetTimer);

    connect(p->networkManager, &AsemanNetworkManager::defaultNetworkChanged, this, &AsemanNetworkSleepManager::defaultNetworkChanged);

    defaultNetworkChanged();
    updateAvailablity();
}

void AsemanNetworkSleepManager::setHost(const QString &host)
{
    p->hostCheker->setHost(host);
}

QString AsemanNetworkSleepManager::host() const
{
    return p->hostCheker->host();
}

void AsemanNetworkSleepManager::setPort(qint32 port)
{
    p->hostCheker->setPort(port);
}

qint32 AsemanNetworkSleepManager::port() const
{
    return p->hostCheker->port();
}

void AsemanNetworkSleepManager::setInterval(qint32 ms)
{
    p->hostCheker->setInterval(ms);
}

qint32 AsemanNetworkSleepManager::interval() const
{
    return p->hostCheker->interval();
}

void AsemanNetworkSleepManager::setNetworkManager(bool stt)
{
    if(p->networkManagerState == stt)
        return;

    p->networkManagerState = stt;
    updateAvailablity();
    Q_EMIT networkManagerChanged();
}

bool AsemanNetworkSleepManager::networkManager() const
{
    return p->networkManagerState;
}

bool AsemanNetworkSleepManager::available() const
{
    return p->available && !p->forceDisable;
}

void AsemanNetworkSleepManager::defaultNetworkChanged()
{
    if(p->defaultNetwork)
    {
        disconnect(p->defaultNetwork, &AsemanNetworkManagerItem::bearerTypeChanged, this, &AsemanNetworkSleepManager::networkBearerTypeChanged);
        disconnect(p->defaultNetwork, &AsemanNetworkManagerItem::bearerTypeFamilyChanged, this, &AsemanNetworkSleepManager::networkBearerTypeFamilyChanged);
        disconnect(p->defaultNetwork, &AsemanNetworkManagerItem::identifierChanged, this, &AsemanNetworkSleepManager::networkIdentifierChanged);
        disconnect(p->defaultNetwork, &AsemanNetworkManagerItem::isValidChanged, this, &AsemanNetworkSleepManager::networkIsValidChanged);
        disconnect(p->defaultNetwork, &AsemanNetworkManagerItem::stateChanged, this, &AsemanNetworkSleepManager::networkStateChanged);
        disconnect(p->defaultNetwork, &AsemanNetworkManagerItem::typeChanged, this, &AsemanNetworkSleepManager::networkTypeChanged);
    }

    p->defaultNetwork = p->networkManager->defaultNetwork();
    if(p->defaultNetwork)
    {
        connect(p->defaultNetwork, &AsemanNetworkManagerItem::bearerTypeChanged, this, &AsemanNetworkSleepManager::networkBearerTypeChanged);
        connect(p->defaultNetwork, &AsemanNetworkManagerItem::bearerTypeFamilyChanged, this, &AsemanNetworkSleepManager::networkBearerTypeFamilyChanged);
        connect(p->defaultNetwork, &AsemanNetworkManagerItem::identifierChanged, this, &AsemanNetworkSleepManager::networkIdentifierChanged);
        connect(p->defaultNetwork, &AsemanNetworkManagerItem::isValidChanged, this, &AsemanNetworkSleepManager::networkIsValidChanged);
        connect(p->defaultNetwork, &AsemanNetworkManagerItem::stateChanged, this, &AsemanNetworkSleepManager::networkStateChanged);
        connect(p->defaultNetwork, &AsemanNetworkManagerItem::typeChanged, this, &AsemanNetworkSleepManager::networkTypeChanged);
    }
}

void AsemanNetworkSleepManager::networkRecheckAll()
{
    networkBearerTypeChanged();
    networkBearerTypeFamilyChanged();
    networkIdentifierChanged();
    networkIsValidChanged();
    networkStateChanged();
    networkTypeChanged();
}

void AsemanNetworkSleepManager::networkBearerTypeChanged()
{
    updateAvailablity();
}

void AsemanNetworkSleepManager::networkBearerTypeFamilyChanged()
{
    updateAvailablity();
}

void AsemanNetworkSleepManager::networkIdentifierChanged()
{
    startResetTimer();
}

void AsemanNetworkSleepManager::networkIsValidChanged()
{
    updateAvailablity();
}

void AsemanNetworkSleepManager::networkStateChanged()
{
    updateAvailablity();
}

void AsemanNetworkSleepManager::networkTypeChanged()
{
    updateAvailablity();
}

void AsemanNetworkSleepManager::updateAvailablity()
{
    bool networkState = true;
    if(p->defaultNetwork && p->defaultNetwork->isValid() && p->networkManagerState)
    {
        networkState = (
                    p->defaultNetwork->bearerType() != AsemanNetworkManagerItem::BearerUnknown &&
                    p->defaultNetwork->bearerTypeFamily() != AsemanNetworkManagerItem::BearerUnknown &&
                    p->defaultNetwork->isValid() &&
                    p->defaultNetwork->state() == AsemanNetworkManagerItem::Active &&
                    p->defaultNetwork->type() == AsemanNetworkManagerItem::InternetAccessPoint
                );
    }

    bool hostState = p->hostCheker->available();
    setAvailable(hostState && networkState);
}

void AsemanNetworkSleepManager::setAvailable(bool stt)
{
    if(stt == p->available && !p->forceDisable)
        return;

    p->available = stt;
    emitAvailableChanged();
}

void AsemanNetworkSleepManager::emitAvailableChanged()
{
    Q_EMIT availableChanged();
    if(available())
        Q_EMIT wake();
    else
        Q_EMIT sleep();
}

void AsemanNetworkSleepManager::startResetTimer()
{
    p->resetTimer->stop();
    p->resetTimer->start();

    bool previous = available();
    p->forceDisable = true;
    if(available() != previous)
        emitAvailableChanged();
}

void AsemanNetworkSleepManager::finishResetTimer()
{
    bool previous = available();
    p->forceDisable = false;
    if(available() != previous)
        emitAvailableChanged();
}

AsemanNetworkSleepManager::~AsemanNetworkSleepManager()
{
    delete p;
}
