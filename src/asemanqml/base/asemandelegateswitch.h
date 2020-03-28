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

#ifndef ASEMANDELEGATESWITCH_H
#define ASEMANDELEGATESWITCH_H

#include <QObject>
#include <QQuickItem>
#include <QQmlComponent>

class AsemanDelegateSwitch : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QQmlComponent> components READ components NOTIFY componentsChanged)
    Q_PROPERTY(qint32 current READ current WRITE setCurrent NOTIFY currentChanged)
    Q_PROPERTY(QQuickItem* item READ item NOTIFY itemChanged)
    Q_CLASSINFO("DefaultProperty", "components")

    class Private;

public:
    AsemanDelegateSwitch(QQuickItem *parent = Q_NULLPTR);
    virtual ~AsemanDelegateSwitch();

    QQmlListProperty<QQmlComponent> components();
    QList<QQmlComponent*> componentsList() const;

    void setCurrent(qint32 current);
    qint32 current() const;

    QQuickItem *item() const;

Q_SIGNALS:
    void componentsChanged();
    void currentChanged();
    void itemChanged();

private:
    static void append(QQmlListProperty<QQmlComponent> *p, QQmlComponent *v);
    static int count(QQmlListProperty<QQmlComponent> *p);
    static QQmlComponent *at(QQmlListProperty<QQmlComponent> *p, int idx);
    static void clear(QQmlListProperty<QQmlComponent> *p);

    void refresh();
    void refreshWidth();
    void refreshHeight();

private:
    Private *p;
};

#endif // ASEMANDELEGATESWITCH_H
