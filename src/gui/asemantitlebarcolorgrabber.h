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

#ifndef ASEMANTITLEBARCOLORGRABBER_H
#define ASEMANTITLEBARCOLORGRABBER_H

#include <QObject>
#include <QWindow>

#include "asemangui_global.h"

class AsemanTitleBarColorGrabberPrivate;
class LIBQTASEMAN_GUI_EXPORT AsemanTitleBarColorGrabber : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ window WRITE setWindow NOTIFY windowChanged)
    Q_PROPERTY(bool autoRefresh READ autoRefresh WRITE setAutoRefresh NOTIFY autoRefreshChanged)
    Q_PROPERTY(QColor defaultColor READ defaultColor WRITE setDefaultColor NOTIFY defaultColorChanged)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    AsemanTitleBarColorGrabber(QObject *parent = 0);
    virtual ~AsemanTitleBarColorGrabber();

    void setWindow(QWindow *win);
    QWindow *window() const;

    void setAutoRefresh(bool stt);
    bool autoRefresh() const;

    void setDefaultColor(const QColor &color);
    QColor defaultColor() const;

    QColor color() const;

public Q_SLOTS:
    void refresh();

Q_SIGNALS:
    void windowChanged();
    void colorChanged();
    void autoRefreshChanged();
    void defaultColorChanged();

private Q_SLOTS:
    void activeChanged();

private:
    AsemanTitleBarColorGrabberPrivate *p;
};

typedef AsemanTitleBarColorGrabber QAsemanTitleBarColorGrabber;

#endif // ASEMANTITLEBARCOLORGRABBER_H
