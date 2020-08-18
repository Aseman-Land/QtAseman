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

#include "asemanprocess.h"

#include <QPointer>
#if QT_CONFIG(processenvironment)
#   include <QProcess>
#endif

class AsemanProcess::Private
{
public:
    QString command;
    QStringList arguments;
#if QT_CONFIG(processenvironment)
    QPointer<QProcess> process;
#endif
};

AsemanProcess::AsemanProcess(QObject *parent) :
    QObject(parent)
{
    p = new Private;
}

void AsemanProcess::setCommand(const QString &command)
{
    if(p->command == command)
        return;

    p->command = command;
    Q_EMIT commandChanged();
}

QString AsemanProcess::command() const
{
    return p->command;
}

void AsemanProcess::setArguments(const QStringList &arguments)
{
    if(p->arguments == arguments)
        return;

    p->arguments = arguments;
    Q_EMIT argumentsChanged();
}

void AsemanProcess::start()
{
#if QT_CONFIG(processenvironment)
    if(p->process)
        p->process->terminate();

    QProcess *process = new QProcess(this);
    process->setReadChannelMode(QProcess::ForwardedChannels);

    connect(process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), this, [process](int){
        process->deleteLater();
    });
    connect(process, &QProcess::destroyed, this, [this, process](){
        if(!p->process || p->process == process)
            Q_EMIT runningChanged();
    });
    connect(process, &QProcess::readyReadStandardOutput, this, [this, process](){
        Q_EMIT standardOutput(QString::fromUtf8(process->readAllStandardOutput()));
    });
    connect(process, &QProcess::readAllStandardError, this, [this, process](){
        Q_EMIT standardOutput(QString::fromUtf8(process->readAllStandardError()));
    });

    p->process = process;
    p->process->start(p->command, p->arguments);

    Q_EMIT runningChanged();
#endif
}

void AsemanProcess::terminate()
{
#if QT_CONFIG(processenvironment)
    if(!p->process)
        return;

    p->process->terminate();
    Q_EMIT runningChanged();
#endif
}

QStringList AsemanProcess::arguments() const
{
    return p->arguments;
}

bool AsemanProcess::running() const
{
#if QT_CONFIG(processenvironment)
    return p->process;
#else
    return false;
#endif
}

AsemanProcess::~AsemanProcess()
{
#if QT_CONFIG(processenvironment)
    delete p;
#endif
}
