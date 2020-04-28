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

void AsemanQuickListModelSource::refresh()
{
    QVariant data = p->source;

    QStringList pathList = p->path.split(QStringLiteral("->"));
    for (const QString &pt: pathList)
    {
        QRegExp rx(QStringLiteral("\\w+\\s*\\[\\s*(\\d+)\\s*\\]"));
        int pos = 0;

        if ((pos = rx.indexIn(pt)) > 0 && pos + rx.matchedLength() == pt.length())
        {
            qint32 idx = rx.cap(1).toInt();
            QVariantList list = data.toList();
            if (idx < list.count())
                data = list.at(idx);
            else
            {
                data = QVariant();
                break;
            }
        }
        else
            data = data.toMap().value(pt);
    }

    p->data.clear();
    switch (static_cast<int>(data.type()))
    {
    case QVariant::List:
        p->data = data.toList();
        break;
    case QVariant::StringList:
    {
        QStringList list = data.toStringList();
        for (const QString &l: list)
            p->data << QVariantMap( {{"value", l}} );
    }
        break;
    case QVariant::Map:
    {
        QVariantMap map = data.toMap();
        QMapIterator<QString, QVariant> i(map);
        while (i.hasNext())
        {
            i.next();
            p->data << QVariantMap( {{"key", i.key()}, {"value", i.value()}} );
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
            p->data << QVariantMap( {{"key", i.key()}, {"value", i.value()}} );
        }
    }
        break;
    }

    Q_EMIT dataChanged();
}

AsemanQuickListModelSource::~AsemanQuickListModelSource()
{
    delete p;
}
