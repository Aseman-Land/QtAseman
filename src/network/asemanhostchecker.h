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

#ifndef ASEMANHOSTCHECKER_H
#define ASEMANHOSTCHECKER_H

#include <QObject>
#include <QTcpSocket>

#include "asemannetwork_global.h"

class AsemanPingPrivate;
class LIBQTASEMAN_NETWORK_EXPORT AsemanHostChecker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host     READ host     WRITE setHost     NOTIFY hostChanged)
    Q_PROPERTY(qint32  port     READ port     WRITE setPort     NOTIFY portChanged)
    Q_PROPERTY(qint32  interval READ interval WRITE setInterval NOTIFY intervalChanged)

    Q_PROPERTY(bool available READ available NOTIFY availableChanged)

public:
    AsemanHostChecker(QObject *parent = 0);
    virtual ~AsemanHostChecker();

    void setHost(const QString &host);
    QString host() const;

    void setPort(qint32 port);
    qint32 port() const;

    void setInterval(qint32 ms);
    qint32 interval() const;

    bool available() const;

Q_SIGNALS:
    void hostChanged();
    void portChanged();
    void intervalChanged();
    void availableChanged();

private Q_SLOTS:
    void socketStateChanged(QAbstractSocket::SocketState socketState);
    void socketError(QAbstractSocket::SocketError socketError);
    void timedOut();
    void refresh();

private:
    void setAvailable(bool stt);
    void createSocket();

private:
    AsemanPingPrivate *p;
};

#endif // ASEMANHOSTCHECKER_H
