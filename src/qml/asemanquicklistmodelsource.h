#ifndef ASEMANQUICKLISTMODELSOURCE_H
#define ASEMANQUICKLISTMODELSOURCE_H

#include <QObject>
#include <QVariant>

#include "asemantools_global.h"

class LIBQTASEMAN_QML_EXPORT AsemanQuickListModelSource : public QObject
{
    Q_OBJECT
    class Private;

    Q_PROPERTY(QVariant source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QVariantList data READ data NOTIFY dataChanged)

public:
    AsemanQuickListModelSource(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickListModelSource();

    void setSource(const QVariant &source);
    QVariant source() const;

    void setPath(const QString &path);
    QString path() const;

    QVariantList data() const;

Q_SIGNALS:
    void sourceChanged();
    void pathChanged();
    void dataChanged();

public Q_SLOTS:
    void refresh();

private:
    Private *p;
};

#endif // ASEMANQUICKLISTMODELSOURCE_H
