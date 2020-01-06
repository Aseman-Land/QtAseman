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

#include "asemannetworkrequestreply.h"

#include <QJsonDocument>
#include <QPointer>

class AsemanNetworkRequestReply::Private
{
public:
    QByteArray buffer;
    QPointer<QNetworkReply> reply;
    bool finishedEmited;
};

AsemanNetworkRequestReply::AsemanNetworkRequestReply(QNetworkReply *reply) :
    QObject(reply)
{
    p = new Private;
    p->reply = reply;
    p->finishedEmited = false;

    connect(reply, &QNetworkReply::readyRead, this, [this](){
        p->buffer += p->reply->readAll();
    });
    connect(reply, &QNetworkReply::sslErrors, this, [this](const QList<QSslError> &errors){
        p->reply->ignoreSslErrors(errors);
    });
    connect(reply, &QNetworkReply::finished, this, [this](){
        if (p->finishedEmited)
            return ;

        p->finishedEmited = true;
        Q_EMIT finished(statusCode(), p->buffer);

        p->reply->deleteLater();
        deleteLater();
    });
    connect(reply, &QNetworkReply::destroyed, this, [this](){
        if (p->finishedEmited)
            return ;

        p->finishedEmited = true;
        Q_EMIT finished(statusCode(), p->buffer);
    });
    connect(reply, &QNetworkReply::uploadProgress, this, &AsemanNetworkRequestReply::uploadProgress);
    connect(reply, &QNetworkReply::downloadProgress, this, &AsemanNetworkRequestReply::downloadProgress);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, [this, reply](QNetworkReply::NetworkError err){
        QVariant var = QVariant::fromValue<QNetworkReply::NetworkError>(err);
        var.convert(QVariant::String);

        QString errorString = var.toString().remove(QStringLiteral("QNetworkReply::"));
        if (reply->errorString().count())
            errorString += ": " + reply->errorString();

        Q_EMIT error(errorString, err);

        p->reply->deleteLater();
        deleteLater();
    });
}

void AsemanNetworkRequestReply::abort()
{
    if (!p->reply)
        return;

    p->buffer.clear();
    p->reply->abort();
}

qint32 AsemanNetworkRequestReply::statusCode() const
{
    if (!p->reply)
        return 0;

    QVariant status_code = p->reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (!status_code.isValid())
        return 0;

    return status_code.toString().toInt();
}

QVariantMap AsemanNetworkRequestReply::headers() const
{
    QVariantMap res;
    if (!p->reply)
        return res;

    QList<QByteArray> list = p->reply->rawHeaderList();
    for (const QByteArray &l: list)
        res[QString::fromUtf8(l).toLower()] = QString::fromUtf8(p->reply->rawHeader(l));

    return res;
}

AsemanNetworkRequestReply::~AsemanNetworkRequestReply()
{
    if (!p->finishedEmited)
        abort();

    delete p;
}
