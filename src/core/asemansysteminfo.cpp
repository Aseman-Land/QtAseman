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

#define CPU_CORE_PATH "/sys/devices/system/cpu/"
#define CPU_FREQ_PATH "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq"

#include "asemansysteminfo.h"

#include <QFile>
#include <QStringList>
#include <QDir>

class AsemanSystemInfoPrivate
{
public:
    quint64 cpu_cores;
    quint64 cpu_freq;
};

AsemanSystemInfo::AsemanSystemInfo(QObject *parent) :
    QObject(parent)
{
    p = new AsemanSystemInfoPrivate;
    p->cpu_cores = 0;
    p->cpu_freq = 0;
}

quint64 AsemanSystemInfo::cpuCores()
{
    if( p->cpu_cores )
        return p->cpu_cores;

    p->cpu_cores = 0;

    const QStringList & dirs = QDir(QStringLiteral(CPU_CORE_PATH)).entryList(QDir::Dirs|QDir::NoDotAndDotDot);
    for(const QString & dir: dirs)
    {
        bool ok = false;
        const QString & left = dir.left(3);
        dir.mid(3).toInt(&ok);
        if( left == QStringLiteral("cpu") && ok )
            p->cpu_cores++;
    }

    return p->cpu_cores;
}

quint64 AsemanSystemInfo::cpuFreq()
{
    if( p->cpu_freq )
        return p->cpu_freq;
    if( !cpuCores() )
        return 0;

    QFile file(QStringLiteral(CPU_FREQ_PATH));
    if( !file.open(QFile::ReadOnly) )
        return 0;

    p->cpu_freq = QString::fromUtf8(file.readAll()).remove(QStringLiteral("\n")).toULongLong();
    return p->cpu_freq;
}

AsemanSystemInfo::~AsemanSystemInfo()
{
    delete p;
}
