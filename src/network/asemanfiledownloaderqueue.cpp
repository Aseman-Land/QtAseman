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

#include "asemanfiledownloaderqueue.h"
#include "asemandownloader.h"

#include <QQueue>
#include <QStack>
#include <QSet>
#include <QFile>
#include <QFileInfo>
#include <QDir>

class AsemanFileDownloaderQueuePrivate
{
public:
    QStack<AsemanDownloader*> inactiveItems;
    QSet<AsemanDownloader*> activeItems;
    QQueue<QString> queue;
    QHash<QString, QPair<QSet<QString>, QVariantMap> > names;

    int capacity;
    QString destination;
};

AsemanFileDownloaderQueue::AsemanFileDownloaderQueue(QObject *parent) :
    QObject(parent)
{
    p = new AsemanFileDownloaderQueuePrivate;
    p->capacity = 10;
}

void AsemanFileDownloaderQueue::setCapacity(int cap)
{
    if(p->capacity == cap)
        return;

    p->capacity = cap;
    Q_EMIT capacityChanged();
}

int AsemanFileDownloaderQueue::capacity() const
{
    return p->capacity;
}

void AsemanFileDownloaderQueue::setDestination(const QString &dest)
{
    if(p->destination == dest)
        return;

    p->destination = dest;
    QDir().mkpath(p->destination);

    Q_EMIT destinationChanged();
}

QString AsemanFileDownloaderQueue::destination() const
{
    return p->destination;
}

void AsemanFileDownloaderQueue::download(const QString &url, const QString &fileName, const QVariantMap &header)
{
    if( QFileInfo((p->destination.count()? p->destination + QStringLiteral("/") : QStringLiteral("")) + fileName).exists() )
    {
        Q_EMIT progressChanged(url, fileName, 100);
        Q_EMIT finished(url, fileName);
        return;
    }

    auto &pair = p->names[url];
    pair.first.insert(fileName);
    pair.second = header;

    if(p->queue.contains(url))
        return;

    p->queue.append(url);
    next();
}

void AsemanFileDownloaderQueue::finishedSlt(const QByteArray &data)
{
    AsemanDownloader *downloader = static_cast<AsemanDownloader*>(sender());
    if(!downloader)
        return;

    const QString &url = downloader->path();
    auto names = p->names.value(url).first;
    for (auto name: names)
    {
        QFile file((p->destination.count()? p->destination + QStringLiteral("/") : QStringLiteral("")) + name);
        if(!file.open(QFile::WriteOnly))
            continue;

        file.write(data);
        file.close();
        Q_EMIT finished(url, name);
    }

    p->names.remove(url);
    p->activeItems.remove(downloader);
    p->inactiveItems.push(downloader);
    next();
}

void AsemanFileDownloaderQueue::recievedBytesChanged()
{
    AsemanDownloader *downloader = static_cast<AsemanDownloader*>(sender());
    if(!downloader)
        return;

    const qint64 total = downloader->totalBytes();
    const qint64 recieved = downloader->recievedBytes();
    const qreal percent = ((qreal)recieved/total)*100;
    const QString &url = downloader->path();
    const QSet<QString> names = p->names.value(url).first;
    for(const QString &name: names)
        Q_EMIT progressChanged(url, name, percent);
}

void AsemanFileDownloaderQueue::next()
{
    while(!p->inactiveItems.isEmpty() && p->inactiveItems.count()+p->activeItems.count()>p->capacity)
        p->inactiveItems.pop()->deleteLater();
    if(p->queue.isEmpty())
        return;

    AsemanDownloader *downloader = getDownloader();
    if(!downloader)
        return;

    const QString &url = p->queue.takeFirst();
    auto item = p->names.value(url);

    downloader->setPath(url);
    downloader->setHeader(item.second);
    downloader->start();
}

AsemanDownloader *AsemanFileDownloaderQueue::getDownloader()
{
    if(!p->inactiveItems.isEmpty())
        return p->inactiveItems.pop();
    if(p->activeItems.count() >= p->capacity)
        return 0;

    AsemanDownloader *result = new AsemanDownloader(this);
    p->activeItems.insert(result);

    connect(result, &AsemanDownloader::recievedBytesChanged, this, &AsemanFileDownloaderQueue::recievedBytesChanged);
    connect(result, &AsemanDownloader::finished, this, &AsemanFileDownloaderQueue::finishedSlt);

    return result;
}

AsemanFileDownloaderQueue::~AsemanFileDownloaderQueue()
{
    delete p;
}
