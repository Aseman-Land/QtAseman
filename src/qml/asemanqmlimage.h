#ifndef ASEMANQMLIMAGE_H
#define ASEMANQMLIMAGE_H

#include <QQuickPaintedItem>
#include <QUrl>
#include <QVariant>

#include "asemantools_global.h"

class LIBQTASEMAN_QML_EXPORT AsemanQmlImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_ENUMS(FillMode)

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)
    Q_PROPERTY(bool asynchronous READ asynchronous WRITE setAsynchronous NOTIFY asynchronousChanged)
    Q_PROPERTY(bool autoTransform READ autoTransform WRITE setAutoTransform NOTIFY autoTransformChanged)
    Q_PROPERTY(bool cache READ cache WRITE setCache NOTIFY cacheChanged)
    Q_PROPERTY(int horizontalAlignment READ horizontalAlignment WRITE setHorizontalAlignment NOTIFY horizontalAlignmentChanged)
    Q_PROPERTY(int verticalAlignment READ verticalAlignment WRITE setVerticalAlignment NOTIFY verticalAlignmentChanged)
    Q_PROPERTY(bool mipmap READ mipmap WRITE setMipmap NOTIFY mipmapChanged)
    Q_PROPERTY(bool mirror READ mirror WRITE setMirror NOTIFY mirrorChanged)
    Q_PROPERTY(qreal paintedWidth READ paintedWidth NOTIFY paintedSizeChanged)
    Q_PROPERTY(qreal paintedHeight READ paintedHeight NOTIFY paintedSizeChanged)
    Q_PROPERTY(qreal progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth NOTIFY smoothChanged)
    Q_PROPERTY(QSize sourceSize READ imageSize NOTIFY sourceSizeChanged)

    class Private;

public:
    enum FillMode {
        Stretch,
        PreserveAspectFit,
        PreserveAspectCrop,
        Tile
    };

    AsemanQmlImage(QQuickItem *parent = Q_NULLPTR);
    virtual ~AsemanQmlImage();

    virtual void paint(QPainter *painter);

    void setSource(const QUrl &source);
    QUrl source() const;

    void setFillMode(int fillMode);
    int fillMode() const;

    void setAsynchronous(bool asynchronous);
    bool asynchronous() const;

    void setAutoTransform(bool autoTransform);
    bool autoTransform() const;

    void setCache(bool cache);
    bool cache() const;

    void setHorizontalAlignment(int horizontalAlignment);
    int horizontalAlignment() const;

    void setVerticalAlignment(int verticalAlignment);
    int verticalAlignment() const;

    void setMipmap(bool mipmap);
    bool mipmap() const;

    void setMirror(bool mirror);
    bool mirror() const;

    void setSmooth(bool smooth);
    bool smooth() const;

    qreal paintedHeight() const;
    qreal paintedWidth() const;

    QSize imageSize() const;
    QSizeF paintedSize() const;

    qreal progress() const;

Q_SIGNALS:
    void sourceChanged();
    void fillModeChanged();
    void asynchronousChanged();
    void autoTransformChanged();
    void cacheChanged();
    void horizontalAlignmentChanged();
    void verticalAlignmentChanged();
    void mipmapChanged();
    void mirrorChanged();
    void paintedSizeChanged();
    void progressChanged();
    void smoothChanged();
    void sourceSizeChanged();

public Q_SLOTS:
    void refresh();

protected:
    QString hash();

private:
    Private *p;
};

#endif // ASEMANQMLIMAGE_H
