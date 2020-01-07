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

#ifndef ASEMANFILEDOWNLOADERQUEUEITEM_H
#define ASEMANFILEDOWNLOADERQUEUEITEM_H

#include <QObject>

#include "asemannetwork_global.h"

class AsemanFileDownloaderQueue;
class AsemanFileDownloaderQueueItemPrivate;
class LIBQTASEMAN_NETWORK_EXPORT AsemanFileDownloaderQueueItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(qreal percent READ percent NOTIFY percentChanged)
    Q_PROPERTY(AsemanFileDownloaderQueue* downloaderQueue READ downloaderQueue WRITE setDownloaderQueue NOTIFY downloaderQueueChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)

public:
    AsemanFileDownloaderQueueItem(QObject *parent = 0);
    virtual ~AsemanFileDownloaderQueueItem();

    void setSource(const QString &url);
    QString source() const;

    void setFileName(const QString &name);
    QString fileName() const;

    qreal percent() const;

    void setDownloaderQueue(AsemanFileDownloaderQueue *queue);
    AsemanFileDownloaderQueue *downloaderQueue() const;

    QString result() const;

Q_SIGNALS:
    void sourceChanged();
    void downloaderQueueChanged();
    void resultChanged();
    void fileNameChanged();
    void percentChanged();

private Q_SLOTS:
    void finished(const QString &url, const QString &fileName);
    void progressChanged(const QString &url, const QString &fileName, qreal percent);

private:
    void refresh();

private:
    AsemanFileDownloaderQueueItemPrivate *p;
};

typedef AsemanFileDownloaderQueueItem QAsemanFileDownloaderQueueItem;

#endif // ASEMANFILEDOWNLOADERQUEUEITEM_H
