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

#ifndef ASEMANFILEDOWNLOADERQUEUE_H
#define ASEMANFILEDOWNLOADERQUEUE_H

#include <QObject>
#include <QUrl>

#include "asemannetwork_global.h"

class AsemanDownloader;
class AsemanFileDownloaderQueuePrivate;
class LIBQTASEMAN_NETWORK_EXPORT AsemanFileDownloaderQueue : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int capacity READ capacity WRITE setCapacity NOTIFY capacityChanged)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY destinationChanged)

public:
    AsemanFileDownloaderQueue(QObject *parent = 0);
    virtual ~AsemanFileDownloaderQueue();

    void setCapacity(int cap);
    int capacity() const;

    void setDestination(const QString &dest);
    QString destination() const;

public Q_SLOTS:
    void download(const QString &url, const QString &fileName);

Q_SIGNALS:
    void capacityChanged();
    void destinationChanged();
    void finished(const QString &url, const QString &fileName);
    void progressChanged(const QString &url, const QString &fileName, qreal percent);

private Q_SLOTS:
    void finishedSlt( const QByteArray & data );
    void recievedBytesChanged();

private:
    void next();
    AsemanDownloader *getDownloader();

private:
    AsemanFileDownloaderQueuePrivate *p;
};

typedef AsemanFileDownloaderQueue QAsemanFileDownloaderQueue;

#endif // ASEMANFILEDOWNLOADERQUEUE_H
