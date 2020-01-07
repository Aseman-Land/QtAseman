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

#ifndef ASEMANNATIVENOTIFICATIONITEM_H
#define ASEMANNATIVENOTIFICATIONITEM_H

#include <QWidget>
#include <QStringList>

#include "asemanwidgets_global.h"

class AsemanNativeNotificationItemPrivate;
class LIBQTASEMAN_WIDGETS_EXPORT AsemanNativeNotificationItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    AsemanNativeNotificationItem(QWidget *parent = 0);
    virtual ~AsemanNativeNotificationItem();

    void setColor(const QColor &color);
    QColor color() const;

    void setActions(const QStringList & actions);
    void setTitle(const QString &title);
    void setBody(const QString &body);
    void setIcon(const QString &icon);
    void setTimeOut(int timeOut);

Q_SIGNALS:
    void actionTriggered(const QString & act);
    void colorChanged();

protected:
    void resizeEvent(QResizeEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private Q_SLOTS:
    void refreshSize();
    void setRaised();
    void buttonClicked();

private:
    AsemanNativeNotificationItemPrivate *p;
};

typedef AsemanNativeNotificationItem QAsemanNativeNotificationItem;

#endif // ASEMANNATIVENOTIFICATIONITEM_H
