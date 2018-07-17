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

#include "asemanquickitemimagegrabber.h"

#include <QQuickItem>
#include <QSharedPointer>
#include <QPointer>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
#include <QQuickItemGrabResult>
#endif

class AsemanQuickItemImageGrabberPrivate
{
public:
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
    QSharedPointer<QQuickItemGrabResult> result;
#endif

    QPointer<QQuickItem> item;
    QImage image;
    QUrl defaultImage;
};

AsemanQuickItemImageGrabber::AsemanQuickItemImageGrabber(QObject *parent) :
    QObject(parent)
{
    p = new AsemanQuickItemImageGrabberPrivate;
}

void AsemanQuickItemImageGrabber::setItem(QQuickItem *item)
{
    if(p->item == item)
        return;

    p->item = item;
    Q_EMIT itemChanged();
}

QQuickItem *AsemanQuickItemImageGrabber::item() const
{
    return p->item;
}

void AsemanQuickItemImageGrabber::setDefaultImage(const QUrl &url)
{
    if(p->defaultImage == url)
        return;

    p->defaultImage = url;
    Q_EMIT defaultImageChanged();
}

QUrl AsemanQuickItemImageGrabber::defaultImage() const
{
    return p->defaultImage;
}

QImage AsemanQuickItemImageGrabber::image() const
{
    return p->image;
}

void AsemanQuickItemImageGrabber::start()
{
    if(!p->item)
        return;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
    p->result = p->item->grabToImage();
    if(p->result.isNull())
    {
        QMetaObject::invokeMethod(this, "ready", Qt::QueuedConnection );
        return;
    }
    connect(p->result.data(), &QQuickItemGrabResult::ready, this, &AsemanQuickItemImageGrabber::ready);
#else
    QMetaObject::invokeMethod(this, "ready", Qt::QueuedConnection );
#endif
}

void AsemanQuickItemImageGrabber::ready()
{
    if(!p->item)
        return;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
    if(!p->result)
        return;

    disconnect(p->result.data(), &QQuickItemGrabResult::ready, this, &AsemanQuickItemImageGrabber::ready);

    p->image = p->result->image();
    Q_EMIT imageChanged();
#else
    p->image = QImage(p->defaultImage.toLocalFile());
    Q_EMIT imageChanged();
#endif
}

AsemanQuickItemImageGrabber::~AsemanQuickItemImageGrabber()
{
    delete p;
}
