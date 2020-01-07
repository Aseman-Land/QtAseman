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

#ifndef ASEMANITEMGRABBER_H
#define ASEMANITEMGRABBER_H

#include <QObject>
#include <QQuickItem>

#include "asemantools_global.h"

class AsemanItemGrabberPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanItemGrabber : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    AsemanItemGrabber(QObject *parent = 0);
    virtual ~AsemanItemGrabber();

    void setItem(QQuickItem *item);
    QQuickItem *item() const;

    void setSuffix(const QString &suffix);
    QString suffix() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

public Q_SLOTS:
    void save(const QString &dest, const QSize &size);

Q_SIGNALS:
    void itemChanged();
    void suffixChanged();
    void fileNameChanged();
    void saved(const QString &dest);
    void failed();

private Q_SLOTS:
    void ready();

private:
    AsemanItemGrabberPrivate *p;
};

typedef AsemanItemGrabber QAsemanItemGrabber;

#endif // ASEMANITEMGRABBER_H
