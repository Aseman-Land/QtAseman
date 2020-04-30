/*
    Copyright (C) 2019 Aseman Team
    http://aseman.io

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemanquicklistmodel.h"
#include "asemanquicklistmodelsource.h"

#include <QTimer>
#include <QDebug>

class AsemanQuickListModel::Private
{
public:
    QList<QObject*> items;
    QList<AsemanQuickListModelSource*> sources;
    QList<AsemanAbstractQuickListModelHint*> hints;

    QList<QVariantMap> backupList;
    QString sortField;
    bool sortDescending;
};

AsemanQuickListModel::AsemanQuickListModel(QObject *parent) :
    AsemanListModel(parent)
{
    p = new Private;
    p->sortDescending = false;

    QTimer *sourceChangeTimer = new QTimer(this);
    sourceChangeTimer->setInterval(100);
    sourceChangeTimer->setSingleShot(true);

    connect(this, &AsemanQuickListModel::itemsChanged, sourceChangeTimer, [sourceChangeTimer](){
        sourceChangeTimer->stop();
        sourceChangeTimer->start();
    });
    connect(sourceChangeTimer, &QTimer::timeout, this, &AsemanQuickListModel::reloadItems);
}

QQmlListProperty<QObject> AsemanQuickListModel::items()
{
    return QQmlListProperty<QObject>(this, &p->items, QQmlListProperty<QObject>::AppendFunction(append),
                                                      QQmlListProperty<QObject>::CountFunction(count),
                                                      QQmlListProperty<QObject>::AtFunction(at),
                                                      QQmlListProperty<QObject>::ClearFunction(clear) );
}

QList<QObject *> AsemanQuickListModel::itemsList() const
{
    return p->items;
}

void AsemanQuickListModel::setSortField(const QString &sortField)
{
    if (p->sortField == sortField)
        return;

    p->sortField = sortField;
    Q_EMIT sortFieldChanged();
}

QString AsemanQuickListModel::sortField() const
{
    return p->sortField;
}

void AsemanQuickListModel::setSortDescending(bool sortDescending)
{
    if (p->sortDescending == sortDescending)
        return;

    p->sortDescending = sortDescending;
    Q_EMIT sortDescendingChanged();
}

bool AsemanQuickListModel::sortDescending() const
{
    return p->sortDescending;
}

void AsemanQuickListModel::reload()
{
    changed(p->backupList);
}

void AsemanQuickListModel::append(QQmlListProperty<QObject> *p, QObject *v)
{
    AsemanQuickListModel *aobj = static_cast<AsemanQuickListModel*>(p->object);
    aobj->p->items.append(v);
    Q_EMIT aobj->itemsChanged();
}

int AsemanQuickListModel::count(QQmlListProperty<QObject> *p)
{
    AsemanQuickListModel *aobj = static_cast<AsemanQuickListModel*>(p->object);
    return aobj->p->items.count();
}

QObject *AsemanQuickListModel::at(QQmlListProperty<QObject> *p, int idx)
{
    AsemanQuickListModel *aobj = static_cast<AsemanQuickListModel*>(p->object);
    return aobj->p->items.at(idx);
}

void AsemanQuickListModel::clear(QQmlListProperty<QObject> *p)
{
    AsemanQuickListModel *aobj = static_cast<AsemanQuickListModel*>(p->object);
    aobj->p->items.clear();
    Q_EMIT aobj->itemsChanged();
}

void AsemanQuickListModel::reloadItems()
{
    while (p->sources.count())
        disconnect(p->sources.takeFirst(), &AsemanQuickListModelSource::dataChanged, this, &AsemanQuickListModel::refreshData);

    for (QObject *obj: p->items)
    {
        AsemanQuickListModelSource *source = qobject_cast<AsemanQuickListModelSource*>(obj);
        if (!source)
            continue;

        connect(source, &AsemanQuickListModelSource::dataChanged, this, &AsemanQuickListModel::refreshData);
        p->sources << source;
    }

    p->hints.clear();
    for (QObject *obj: p->items)
    {
        AsemanAbstractQuickListModelHint *hint = qobject_cast<AsemanAbstractQuickListModelHint*>(obj);
        if (!hint)
            continue;

        p->hints << hint;
    }

    refreshData();
}

void AsemanQuickListModel::refreshData()
{
    if (p->sources.count())
    {
        QVariantList list;
        for (AsemanQuickListModelSource *src: p->sources)
            list << src->data();

        change(list);
    }
    else
    if (p->hints.count())
        changed(p->backupList);
}

void AsemanQuickListModel::changed(const QList<QVariantMap> &l)
{
    p->backupList = l;
    QList<QVariantMap> list = l;

    QList<AsemanAbstractQuickListModelHint*> hints;
    for (QObject *obj: p->items)
    {
        AsemanAbstractQuickListModelHint *hint = qobject_cast<AsemanAbstractQuickListModelHint*>(obj);
        if (hint)
            hints << hint;
    }

    for (qint32 i=0; i<list.count(); i++)
    {
        QVariantMap &l = list[i];
        for (AsemanAbstractQuickListModelHint *h: hints)
            l = h->analyze(l);
    }

    if (p->sortField.count())
    {
        QMap<QString, QVariantMap> sortMapStr;
        QMap<qint32, QVariantMap> sortMapInt;
        for (const QVariantMap &l: list)
        {
            QVariant val = AsemanAbstractQuickListModelHint::getPathValue(l, p->sortField);
            if (val.type() == QVariant::Int || (val.canConvert(QVariant::Int) && val.convert(QVariant::Int)))
                sortMapInt.insertMulti(val.toInt(), l);
            else
                sortMapStr.insertMulti(val.toString(), l);
        }

        list.clear();
        list << sortMapInt.values();
        list << sortMapStr.values();
    }

    AsemanListModel::changed(list);
}

AsemanQuickListModel::~AsemanQuickListModel()
{
    delete p;
}
