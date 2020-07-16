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

#include "asemanfiledownloaderqueueitem.h"
#include "asemanfiledownloaderqueue.h"
#include "asemandevices.h"

#include <QPointer>

class AsemanFileDownloaderQueueItemPrivate
{
public:
    QPointer<AsemanFileDownloaderQueue> queue;
    QString source;
    QString result;
    QString fileName;
    QVariantMap header;
    qreal percent;
};

AsemanFileDownloaderQueueItem::AsemanFileDownloaderQueueItem(QObject *parent) :
    QObject(parent)
{
    p = new AsemanFileDownloaderQueueItemPrivate;
    p->percent = 0;
}

void AsemanFileDownloaderQueueItem::setSource(const QString &url)
{
    if(p->source == url)
        return;

    p->source = url;
    Q_EMIT sourceChanged();

    refresh();
}

QString AsemanFileDownloaderQueueItem::source() const
{
    return p->source;
}

void AsemanFileDownloaderQueueItem::setFileName(const QString &name)
{
    if(p->fileName == name)
        return;

    p->fileName = name;
    Q_EMIT fileNameChanged();

    refresh();
}

QString AsemanFileDownloaderQueueItem::fileName() const
{
    return p->fileName;
}

void AsemanFileDownloaderQueueItem::setHeader(const QVariantMap &header)
{
    if (p->header == header)
        return;

    p->header = header;
    Q_EMIT headerChanged();
}

QVariantMap AsemanFileDownloaderQueueItem::header() const
{
    return p->header;
}

qreal AsemanFileDownloaderQueueItem::percent() const
{
    return p->percent;
}

void AsemanFileDownloaderQueueItem::setDownloaderQueue(AsemanFileDownloaderQueue *queue)
{
    if(p->queue == queue)
        return;

    if(p->queue)
    {
        disconnect(p->queue, &AsemanFileDownloaderQueue::finished, this, &AsemanFileDownloaderQueueItem::finished);
        disconnect(p->queue, &AsemanFileDownloaderQueue::progressChanged, this, &AsemanFileDownloaderQueueItem::progressChanged);
    }

    p->queue = queue;
    Q_EMIT downloaderQueueChanged();

    if(p->queue)
    {
        connect(p->queue, &AsemanFileDownloaderQueue::finished, this, &AsemanFileDownloaderQueueItem::finished);
        connect(p->queue, &AsemanFileDownloaderQueue::progressChanged, this, &AsemanFileDownloaderQueueItem::progressChanged);
    }

    refresh();
}

AsemanFileDownloaderQueue *AsemanFileDownloaderQueueItem::downloaderQueue() const
{
    return p->queue;
}

QString AsemanFileDownloaderQueueItem::result() const
{
    return p->result;
}

void AsemanFileDownloaderQueueItem::finished(const QString &url, const QString &fileName)
{
    if(p->source != url || p->fileName != fileName)
        return;

    QString dest = (p->queue->destination().count()? p->queue->destination() + QStringLiteral("/") : QStringLiteral(""));

    p->result = AsemanDevices::localFilesPrePath() + dest + fileName;
    Q_EMIT resultChanged();

    p->percent = 100;
    Q_EMIT percentChanged();
}

void AsemanFileDownloaderQueueItem::progressChanged(const QString &url, const QString &fileName, qreal percent)
{
    if(p->source != url || p->fileName != fileName)
        return;

    p->percent = percent;
    Q_EMIT percentChanged();
}

void AsemanFileDownloaderQueueItem::refresh()
{
    if(p->source.isEmpty() || p->fileName.isEmpty())
        return;
    if(!p->queue)
        return;

    p->queue->download(p->source, p->fileName, p->header);
}

AsemanFileDownloaderQueueItem::~AsemanFileDownloaderQueueItem()
{
    delete p;
}
