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

#ifndef ASEMANMIMEDATA_H
#define ASEMANMIMEDATA_H

#include <QObject>
#include <QUrl>
#include <QVariantMap>

#include "asemangui_global.h"

class AsemanMimeDataPrivate;
class LIBQTASEMAN_GUI_EXPORT AsemanMimeData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString html READ html WRITE setHtml NOTIFY htmlChanged)
    Q_PROPERTY(QList<QUrl> urls READ urls WRITE setUrls NOTIFY urlsChanged)
    Q_PROPERTY(QVariantMap dataMap READ dataMap WRITE setDataMap NOTIFY dataMapChanged)
    Q_PROPERTY(QStringList formats READ formats NOTIFY dataMapChanged)

public:
    AsemanMimeData(QObject *parent = Q_NULLPTR);
    virtual ~AsemanMimeData();

    void setText(const QString &txt);
    QString text() const;

    void setHtml(const QString &html);
    QString html() const;

    void setUrls(const QList<QUrl> &urls);
    QList<QUrl> urls() const;

    void setDataMap(const QVariantMap &map);
    QVariantMap dataMap() const;
    QStringList formats() const;

public Q_SLOTS:
    void fetchClipboard();
    QString getDataAsString(const QString &type);

Q_SIGNALS:
    void textChanged();
    void htmlChanged();
    void urlsChanged();
    void dataMapChanged();

private:
    AsemanMimeDataPrivate *p;
};

typedef AsemanMimeData QAsemanMimeData;

Q_DECLARE_METATYPE(AsemanMimeData*)

#endif // ASEMANMIMEDATA_H
