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

#ifndef ASEMANAUTOSTARTMANAGER_H
#define ASEMANAUTOSTARTMANAGER_H

#include <QObject>
#include <QUrl>

#include "asemancore_global.h"

class AsemanAutoStartManagerPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanAutoStartManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
    Q_PROPERTY(QString source  READ source  WRITE setSource  NOTIFY sourceChanged )
    Q_PROPERTY(QString name    READ name    WRITE setName    NOTIFY nameChanged   )
    Q_PROPERTY(QString type    READ type    WRITE setType    NOTIFY typeChanged   )
    Q_PROPERTY(bool    active  READ active  WRITE setActive  NOTIFY activeChanged )

public:
    AsemanAutoStartManager(QObject *parent = Q_NULLPTR);
    virtual ~AsemanAutoStartManager();

    void setCommand(const QString &cmd);
    QString command() const;

    void setSource(const QString &fileName);
    QString source() const;

    void setComment(const QString &txt);
    QString comment() const;

    void setName(const QString &name);
    QString name() const;

    void setType(const QString &t);
    QString type() const;

    void setActive(bool active);
    bool active() const;

public Q_SLOTS:
    void refresh();
    void save();

Q_SIGNALS:
    void commandChanged();
    void sourceChanged();
    void commentChanged();
    void nameChanged();
    void typeChanged();
    void activeChanged();

private:
    AsemanAutoStartManagerPrivate *p;
};

typedef AsemanAutoStartManager QAsemanAutoStartManager;

#endif // ASEMANAUTOSTARTMANAGER_H
