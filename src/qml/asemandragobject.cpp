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

#include "asemandragobject.h"
#include "asemanmimedata.h"

#include <QDrag>
#include <QPointer>
#include <QMimeData>
#include <QDebug>
#include <QPixmap>
#include <QQmlContext>

class AsemanDragObjectPrivate
{
public:
    QPointer<AsemanMimeData> mime;
    QPointer<QQuickItem> source;

    QUrl image;
    QImage imageData;

    int dropAction;
    QPoint hotSpot;

    QPointer<QDrag> drag;

    bool onDrag;
};

AsemanDragObject::AsemanDragObject(QObject *parent) :
    QObject(parent)
{
    p = new AsemanDragObjectPrivate;
    p->dropAction = Qt::MoveAction;
    p->onDrag = false;
}

void AsemanDragObject::setMimeData(AsemanMimeData *mime)
{
    if(p->mime == mime)
        return;

    p->mime = mime;
    Q_EMIT mimeDataChanged();
}

AsemanMimeData *AsemanDragObject::mimeData() const
{
    return p->mime;
}

void AsemanDragObject::setDropAction(int act)
{
    if(p->dropAction == act)
        return;

    p->dropAction = act;
    Q_EMIT dropActionChanged();
}

int AsemanDragObject::dropAction() const
{
    return p->dropAction;
}

void AsemanDragObject::setSource(QQuickItem *item)
{
    if(p->source == item)
        return;

    p->source = item;
    Q_EMIT sourceChanged();
}

QQuickItem *AsemanDragObject::source() const
{
    return p->source;
}

void AsemanDragObject::setImage(const QUrl &_url)
{
    QUrl url = _url;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    const QQmlContext *context = qmlContext(this);
    if (context)
        url = context->resolvedUrl(url);
#endif

    if(p->image == url)
        return;

    p->image = url;
    Q_EMIT imageChanged();
}

QUrl AsemanDragObject::image() const
{
    return p->image;
}

void AsemanDragObject::setImageData(const QImage &img)
{
    if(p->imageData == img)
        return;

    p->imageData = img;
    Q_EMIT imageDataChanged();
}

QImage AsemanDragObject::imageData() const
{
    return p->imageData;
}

bool AsemanDragObject::dragging() const
{
    return p->onDrag;
}

void AsemanDragObject::setHotSpot(const QPoint &point)
{
    if(p->hotSpot == point)
        return;

    p->hotSpot = point;
    Q_EMIT hotSpotChanged();
}

QPoint AsemanDragObject::hotSpot() const
{
    return p->hotSpot;
}

int AsemanDragObject::start()
{
    if(!p->source)
    {
        qDebug() << "DragObject: source property is null!";
        return -1;
    }
    if(p->onDrag)
        return -1;

    p->onDrag = true;
    Q_EMIT draggingChanged();

    QMimeData *mime = new QMimeData();
    if(p->mime)
    {
        mime->setText(p->mime->text());
        mime->setHtml(p->mime->html());
        mime->setUrls(p->mime->urls());

        const QVariantMap &map = p->mime->dataMap();
        QMapIterator<QString,QVariant> i(map);
        while(i.hasNext())
        {
            i.next();
            mime->setData(i.key(), i.value().toByteArray());
        }
    }

    p->drag = new QDrag(p->source);
    p->drag->setMimeData(mime);
    if(!p->imageData.isNull())
    {
        p->drag->setPixmap(QPixmap::fromImage(p->imageData));
    }
    else
    if(p->image.isValid())
    {
        QString path = p->image.toString();
        if(path.left(4) == QStringLiteral("qrc:"))
            path = path.mid(3);

        p->drag->setPixmap( QPixmap(path) );
    }
    if(!p->hotSpot.isNull())
        p->drag->setHotSpot(p->hotSpot);

    int res = p->drag->exec( static_cast<Qt::DropAction>(p->dropAction) );

#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
    p->drag->deleteLater();
#endif

    p->source->ungrabMouse();
    p->source->ungrabTouchPoints();

    p->onDrag = false;
    Q_EMIT draggingChanged();

    return res;
}

AsemanDragObject::~AsemanDragObject()
{
    delete p;
}
