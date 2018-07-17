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

#ifndef ASEMANTASKBARBUTTON_H
#define ASEMANTASKBARBUTTON_H

#include <QObject>
#include <QVariant>

#include "asemanwidgets_global.h"

class QWindow;
class AsemanTaskbarButtonPrivate;
class LIBQTASEMAN_WIDGETS_EXPORT AsemanTaskbarButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      badgeNumber READ badgeNumber WRITE setBadgeNumber NOTIFY badgeNumberChanged)
    Q_PROPERTY(qreal    progress    READ progress    WRITE setProgress    NOTIFY progressChanged   )
    Q_PROPERTY(QString  launcher    READ launcher    WRITE setLauncher    NOTIFY launcherChanged   )
    Q_PROPERTY(QWindow* window      READ window      WRITE setWindow      NOTIFY windowChanged     )

public:
    AsemanTaskbarButton(QObject *parent = 0);
    virtual ~AsemanTaskbarButton();

    void setBadgeNumber(int num);
    int badgeNumber() const;

    void setProgress(qreal progress);
    qreal progress() const;

    void setLauncher(const QString &launcher);
    QString launcher() const;

    void setWindow(QWindow *win);
    QWindow *window() const;

public Q_SLOTS:
    void userAttention();

Q_SIGNALS:
    void badgeNumberChanged();
    void progressChanged();
    void launcherChanged();
    void windowChanged();

private:
    AsemanTaskbarButtonPrivate *p;
};

#endif // ASEMANTASKBARBUTTON_H
