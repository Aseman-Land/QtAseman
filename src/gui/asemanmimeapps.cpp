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

#define GLOBAL_APPS_PATH QStringLiteral("/usr/share/applications")
#define LOCAL_APPS_PATH QString(QDir::homePath() + QStringLiteral("/.local/share/applications"))

#include "asemanmimeapps.h"

#include <QDir>
#include <QHash>
#include <QSettings>
#ifndef Q_OS_IOS
#include <QProcess>
#endif
#include <QMimeDatabase>
#include <QMimeType>
#include <QFile>
#include <QRegExp>
#include <QDebug>
#include <QRegularExpression>

class AsemanMimeAppsItem
{
public:
    QString name;
    QString icon;
    QString genericName;
    QString comment;
    QString path;
    QString command;
    QStringList mimes;
};

QMultiHash<QString,QString> mime_apps_apps;
QHash<QString,AsemanMimeAppsItem> mime_apps_items;

QStringList filesOf( const QString & path )
{
    QStringList res;

    const QStringList & dirs = QDir(path).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for( const QString &d: dirs)
        res << filesOf( path + "/" + d );

    const QStringList & files = QDir(path).entryList(QStringList()<<QStringLiteral("*.desktop"),QDir::Files);
    for(const QString &f: files)
        res << path + QStringLiteral("/") + f;

    return res;
}

QHash<QString,QString> readConfFile( const QString & file )
{
    QHash<QString,QString> res;

    QFile f(file);
    if( !f.open(QFile::ReadOnly) )
        return res;

    const QString & data = QString::fromUtf8(f.readAll());
    f.close();

    QRegExp mexr(QStringLiteral("\\[(.*)\\]\\s((?:\\s|.)*)\\s(?:\\[|$)"));
    mexr.setMinimal(true);

    int mpos = 0;
    while ((mpos = mexr.indexIn(data, mpos)) != -1)
    {
        const QString & section    = mexr.cap(1);
        const QString & properties = mexr.cap(2);

        QRegExp pexr(QStringLiteral("(?:\\r|\\n|^)(.*)\\=(.*)(?:\\r|\\n)"));
        pexr.setMinimal(true);

        int ppos = 0;
        while ((ppos = pexr.indexIn(properties, ppos)) != -1)
        {
            const QString & key   = pexr.cap(1);
            const QString & value = pexr.cap(2);

            res[ section + "/" + key ] = value;

            ppos += pexr.matchedLength()-1;
        }

        mpos += mexr.matchedLength()-1;
    }

    return res;
}

void init_mimeApps()
{
    if( !mime_apps_items.isEmpty() )
        return;

    QStringList desktops;
    desktops << filesOf(GLOBAL_APPS_PATH);
    desktops << filesOf(LOCAL_APPS_PATH);

    for(const QString &d: desktops)
    {
        const QHash<QString,QString> & conf = readConfFile(d);

        AsemanMimeAppsItem item;
        item.name        = conf.value(QStringLiteral("Desktop Entry/Name"));
        item.icon        = conf.value(QStringLiteral("Desktop Entry/Icon"));
        item.genericName = conf.value(QStringLiteral("Desktop Entry/GenericName"));
        item.comment     = conf.value(QStringLiteral("Desktop Entry/Comment"));
        item.path        = conf.value(QStringLiteral("Desktop Entry/Path"));
        item.command     = conf.value(QStringLiteral("Desktop Entry/Exec"));
        item.mimes       = conf.value(QStringLiteral("Desktop Entry/MimeType")).split(QRegularExpression(QStringLiteral("(\\;|\\:)")),Qt::SkipEmptyParts);

        for(const QString &m: item.mimes)
        {
            mime_apps_apps.insert( m.toLower(), d );
            mime_apps_items.insert( d, item );
        }
    }
}

class AsemanMimeAppsPrivate
{
public:
    QMimeDatabase mdb;
};

AsemanMimeApps::AsemanMimeApps(QObject *parent) :
    QObject(parent)
{
    init_mimeApps();

    p = new AsemanMimeAppsPrivate;
}

QStringList AsemanMimeApps::appsOfMime(const QString &mime)
{
    return mime_apps_apps.values(mime.toLower());
}

QStringList AsemanMimeApps::appsOfFile(const QString &file)
{
    const QMimeType & type = p->mdb.mimeTypeForFile(file);
    return appsOfMime(type.name());
}

QString AsemanMimeApps::appName(const QString &app) const
{
    return mime_apps_items.value(app).name;
}

QString AsemanMimeApps::appIcon(const QString &app) const
{
    return mime_apps_items.value(app).icon;
}

QString AsemanMimeApps::appGenericName(const QString &app) const
{
    return mime_apps_items.value(app).genericName;
}

QString AsemanMimeApps::appComment(const QString &app) const
{
    return mime_apps_items.value(app).comment;
}

QString AsemanMimeApps::appPath(const QString &app) const
{
    return mime_apps_items.value(app).path;
}

QString AsemanMimeApps::appCommand(const QString &app) const
{
    return mime_apps_items.value(app).command;
}

QStringList AsemanMimeApps::appMimes(const QString &app) const
{
    return mime_apps_items.value(app).mimes;
}

void AsemanMimeApps::openFiles(const QString &app, const QStringList &files)
{
    if( !mime_apps_items.contains(app) )
        return;

#ifdef Q_OS_IOS
    Q_UNUSED(files)
#else
    const AsemanMimeAppsItem & item = mime_apps_items.value(app);

    QString cmd;
    QStringList args;

    const QStringList & command_splits = item.command.split(QStringLiteral(" "),Qt::SkipEmptyParts);

    cmd = command_splits.first();
    args = command_splits.mid(1);

    if( args.contains(QStringLiteral("%u")) )
    {
        int index = args.indexOf(QStringLiteral("%u"));
        for(const QString &f: files)
        {
            QStringList targs = args;
            targs.replace(index,f);

            QProcess::startDetached( cmd, targs );
        }
    }
    else
    if( args.contains(QStringLiteral("%U")) )
    {
        int index = args.indexOf(QStringLiteral("%U"));
        QStringList targs = args;
        targs.removeAt(index);

        for(const QString &f: files)
            targs.insert(index,f);

        QProcess::startDetached( cmd, targs );
    }
    else
    if( args.contains(QStringLiteral("%f")) )
    {
        int index = args.indexOf(QStringLiteral("%f"));
        for(const QString &f: files)
        {
            QStringList targs = args;
            targs.replace(index,f);

            QProcess::startDetached( cmd, targs );
        }
    }
    else
    if( args.contains(QStringLiteral("%F")) )
    {
        int index = args.indexOf(QStringLiteral("%F"));
        QStringList targs = args;
        targs.removeAt(index);

        for(const QString &f: files)
            targs.insert(index,f);

        QProcess::startDetached( cmd, targs );
    }
    else
    {
        for(const QString &f: files)
        {
            QStringList targs = args;
            targs.append(f);

            QProcess::startDetached( cmd, targs );
        }
    }
#endif
}

AsemanMimeApps::~AsemanMimeApps()
{
    delete p;
}
