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

#include "asemanmimedata.h"

#include <QClipboard>
#include <QDataStream>
#include <QGuiApplication>
#include <QIODevice>
#include <QMimeData>

class AsemanMimeDataPrivate
{
public:
    QString text;
    QString html;
    QList<QUrl> urls;
    QVariantMap dataMap;
};

AsemanMimeData::AsemanMimeData(QObject *parent) :
    QObject(parent)
{
    p = new AsemanMimeDataPrivate;
}

void AsemanMimeData::setText(const QString &txt)
{
    if(p->text == txt)
        return;

    p->text = txt;
    Q_EMIT textChanged();
}

QString AsemanMimeData::text() const
{
    return p->text;
}

void AsemanMimeData::setHtml(const QString &html)
{
    if(p->html == html)
        return;

    p->html = html;
    Q_EMIT htmlChanged();
}

QString AsemanMimeData::html() const
{
    return p->html;
}

void AsemanMimeData::setUrls(const QList<QUrl> &urls)
{
    if(p->urls == urls)
        return;

    p->urls = urls;
    Q_EMIT urlsChanged();
}

QList<QUrl> AsemanMimeData::urls() const
{
    return p->urls;
}

void AsemanMimeData::setDataMap(const QVariantMap &map)
{
    if(p->dataMap == map)
        return;

    p->dataMap = map;
    Q_EMIT dataMapChanged();
}

QVariantMap AsemanMimeData::dataMap() const
{
    return p->dataMap;
}

QStringList AsemanMimeData::formats() const
{
    return p->dataMap.keys();
}

void AsemanMimeData::fetchClipboard()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    if(!clipboard) return;
    const QMimeData *mime = clipboard->mimeData();
    if(!mime) return;

    setUrls(mime->urls());
    setText(mime->text());
    setHtml(mime->html());

    QVariantMap data;
    for(const QString &format: mime->formats())
    {
        QVariant var;
        QByteArray bytes = mime->data(format);
        QDataStream stream(&bytes, QIODevice::ReadOnly);
        stream >> var;

        data[format] = var;
    }
    setDataMap(data);
}

QString AsemanMimeData::getDataAsString(const QString &type)
{
    return p->dataMap.value(type).toString();
}

AsemanMimeData::~AsemanMimeData()
{
    delete p;
}
