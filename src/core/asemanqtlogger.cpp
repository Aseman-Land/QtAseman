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

#include "asemanqtlogger.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QFileInfo>
#include <QCoreApplication>
#include <QMutex>

QSet<AsemanQtLogger*> aseman_qt_logger_objs;
QtMessageHandler aseman_qt_logger_previousHandler = 0;

void asemanQtLoggerFnc(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    for(AsemanQtLogger *obj: aseman_qt_logger_objs)
        obj->logMsg(type,context,msg);
    aseman_qt_logger_previousHandler(type, context, msg);
}

class AsemanQtLoggerPrivate
{
public:
    QFile *file;
    QString path;
    QMutex file_mutex;
};

AsemanQtLogger::AsemanQtLogger(const QString &path, QObject *parent) :
    QObject(parent)
{
    p = new AsemanQtLoggerPrivate;
    p->path = path;
    p->file = 0;

    aseman_qt_logger_objs.insert(this);
}

void AsemanQtLogger::logMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString file = QString::fromUtf8(context.file);
    QByteArray localMsg = msg.toLocal8Bit();
    QString text = QStringLiteral(": (%2:%3, %4) %5 : %1\n").arg(QString::fromUtf8(localMsg.constData()))
            .arg(file.mid(file.lastIndexOf(QStringLiteral("/"))+1))
            .arg(context.line).arg(QString::fromUtf8(context.function)).arg(QTime::currentTime().toString());

    switch (static_cast<int>(type)) {
    case QtDebugMsg:
        text = "Debug" + text;
        p->file_mutex.lock();
        p->file->write(text.toUtf8());
        p->file->flush();
        p->file_mutex.unlock();
        break;
    case QtWarningMsg:
        text = "Warning" + text;
        p->file_mutex.lock();
        p->file->write(text.toUtf8());
        p->file->flush();
        p->file_mutex.unlock();
        break;
    case QtCriticalMsg:
        text = "Critical" + text;
        p->file_mutex.lock();
        p->file->write(text.toUtf8());
        p->file->flush();
        p->file_mutex.unlock();
        break;
    case QtFatalMsg:
        text = "Fatal" + text;
        p->file_mutex.lock();
        p->file->write(text.toUtf8());
        p->file->flush();
        p->file_mutex.unlock();
        abort();
    }
}

QString AsemanQtLogger::path() const
{
    return p->path;
}

void AsemanQtLogger::debug(const QVariant &var)
{
    qDebug() << var;
}

void AsemanQtLogger::start()
{
    if(p->file)
        return;

    p->file = new QFile(p->path);
    p->file->open(QFile::WriteOnly);

    if(aseman_qt_logger_previousHandler)
        return;

    aseman_qt_logger_previousHandler = qInstallMessageHandler(asemanQtLoggerFnc);
}

void AsemanQtLogger::app_closed()
{
}

AsemanQtLogger::~AsemanQtLogger()
{
    aseman_qt_logger_objs.remove(this);
    if( aseman_qt_logger_objs.isEmpty() )
        qInstallMessageHandler(0);

    delete p;
}
