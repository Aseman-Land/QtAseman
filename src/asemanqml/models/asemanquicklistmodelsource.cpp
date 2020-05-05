#include "asemanquicklistmodelsource.h"

#include <QPointer>
#include <QDebug>

class AsemanQuickListModelSource::Private
{
public:
    QVariant source;
    QString path;

    QVariantList data;
    QPointer<QObject> networkRequest;
    QList<AsemanAbstractQuickListModelHint*> hints;
};

AsemanQuickListModelSource::AsemanQuickListModelSource(QObject *parent) :
    QObject(parent)
{
    p = new Private;
}

void AsemanQuickListModelSource::setSource(const QVariant &source)
{
    if (p->source == source)
        return;

    p->source = source;
    refresh();
    Q_EMIT sourceChanged();
}

QVariant AsemanQuickListModelSource::source() const
{
    return p->source;
}

void AsemanQuickListModelSource::setPath(const QString &path)
{
    if (p->path == path)
        return;

    p->path = path;
    refresh();
    Q_EMIT pathChanged();
}

QString AsemanQuickListModelSource::path() const
{
    return p->path;
}

QVariantList AsemanQuickListModelSource::data() const
{
    return p->data;
}

QQmlListProperty<AsemanAbstractQuickListModelHint> AsemanQuickListModelSource::hints()
{
    return QQmlListProperty<AsemanAbstractQuickListModelHint>(this, &p->hints,
                                                            QQmlListProperty<AsemanAbstractQuickListModelHint>::AppendFunction(append),
                                                            QQmlListProperty<AsemanAbstractQuickListModelHint>::CountFunction(count),
                                                            QQmlListProperty<AsemanAbstractQuickListModelHint>::AtFunction(at),
                                                            QQmlListProperty<AsemanAbstractQuickListModelHint>::ClearFunction(clear) );
}

void AsemanQuickListModelSource::refresh()
{
    QVariant data = AsemanAbstractQuickListModelHint::getPathValue(p->source, p->path);

    QVariantList vlist;
    switch (static_cast<int>(data.type()))
    {
    case QVariant::StringList:
    {
        QStringList list = data.toStringList();
        for (const QString &l: list)
            vlist << QVariantMap( {{"value", l}} );
    }
        break;
    case QVariant::Map:
    {
        QVariantMap map = data.toMap();
        QMapIterator<QString, QVariant> i(map);
        while (i.hasNext())
        {
            i.next();
           vlist << QVariantMap( {{"key", i.key()}, {"value", i.value()}} );
        }
    }
        break;
    case QVariant::Hash:
    {
        QVariantHash hash = data.toHash();
        QHashIterator<QString, QVariant> i(hash);
        while (i.hasNext())
        {
            i.next();
            vlist << QVariantMap( {{"key", i.key()}, {"value", i.value()}} );
        }
    }
        break;
    case QVariant::List:
    default:
        vlist = data.toList();
        break;
    }

    p->data.clear();
    for (const QVariant &l: vlist)
    {
        QVariantMap m = l.toMap();
        for (AsemanAbstractQuickListModelHint *h: p->hints)
            m = h->analyze(m);

        p->data << m;
    }

    Q_EMIT dataChanged();
}

void AsemanQuickListModelSource::append(QQmlListProperty<AsemanAbstractQuickListModelHint> *p, AsemanAbstractQuickListModelHint *v)
{
    AsemanQuickListModelSource *aobj = static_cast<AsemanQuickListModelSource*>(p->object);
    aobj->p->hints.append(v);
    Q_EMIT aobj->hintsChanged();
}

int AsemanQuickListModelSource::count(QQmlListProperty<AsemanAbstractQuickListModelHint> *p)
{
    AsemanQuickListModelSource *aobj = static_cast<AsemanQuickListModelSource*>(p->object);
    return aobj->p->hints.count();
}

AsemanAbstractQuickListModelHint *AsemanQuickListModelSource::at(QQmlListProperty<AsemanAbstractQuickListModelHint> *p, int idx)
{
    AsemanQuickListModelSource *aobj = static_cast<AsemanQuickListModelSource*>(p->object);
    return aobj->p->hints.at(idx);
}

void AsemanQuickListModelSource::clear(QQmlListProperty<AsemanAbstractQuickListModelHint> *p)
{
    AsemanQuickListModelSource *aobj = static_cast<AsemanQuickListModelSource*>(p->object);
    aobj->p->hints.clear();
    Q_EMIT aobj->hintsChanged();
}

AsemanQuickListModelSource::~AsemanQuickListModelSource()
{
    delete p;
}
