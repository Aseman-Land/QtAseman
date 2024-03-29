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
#include <QVariantMap>

#include "asemannetwork_global.h"
#include "asemanfiledownloaderqueue.h"

class AsemanFileDownloaderQueue;
class AsemanFileDownloaderQueueItemPrivate;
class LIBQTASEMAN_NETWORK_EXPORT AsemanFileDownloaderQueueItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QVariantMap header READ header WRITE setHeader NOTIFY headerChanged)
    Q_PROPERTY(qreal percent READ percent NOTIFY percentChanged)
    Q_PROPERTY(AsemanFileDownloaderQueue* downloaderQueue READ downloaderQueue WRITE setDownloaderQueue NOTIFY downloaderQueueChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)
    Q_PROPERTY(bool ignoreSslErrors READ ignoreSslErrors WRITE setIgnoreSslErrors NOTIFY ignoreSslErrorsChanged)

public:
    AsemanFileDownloaderQueueItem(QObject *parent = Q_NULLPTR);
    virtual ~AsemanFileDownloaderQueueItem();

    void setSource(const QString &url);
    QString source() const;

    void setFileName(const QString &name);
    QString fileName() const;

    void setHeader(const QVariantMap &header);
    QVariantMap header() const;

    qreal percent() const;

    void setDownloaderQueue(AsemanFileDownloaderQueue *queue);
    AsemanFileDownloaderQueue *downloaderQueue() const;

    QString result() const;

    bool ignoreSslErrors() const;
    void setIgnoreSslErrors(bool newIgnoreSslErrors);

Q_SIGNALS:
    void sourceChanged();
    void downloaderQueueChanged();
    void resultChanged();
    void fileNameChanged();
    void percentChanged();
    void headerChanged();
    void ignoreSslErrorsChanged();

private Q_SLOTS:
    void finished(const QString &url, const QString &fileName);
    void progressChanged(const QString &url, const QString &fileName, qreal percent);

private:
    void refresh();
    void download();

private:
    AsemanFileDownloaderQueueItemPrivate *p;
};

typedef AsemanFileDownloaderQueueItem QAsemanFileDownloaderQueueItem;

#endif // ASEMANFILEDOWNLOADERQUEUEITEM_H
