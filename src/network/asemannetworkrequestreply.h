/*
    Copyright (C) 2019 Aseman Team
    http://aseman.io

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANNETWORKREQUESTREPLY_H
#define ASEMANNETWORKREQUESTREPLY_H

#include <QNetworkReply>
#include <QObject>

#include "asemannetwork_global.h"

class LIBQTASEMAN_NETWORK_EXPORT AsemanNetworkRequestReply : public QObject
{
    Q_OBJECT
    class Private;

public:
    AsemanNetworkRequestReply(bool ignoreSslErrors, QNetworkReply *reply = Q_NULLPTR);
    virtual ~AsemanNetworkRequestReply();

    qint32 statusCode() const;
    QVariantMap headers() const;

Q_SIGNALS:
    void finished(qint32 status, const QByteArray &data);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void error(const QString &errorString, QNetworkReply::NetworkError errorCode);
    void sslErrors(const QString &errorString);

public Q_SLOTS:
    void abort();

private:
    Private *p;
};

typedef AsemanNetworkRequestReply QAsemanNetworkRequestReply;

#endif // ASEMANNETWORKREQUESTREPLY_H
