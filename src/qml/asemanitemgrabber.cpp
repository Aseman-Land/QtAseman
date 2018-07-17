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

#include "asemanitemgrabber.h"

#include <QPointer>
#include <QQuickItemGrabResult>
#include <QImageWriter>
#include <QDir>
#include <QUuid>

class AsemanItemGrabberPrivate
{
public:
    QPointer<QQuickItem> item;
    QSharedPointer<QQuickItemGrabResult> result;
    QString dest;
    QString suffix;
    QString fileName;
};

AsemanItemGrabber::AsemanItemGrabber(QObject *parent) :
    QObject(parent)
{
    p = new AsemanItemGrabberPrivate;
    p->suffix = QStringLiteral("png");
}

void AsemanItemGrabber::setItem(QQuickItem *item)
{
    if(p->item == item)
        return;

    p->item = item;
    Q_EMIT itemChanged();
}

QQuickItem *AsemanItemGrabber::item() const
{
    return p->item;
}

void AsemanItemGrabber::setSuffix(const QString &suffix)
{
    if(p->suffix == suffix)
        return;

    p->suffix = suffix;
    Q_EMIT suffixChanged();
}

QString AsemanItemGrabber::suffix() const
{
    return p->suffix;
}

void AsemanItemGrabber::setFileName(const QString &fileName)
{
    if(p->fileName == fileName)
        return;

    p->fileName = fileName;
    Q_EMIT fileNameChanged();
}

QString AsemanItemGrabber::fileName() const
{
    return p->fileName;
}

void AsemanItemGrabber::save(const QString &dest, const QSize &size)
{
    if(!p->item)
    {
        Q_EMIT failed();
        return;
    }

    p->result = p->item->grabToImage(size);
    if(!p->result)
    {
        Q_EMIT failed();
        return;
    }

    connect(p->result.data(), &QQuickItemGrabResult::ready, this, &AsemanItemGrabber::ready);

    QDir().mkpath(dest);

    QString fileName = p->fileName;
    if(fileName.isEmpty())
        fileName = QUuid::createUuid().toString().remove(QStringLiteral("{")).remove(QStringLiteral("}"));
    if(!p->suffix.isEmpty())
        fileName += QStringLiteral(".") + p->suffix;

    p->dest = dest + QStringLiteral("/") + fileName;
}

void AsemanItemGrabber::ready()
{
    disconnect(p->result.data(), &QQuickItemGrabResult::ready, this, &AsemanItemGrabber::ready);

    const QImage & img = p->result->image();

    QImageWriter writer(p->dest);
    writer.write(img);

    Q_EMIT saved(p->dest);
}

AsemanItemGrabber::~AsemanItemGrabber()
{
    delete p;
}
