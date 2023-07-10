#ifndef ASEMANQUICKLAYOUT_H
#define ASEMANQUICKLAYOUT_H

#include <QQuickItem>
#include <QTimer>

class AsemanQuickLayoutProperty;
class AsemanQuickLayout : public QQuickItem
{
    Q_OBJECT
public:
    AsemanQuickLayout(QQuickItem *parent = nullptr);
    virtual ~AsemanQuickLayout();

    static AsemanQuickLayoutProperty *qmlAttachedProperties(QObject *object);

public Q_SLOTS:
    void reload();

protected:
    void reloadDelayed();
    virtual void relocateChilds() {}

    void itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &value) override;

    AsemanQuickLayoutProperty *getAttached(QObject *object);

private:
    QTimer *mReloadTimer = nullptr;
};

class AsemanQuickLayoutProperty : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool fillWidth MEMBER mFillWidth NOTIFY changed)
    Q_PROPERTY(bool fillHeight MEMBER mFillHeight NOTIFY changed)

    Q_PROPERTY(qreal preferredWidth MEMBER mPreferredWidth NOTIFY changed)
    Q_PROPERTY(qreal preferredHeight MEMBER mPreferredHeight NOTIFY changed)

    Q_PROPERTY(qreal leftMargin MEMBER mLeftMargin NOTIFY changed)
    Q_PROPERTY(qreal topMargin MEMBER mTopMargin NOTIFY changed)
    Q_PROPERTY(qreal rightMargin MEMBER mRightMargin NOTIFY changed)
    Q_PROPERTY(qreal bottomMargin MEMBER mBottomMargin NOTIFY changed)

    Q_PROPERTY(qint32 alignment MEMBER mAlignment NOTIFY changed)

public:
    AsemanQuickLayoutProperty(QObject *parent = nullptr): QObject(parent) {}
    virtual ~AsemanQuickLayoutProperty() {}

Q_SIGNALS:
    void changed();

public:
    bool mFillWidth = false;
    bool mFillHeight = false;

    qreal mPreferredWidth = 0;
    qreal mPreferredHeight = 0;

    qreal mLeftMargin = 0;
    qreal mTopMargin = 0;
    qreal mRightMargin = 0;
    qreal mBottomMargin = 0;

    qint32 mAlignment = 0;
};

QML_DECLARE_TYPEINFO(AsemanQuickLayout, QML_HAS_ATTACHED_PROPERTIES)

#endif // ASEMANQUICKLAYOUT_H
