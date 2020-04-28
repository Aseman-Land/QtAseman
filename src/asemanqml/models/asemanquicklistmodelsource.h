#ifndef ASEMANQUICKLISTMODELSOURCE_H
#define ASEMANQUICKLISTMODELSOURCE_H

#include <QObject>
#include <QQmlListProperty>
#include <QVariant>

#include "asemanquicklistmodelcopyhint.h"

class AsemanQuickListModelSource : public QObject
{
    Q_OBJECT
    class Private;

    Q_PROPERTY(QVariant source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QVariantList data READ data NOTIFY dataChanged)

    Q_PROPERTY(QQmlListProperty<AsemanAbstractQuickListModelHint> hints READ hints NOTIFY hintsChanged)
    Q_CLASSINFO("DefaultProperty", "hints")

public:
    AsemanQuickListModelSource(QObject *parent = Q_NULLPTR);
    virtual ~AsemanQuickListModelSource();

    void setSource(const QVariant &source);
    QVariant source() const;

    void setPath(const QString &path);
    QString path() const;

    QVariantList data() const;

    QQmlListProperty<AsemanAbstractQuickListModelHint> hints();

Q_SIGNALS:
    void hintsChanged();
    void sourceChanged();
    void pathChanged();
    void dataChanged();

public Q_SLOTS:
    void refresh();

private:
    static void append(QQmlListProperty<AsemanAbstractQuickListModelHint> *p, AsemanAbstractQuickListModelHint *v);
    static int count(QQmlListProperty<AsemanAbstractQuickListModelHint> *p);
    static AsemanAbstractQuickListModelHint *at(QQmlListProperty<AsemanAbstractQuickListModelHint> *p, int idx);
    static void clear(QQmlListProperty<AsemanAbstractQuickListModelHint> *p);

private:
    Private *p;
};

#endif // ASEMANQUICKLISTMODELSOURCE_H
