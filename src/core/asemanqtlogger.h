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

#ifndef ASEMANQTLOGGER_H
#define ASEMANQTLOGGER_H

#include <QObject>

#include "asemancore_global.h"

class AsemanQtLoggerPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanQtLogger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path NOTIFY pathChanged)

public:
    AsemanQtLogger(const QString & path, QObject *parent = Q_NULLPTR);
    virtual ~AsemanQtLogger();

    virtual void logMsg(QtMsgType type , const QMessageLogContext &context, const QString &msg);
    QString path() const;

Q_SIGNALS:
    void pathChanged();

public Q_SLOTS:
    void debug( const QVariant & var );
    void start();

private Q_SLOTS:
    void app_closed();

private:
    AsemanQtLoggerPrivate *p;
};

typedef AsemanQtLogger QAsemanQtLogger;

#endif // ASEMANQTLOGGER_H
