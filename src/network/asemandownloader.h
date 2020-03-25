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

#ifndef ASEMANDOWNLOADER_H
#define ASEMANDOWNLOADER_H

#include <QObject>
#include <QStringList>

#include "asemannetwork_global.h"

class QNetworkReply;
class QSslError;
class AsemanDownloaderPrivate;
class LIBQTASEMAN_NETWORK_EXPORT AsemanDownloader : public QObject
{
    Q_PROPERTY(qint64 recievedBytes READ recievedBytes NOTIFY recievedBytesChanged)
    Q_PROPERTY(qint64 totalBytes READ totalBytes NOTIFY totalBytesChanged)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY destinationChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(int downloaderId READ downloaderId WRITE setDownloaderId NOTIFY downloaderIdChanged)
    Q_PROPERTY(bool downloading READ downloading NOTIFY downloadingChanged)

    Q_OBJECT
public:
    AsemanDownloader(QObject *parent = Q_NULLPTR);
    virtual ~AsemanDownloader();

    qint64 recievedBytes() const;
    qint64 totalBytes() const;

    void setDestination( const QString & dest );
    QString destination() const;

    void setPath( const QString & path );
    QString path() const;

    void setDownloaderId( int id );
    int downloaderId() const;

    bool downloading() const;

public Q_SLOTS:
    void start();
    void stop();

Q_SIGNALS:
    void recievedBytesChanged();
    void totalBytesChanged();
    void destinationChanged();
    void downloaderIdChanged();
    void pathChanged();
    void downloadingChanged();
    void error( const QStringList & error );
    void finished( const QByteArray & data );
    void finishedWithId( int id, const QByteArray & data );
    void failed();

private Q_SLOTS:
    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &list);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    void init_manager();

private:
    AsemanDownloaderPrivate *p;
};

typedef AsemanDownloader QAsemanDownloader;

#endif // ASEMANDOWNLOADER_H
