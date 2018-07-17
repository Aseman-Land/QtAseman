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

#include "asemanhostchecker.h"

#include <QTcpSocket>
#include <QTimer>
#include <QDebug>
#include <QDebug>

class AsemanPingPrivate
{
public:
    QString host;
    qint32 port;
    qint32 interval;
    QTcpSocket *socket;
    QTimer *timer;
    bool reconnectAfterDisconnect;
    bool available;
};

AsemanHostChecker::AsemanHostChecker(QObject *parent) :
    QObject(parent)
{
    p = new AsemanPingPrivate;
    p->port = 80;
    p->interval = 0;
    p->reconnectAfterDisconnect = false;
    p->available = false;
    p->socket = 0;

    p->timer = new QTimer(this);
    p->timer->setSingleShot(false);

    connect(p->timer, &QTimer::timeout, this, &AsemanHostChecker::timedOut);
}

void AsemanHostChecker::setHost(const QString &host)
{
    if(p->host == host)
        return;

    p->host = host;
    refresh();
    Q_EMIT hostChanged();
}

QString AsemanHostChecker::host() const
{
    return p->host;
}

void AsemanHostChecker::setPort(qint32 port)
{
    if(p->port == port)
        return;

    p->port = port;
    refresh();
    Q_EMIT portChanged();
}

qint32 AsemanHostChecker::port() const
{
    return p->port;
}

void AsemanHostChecker::setInterval(qint32 ms)
{
    if(p->interval == ms)
        return;

    p->interval = ms;
    refresh();
    Q_EMIT intervalChanged();
}

qint32 AsemanHostChecker::interval() const
{
    return p->interval;
}

bool AsemanHostChecker::available() const
{
    return p->available;
}

void AsemanHostChecker::setAvailable(bool stt)
{
    if(p->available == stt)
        return;

    p->available = stt;
    Q_EMIT availableChanged();
}

void AsemanHostChecker::createSocket()
{
    if(p->socket)
    {
        disconnect(p->socket, &QTcpSocket::stateChanged, this, &AsemanHostChecker::socketStateChanged);
        disconnect(p->socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                   this, &AsemanHostChecker::socketError);
        p->socket->deleteLater();
    }

    p->socket = new QTcpSocket(this);

    connect(p->socket, &QTcpSocket::stateChanged, this, &AsemanHostChecker::socketStateChanged);
    connect(p->socket, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            this, &AsemanHostChecker::socketError);
}

void AsemanHostChecker::refresh()
{
    p->timer->stop();
    if(p->host.isEmpty() || p->port<=0 || p->interval<=0)
        return;

    p->timer->setInterval(p->interval);
    p->timer->start();

    createSocket();
    timedOut();
}

void AsemanHostChecker::socketStateChanged(QAbstractSocket::SocketState socketState)
{
    switch(static_cast<int>(socketState))
    {
    case QAbstractSocket::UnconnectedState:
        if(p->reconnectAfterDisconnect)
        {
            p->socket->connectToHost(p->host, p->port);
            p->reconnectAfterDisconnect = false;
        }
        break;

    case QAbstractSocket::HostLookupState:
        break;

    case QAbstractSocket::ConnectingState:
        break;

    case QAbstractSocket::ConnectedState:
        setAvailable(true);
        p->socket->disconnectFromHost();
        break;

    case QAbstractSocket::BoundState:
        break;

    case QAbstractSocket::ListeningState:
        break;

    case QAbstractSocket::ClosingState:
        break;
    }
}

void AsemanHostChecker::socketError(QAbstractSocket::SocketError socketError)
{
    if(socketError != QAbstractSocket::UnknownSocketError)
    {
        setAvailable(false);
    }
}

void AsemanHostChecker::timedOut()
{
    if(p->socket->state() == QAbstractSocket::UnconnectedState)
        p->socket->connectToHost(p->host, p->port);
    else
    {
        if(p->socket->state() != QAbstractSocket::ConnectedState)
            setAvailable(false);

        p->reconnectAfterDisconnect = true;
        p->socket->disconnectFromHost();
    }
}

AsemanHostChecker::~AsemanHostChecker()
{
    delete p;
}
