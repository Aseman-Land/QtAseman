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

#ifndef ASEMANQUICKITEMIMAGEGRABBER_H
#define ASEMANQUICKITEMIMAGEGRABBER_H

#include <QObject>
#include <QImage>
#include <QUrl>

#include "asemantools_global.h"

class QQuickItem;
class AsemanQuickItemImageGrabberPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanQuickItemImageGrabber : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(QImage image READ image NOTIFY imageChanged)
    Q_PROPERTY(QUrl defaultImage READ defaultImage WRITE setDefaultImage NOTIFY defaultImageChanged)

public:
    AsemanQuickItemImageGrabber(QObject *parent = 0);
    virtual ~AsemanQuickItemImageGrabber();

    void setItem(QQuickItem *item);
    QQuickItem *item() const;

    void setDefaultImage(const QUrl &url);
    QUrl defaultImage() const;

    QImage image() const;

public Q_SLOTS:
    void start();

Q_SIGNALS:
    void itemChanged();
    void imageChanged();
    void defaultImageChanged();

private Q_SLOTS:
    void ready();

private:
    AsemanQuickItemImageGrabberPrivate *p;
};

#endif // ASEMANQUICKITEMIMAGEGRABBER_H
