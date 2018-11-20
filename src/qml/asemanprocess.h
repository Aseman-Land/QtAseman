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

#ifndef ASEMANPROCESS_H
#define ASEMANPROCESS_H

#include <QObject>
#include <QStringList>

#include "asemantools_global.h"

class LIBQTASEMAN_QML_EXPORT AsemanProcess : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList arguments READ arguments WRITE setArguments NOTIFY argumentsChanged)
    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

    class Private;

public:
    AsemanProcess(QObject *parent = Q_NULLPTR);
    virtual ~AsemanProcess();

    void setCommand(const QString &command);
    QString command() const;

    void setArguments(const QStringList &arguments);
    QStringList arguments() const;

    bool running() const;

Q_SIGNALS:
    void commandChanged();
    void argumentsChanged();
    void runningChanged();

public Q_SLOTS:
    void start();
    void terminate();

private:
    Private *p;
};

#endif // ASEMANPROCESS_H
