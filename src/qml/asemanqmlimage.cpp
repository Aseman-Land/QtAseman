#include "asemanqmlimage.h"
#include "asemantools.h"

#include <QPainter>
#include <QMutex>
#include <QImageReader>
#include <QImage>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QQmlContext>

class AsemanQmlImage::Private
{
public:
    QUrl source;
    int fillMode;
    bool asynchronous;
    bool autoTransform;
    bool cache;
    int horizontalAlignment;
    int verticalAlignment;
    bool mirror;
    bool smooth;
    qreal progress;
    QMutex mutex;

    QString cacheHash;
    QImage cacheImage;
};

AsemanQmlImage::AsemanQmlImage(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    p = new Private;
    p->fillMode = PreserveAspectFit;
    p->asynchronous = false;
    p->autoTransform = false;
    p->cache = true;
    p->horizontalAlignment = 0;
    p->verticalAlignment = 0;
    p->mirror = false;
    p->progress = 0;
    p->smooth = false;
//    setRenderTarget(FramebufferObject);
}

void AsemanQmlImage::paint(QPainter *painter)
{
    p->mutex.lock();
    QUrl source = p->source;
    QSizeF paintSize = paintedSize();
    p->mutex.unlock();

    QString cacheHash = hash();
    if(cacheHash != p->cacheHash)
    {
        QString path = AsemanTools::urlToLocalPath(source);
        if(!QFileInfo::exists(path))
            return;

        QImageReader reader(path);
        reader.setScaledSize(paintSize.toSize());

        p->cacheImage = reader.read();
        p->cacheHash = cacheHash;
    }

    qreal x = width()/2 - p->cacheImage.width()/2;
    qreal y = height()/2 - p->cacheImage.height()/2;


    painter->drawImage(x, y, p->cacheImage);
}

void AsemanQmlImage::setSource(const QUrl &_src)
{
    QUrl source = _src;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    const QQmlContext *context = qmlContext(this);
    if (context)
        source = context->resolvedUrl(source);
#endif

    if(p->source == source)
        return;

    p->mutex.lock();
    p->source = source;
    p->mutex.unlock();

    refresh();
    Q_EMIT sourceChanged();
}

QUrl AsemanQmlImage::source() const
{
    return p->source;
}

void AsemanQmlImage::setFillMode(int fillMode)
{
    if(p->fillMode == fillMode)
        return;

    p->mutex.lock();
    p->fillMode = fillMode;
    p->mutex.unlock();

    refresh();
    Q_EMIT fillModeChanged();
}

int AsemanQmlImage::fillMode() const
{
    return p->fillMode;
}

void AsemanQmlImage::setAsynchronous(bool asynchronous)
{
    if(p->asynchronous == asynchronous)
        return;

    p->mutex.lock();
    p->asynchronous = asynchronous;
    p->mutex.unlock();

    refresh();
    Q_EMIT asynchronousChanged();
}

bool AsemanQmlImage::asynchronous() const
{
    return p->asynchronous;
}

void AsemanQmlImage::setAutoTransform(bool autoTransform)
{
    if(p->autoTransform == autoTransform)
        return;

    p->mutex.lock();
    p->autoTransform = autoTransform;
    p->mutex.unlock();

    refresh();
    Q_EMIT autoTransformChanged();
}

bool AsemanQmlImage::autoTransform() const
{
    return p->autoTransform;
}

void AsemanQmlImage::setCache(bool cache)
{
    if(p->cache == cache)
        return;

    p->mutex.lock();
    p->cache = cache;
    p->mutex.unlock();

    refresh();
    Q_EMIT cacheChanged();
}

bool AsemanQmlImage::cache() const
{
    return p->cache;
}

void AsemanQmlImage::setHorizontalAlignment(int horizontalAlignment)
{
    if(p->horizontalAlignment == horizontalAlignment)
        return;

    p->mutex.lock();
    p->horizontalAlignment = horizontalAlignment;
    p->mutex.unlock();

    refresh();
    Q_EMIT horizontalAlignmentChanged();
}

int AsemanQmlImage::horizontalAlignment() const
{
    return p->horizontalAlignment;
}

void AsemanQmlImage::setVerticalAlignment(int verticalAlignment)
{
    if(p->verticalAlignment == verticalAlignment)
        return;

    p->mutex.lock();
    p->verticalAlignment = verticalAlignment;
    p->mutex.unlock();

    refresh();
    Q_EMIT verticalAlignmentChanged();
}

int AsemanQmlImage::verticalAlignment() const
{
    return p->verticalAlignment;
}

void AsemanQmlImage::setMipmap(bool mipmap)
{
    if(QQuickPaintedItem::mipmap() == mipmap)
        return;


    p->mutex.lock();
    QQuickPaintedItem::setMipmap(mipmap);
    p->mutex.unlock();

    refresh();
    Q_EMIT mipmapChanged();
}

bool AsemanQmlImage::mipmap() const
{
    return QQuickPaintedItem::mipmap();
}

void AsemanQmlImage::setMirror(bool mirror)
{
    if(p->mirror == mirror)
        return;

    p->mutex.lock();
    p->mirror = mirror;
    p->mutex.unlock();

    refresh();
    Q_EMIT mirrorChanged();
}

bool AsemanQmlImage::mirror() const
{
    return p->mirror;
}

void AsemanQmlImage::setSmooth(bool smooth)
{
    if(p->smooth == smooth)
        return;

    p->mutex.lock();
    p->smooth = smooth;
    p->mutex.unlock();

    refresh();
    Q_EMIT smoothChanged();
}

bool AsemanQmlImage::smooth() const
{
    return p->smooth;
}

qreal AsemanQmlImage::paintedHeight() const
{
    return paintedSize().height();
}

qreal AsemanQmlImage::paintedWidth() const
{
    return paintedSize().width();
}

QSize AsemanQmlImage::imageSize() const
{
    QString path = AsemanTools::urlToLocalPath(p->source);
    QImageReader reader(path);
    return reader.size();
}

QSizeF AsemanQmlImage::paintedSize() const
{
    qreal ratio = width()/height();

    QSize imgSize = imageSize();
    qreal imgRatio = (qreal)imgSize.width()/imgSize.height();

    QSizeF res;
    switch(p->fillMode)
    {
    case PreserveAspectCrop:
    {
        if(ratio > imgRatio)
        {
            res.setWidth(width());
            res.setHeight(width()/imgRatio);
        }
        else
        {
            res.setWidth(height()*imgRatio);
            res.setHeight(height());
        }
    }
        break;

    case PreserveAspectFit:
    {
        if(ratio > imgRatio)
        {
            res.setWidth(height()*imgRatio);
            res.setHeight(height());
        }
        else
        {
            res.setWidth(width());
            res.setHeight(width()/imgRatio);
        }
    }
        break;

    case Stretch:
    {
        res.setWidth(width());
        res.setHeight(height());
    }
        break;

    case Tile:
    {
        res = imgSize;
        break;
    }
    }

    return res;
}

qreal AsemanQmlImage::progress() const
{
    return p->progress;
}

void AsemanQmlImage::refresh()
{
    update();
}

QString AsemanQmlImage::hash()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << p->asynchronous;
    stream << p->autoTransform;
    stream << p->cache;
    stream << p->fillMode;
    stream << p->horizontalAlignment;
    stream << p->mirror;
    stream << p->smooth;
    stream << p->source;
    stream << p->verticalAlignment;

    return QString::fromUtf8(QCryptographicHash::hash(data, QCryptographicHash::Md5).toHex());
}

AsemanQmlImage::~AsemanQmlImage()
{
    delete p;
}
