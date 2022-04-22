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
/*!
    \class AsemanFileSystemModel
    \brief The AsemanFileSystemModel class provides a data model system to
    fetch and push file system data to the view.

    \reentrant
    \ingroup AsemanCore
 */

/*!
    \fn AsemanFileSystemModel::countChanged
    This signal emits when count of the model changed.
    \sa setCount
 */

/*!
    \fn AsemanFileSystemModel::showDirsChanged
    This signal emits when showDirs flag changed.
    \sa setShowDirs
 */

/*!
    \fn AsemanFileSystemModel::showDotAndDotDotChanged
    This signal emits when showDotAndDotDot flag changed.
    \sa setShowDotAndDotDot
 */

/*!
    \fn AsemanFileSystemModel::showDirsFirstChanged
    This signal emits when showDirsFirst flag changed.
    \sa setShowDirsFirst
 */

/*!
    \fn AsemanFileSystemModel::showFilesChanged
    This signal emits when showFiles flag changed.
    \sa setShowFiles
 */

/*!
    \fn AsemanFileSystemModel::showHiddenChanged
    This signal emits when showHidden flag changed.
    \sa setShowHidden
 */

/*!
    \fn AsemanFileSystemModel::nameFiltersChanged
    This signal emits when nameFilters changed.
    \sa setNameFilters
 */

/*!
    \fn AsemanFileSystemModel::folderChanged
    This signal emits when current folder changed.
    \sa setFolder
 */

/*!
    \fn AsemanFileSystemModel::parentFolderChanged
    This signal emits when parentFolder changed.
    \sa parentFolder
 */

/*!
    \fn AsemanFileSystemModel::sortFieldChanged
    This signal emits when sortField changed.
    \sa setSortField
 */

/*!
    \fn AsemanFileSystemModel::recursiveChanged
    This signal emits when recursive flag changed.
    \sa setRecursive
 */

/*!
    \fn AsemanFileSystemModel::limitChanged
    This signal emits when limit value changed.
    \sa setLimit
 */

#include "asemanfilesystemmodel.h"

#include <QFileSystemWatcher>
#include <QDir>
#include <QMimeData>
#include <QMimeDatabase>
#include <QMimeType>
#include <QDateTime>
#include <QFileInfo>
#include <QTimerEvent>
#include <QTimer>
#include <QDebug>
#include <QUrl>


class AsemanFileSystemModelPrivate
{
public:
    bool showDirs;
    bool showDotAndDotDot;
    bool showDirsFirst;
    bool showFiles;
    bool showHidden;
    bool recursive;
    QStringList nameFilters;
    QString folder;
    int sortField;
    qint32 limit;

    QList<QFileInfo> list;
    QMimeDatabase mdb;

    QFileSystemWatcher *watcher;
    QTimer *refresh_timer;
};

class SortUnitType
{
public:
    SortUnitType(): num(0){}
    QChar ch;
    quint64 num;
};

QList<SortUnitType> aseman_analize_file_name(const QString &fileName)
{
    QList<SortUnitType> res;
    for(int i=0; i<fileName.length(); i++)
    {
        const QChar &ch = fileName[i];
        if(ch.isNumber())
        {
            int num = QString(ch).toInt();
            if(res.isEmpty() || !res.last().ch.isNull() )
                res << SortUnitType();

            SortUnitType & resUnit = res[res.length()-1];
            resUnit.num = resUnit.num*10 + num;
        }
        else
        {
            SortUnitType unit;
            unit.ch = ch;
            res << unit;
        }
    }

    return res;
}

AsemanFileSystemModelPrivate *fileListSort_private_data = Q_NULLPTR;
bool aseman_fileListSort(const QFileInfo &f1, const QFileInfo &f2)
{
    if(fileListSort_private_data->sortField == AsemanFileSystemModel::Size)
        return f1.size() < f2.size();
    if(fileListSort_private_data->sortField == AsemanFileSystemModel::Date)
        return f1.lastModified() > f2.lastModified();

    if(fileListSort_private_data->showDirsFirst)
    {
        if(f1.isDir() && !f2.isDir())
            return true;
        if(!f1.isDir() && f2.isDir())
            return false;
    }

    const QString & s1 = f1.fileName();
    const QString & s2 = f2.fileName();

    const QList<SortUnitType> &ul1 = aseman_analize_file_name(s1);
    const QList<SortUnitType> &ul2 = aseman_analize_file_name(s2);

    for(int i=0; i<ul1.length() && i<ul2.length(); i++)
    {
        const SortUnitType &u1 = ul1.at(i);
        const SortUnitType &u2 = ul2.at(i);

        if(u1.ch.isNull() && !u2.ch.isNull())
            return true;
        if(!u1.ch.isNull() && u2.ch.isNull())
            return false;
        if(!u1.ch.isNull() && !u2.ch.isNull())
        {
            if(u1.ch < u2.ch)
                return true;
            if(u1.ch > u2.ch)
                return false;
        }
        if(u1.ch.isNull() && u2.ch.isNull())
        {
            if(u1.num < u2.num)
                return true;
            if(u1.num > u2.num)
                return false;
        }
    }

    return ul1.length() < ul2.length();
}



AsemanFileSystemModel::AsemanFileSystemModel(QObject *parent) :
    AsemanAbstractListModel(parent)
{
    p = new AsemanFileSystemModelPrivate;
    p->showDirs = true;
    p->showDotAndDotDot = false;
    p->showDirsFirst = true;
    p->showFiles = true;
    p->showHidden = false;
    p->sortField = AsemanFileSystemModel::Name;
    p->refresh_timer = Q_NULLPTR;
    p->recursive = false;
    p->limit = 0;

    p->watcher = new QFileSystemWatcher(this);

    p->refresh_timer = new QTimer(this);
    p->refresh_timer->setInterval(10);

    connect(p->watcher, &QFileSystemWatcher::directoryChanged, this, &AsemanFileSystemModel::refresh);
    connect(p->watcher, &QFileSystemWatcher::fileChanged, this, &AsemanFileSystemModel::refresh);

    connect(p->refresh_timer, &QTimer::timeout, this, &AsemanFileSystemModel::reinit_buffer);
}


/*!
    Sets model showDirs flag to show directories or not.
    \param stt showDirs state
    \sa showDirs
 */
void AsemanFileSystemModel::setShowDirs(bool stt)
{
    if(p->showDirs == stt)
        return;

    p->showDirs = stt;
    Q_EMIT showDirsChanged();

    refresh();
}

/*!
    Returns showDirs flag state
    \sa setShowDirs
 */
bool AsemanFileSystemModel::showDirs() const
{
    return p->showDirs;
}


/*!
    Sets model showDotAndDotDot flag to show "." and ".." folders or not.
    \param stt "." and ".." state
    \sa showDotAndDotDot
 */
void AsemanFileSystemModel::setShowDotAndDotDot(bool stt)
{
    if(p->showDotAndDotDot == stt)
        return;

    p->showDotAndDotDot = stt;
    Q_EMIT showDotAndDotDotChanged();

    refresh();
}

/*!
    Returns showDotAndDotDot flag state
    \sa setShowDotAndDotDot
 */
bool AsemanFileSystemModel::showDotAndDotDot() const
{
    return p->showDotAndDotDot;
}


/*!
    Sets model showDirsFirst flag to show directories on the top of the list or not
    \param stt showDirsFirst state
    \sa showDirsFirst
 */
void AsemanFileSystemModel::setShowDirsFirst(bool stt)
{
    if(p->showDirsFirst == stt)
        return;

    p->showDirsFirst = stt;
    Q_EMIT showDirsFirstChanged();

    refresh();
}

/*!
    Returns showDirsFirst flag state
    \sa setShowDirsFirst
 */
bool AsemanFileSystemModel::showDirsFirst() const
{
    return p->showDirsFirst;
}


/*!
    Sets model showFiles flag to show files or not.
    \param stt showFiles state
    \sa showFiles
 */
void AsemanFileSystemModel::setShowFiles(bool stt)
{
    if(p->showFiles == stt)
        return;

    p->showFiles = stt;
    Q_EMIT showFilesChanged();

    refresh();
}

/*!
    Returns showFiles flag state
    \sa setShowFiles
 */
bool AsemanFileSystemModel::showFiles() const
{
    return p->showFiles;
}


/*!
    Sets model showHidden flag to show hidden or not.
    \param stt showHidden state
    \sa showHidden
 */
void AsemanFileSystemModel::setShowHidden(bool stt)
{
    if(p->showHidden == stt)
        return;

    p->showHidden = stt;
    Q_EMIT showHiddenChanged();

    refresh();
}

/*!
    Returns showHidden flag state
    \sa setShowHidden
 */
bool AsemanFileSystemModel::showHidden() const
{
    return p->showHidden;
}


/*!
    Sets nameFilters list to filter items in the model.
    \param list nameFilters state
    \sa nameFilters
 */
void AsemanFileSystemModel::setNameFilters(const QStringList &list)
{
    if(p->nameFilters == list)
        return;

    p->nameFilters = list;
    Q_EMIT nameFiltersChanged();

    refresh();
}

/*!
    Returns all nameFilters values
    \sa setNameFilters
 */
QStringList AsemanFileSystemModel::nameFilters() const
{
    return p->nameFilters;
}


/*!
    Sets current folder that model read data from it.
    \param url folder path
    \sa folder
 */
void AsemanFileSystemModel::setFolder(const QString &url)
{
    if(p->folder == url)
        return;

    if(!p->folder.isEmpty())
        p->watcher->removePath(p->folder);

    p->folder = url;
    if(!p->folder.isEmpty())
        p->watcher->addPath(p->folder);

    Q_EMIT folderChanged();

    refresh();
}

/*!
    Returns current folder string.
    \sa setFolder
 */
QString AsemanFileSystemModel::folder() const
{
    return p->folder;
}


/*!
    Sets sort SortFlag, model sort using it.
    \param field sort flag
    \sa sortField
 */
void AsemanFileSystemModel::setSortField(int field)
{
    if(p->sortField == field)
        return;

    p->sortField = field;
    Q_EMIT sortFieldChanged();

    refresh();
}

/*!
    Returns current sortField value.
    \sa setSortField
 */
int AsemanFileSystemModel::sortField() const
{
    return p->sortField;
}


/*!
    Recursive lookup files and folders. If it's set to true, model will show
    all files of the folder, even in the sub-folders.
    \param recursive recursive flag
    \sa recursive
 */
void AsemanFileSystemModel::setRecursive(bool recursive)
{
    if(p->recursive == recursive)
        return;

    p->recursive = recursive;
    Q_EMIT recursiveChanged();

    refresh();
}

/*!
    Returns recursive flag state
    \sa setRecursive
 */
bool AsemanFileSystemModel::recursive() const
{
    return p->recursive;
}


/*!
    Sets limit of the files and folder to load in the model. It's useful
    when you want to explore a folder with million of files and folders.
    \param limit limits of the model
    \sa limit
 */
void AsemanFileSystemModel::setLimit(qint32 limit)
{
    if(p->limit == limit)
        return;

    p->limit = limit;
    Q_EMIT limitChanged();
}

/*!
    Returns limit value
    \sa setRecursive
 */
qint32 AsemanFileSystemModel::limit() const
{
    return p->limit;
}

/*!
    Returns parent path of the current folder. It's useful when you
    want to add "up" action to your view.
    \sa folder
 */
QString AsemanFileSystemModel::parentFolder() const
{
    return QFileInfo(p->folder).dir().absolutePath();
}

const QFileInfo &AsemanFileSystemModel::id(const QModelIndex &index) const
{
    return p->list.at( index.row() );
}

int AsemanFileSystemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return count();
}

QVariant AsemanFileSystemModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    const QFileInfo &info = id(index);
    switch(role)
    {
    case FilePath:
        result = info.filePath();
        break;

    case FileUrl:
        result = QUrl::fromLocalFile(info.filePath());
        break;

    case FileName:
        result = info.fileName();
        break;

    case FileMime:
        result = p->mdb.mimeTypeForFile(info.filePath()).name();
        break;

    case FileSize:
        result = info.size();
        break;

    case FileSuffix:
        result = info.suffix();
        break;

    case FileBaseName:
        result = info.completeBaseName();
        break;

    case FileIsDir:
        result = info.isDir();
        break;

    case FileModifiedDate:
        result = info.lastModified();
        break;

    case FileCreatedDate:
        result = info.birthTime();
        break;
    }

    return result;
}

QHash<qint32, QByteArray> AsemanFileSystemModel::roleNames() const
{
    static QHash<qint32, QByteArray> *res = 0;
    if( res )
        return *res;

    res = new QHash<qint32, QByteArray>();
    res->insert( FilePath, "filePath");
    res->insert( FileUrl , "fileUrl");
    res->insert( FileName, "fileName");
    res->insert( FileMime, "fileMime");
    res->insert( FileSize, "fileSize");
    res->insert( FileSuffix, "fileSuffix");
    res->insert( FileBaseName, "fileBaseName");
    res->insert( FileIsDir, "fileIsDir");
    res->insert( FileModifiedDate, "fileModifiedDate");
    res->insert( FileCreatedDate, "fileCreatedDate");

    return *res;
}

/*!
    Returns count of items exists in the model.
    \returns count of items exists in the model.
    \sa indexOf
 */
int AsemanFileSystemModel::count() const
{
    return p->list.count();
}


/*!
    Clean and reload all data of the model
    \sa count
    \sa setFolder
 */
void AsemanFileSystemModel::refresh()
{
    p->refresh_timer->stop();
    p->refresh_timer->start();
}

void AsemanFileSystemModel::reinit_buffer()
{
    p->refresh_timer->stop();

    int filter = 0;
    if(p->showDirs)
        filter = filter | QDir::Dirs;
    if(!p->showDotAndDotDot)
        filter = filter | QDir::NoDotAndDotDot;
    if(p->showFiles)
        filter = filter | QDir::Files;
    if(p->showHidden)
        filter = filter | QDir::Hidden;

    qint32 limit = p->limit? p->limit : INT_MAX;
    QList<QFileInfo> res = ls(p->folder, filter, p->recursive, limit);

    if(!p->nameFilters.isEmpty())
        for(int i=0; i<res.count(); i++)
        {
            const QFileInfo &inf = res.at(i);

            QStringList suffixes;
            if(!inf.suffix().isEmpty())
                suffixes << inf.suffix();
            else
                suffixes = p->mdb.mimeTypeForFile(inf.filePath()).suffixes();

            bool founded = inf.isDir();
            for(const QString &sfx: suffixes)
                if(p->nameFilters.contains("*."+sfx, Qt::CaseInsensitive))
                {
                    founded = true;
                    break;
                }

            if(!founded)
            {
                res.removeAt(i);
                i--;
            }
        }

    fileListSort_private_data = p;
    std::stable_sort(res.begin(), res.end(), aseman_fileListSort);

    changed(res);
}

QList<QFileInfo> AsemanFileSystemModel::ls(const QString &path, qint32 filter, bool recursive, qint32 &limit)
{
    QList<QFileInfo> res;

    QDir::SortFlags sort = QDir::Name;
    switch(p->sortField)
    {
    case Size:
        sort = QDir::Size;
        break;
    case Date:
        sort = (QDir::Time | QDir::Reversed);
        break;
    }

    QStringList list;
    if(filter && !path.isEmpty())
        list = QDir(path).entryList(static_cast<QDir::Filter>(filter) | QDir::Dirs, sort);

    for(const QString &fileName: list)
    {
        QFileInfo info(path + "/" + fileName);
        if(!info.isDir() || (static_cast<QDir::Filter>(filter) & QDir::Dirs))
        {
            res << info;
            limit--;
        }
        if(limit < 0)
            return res;

        if(info.isDir() && recursive)
            res << ls(path + "/" + fileName, filter, recursive, limit);
    }

    return res;
}

void AsemanFileSystemModel::changed(const QList<QFileInfo> &list)
{
    bool count_changed = (list.count()==p->list.count());

    for( int i=0 ; i<p->list.count() ; i++ )
    {
        const QFileInfo &file = p->list.at(i);
        if( list.contains(file) )
            continue;

        beginRemoveRows(QModelIndex(), i, i);
        p->list.removeAt(i);
        i--;
        endRemoveRows();
    }

    QList<QFileInfo> temp_list = list;
    for( int i=0 ; i<temp_list.count() ; i++ )
    {
        const QFileInfo &file = temp_list.at(i);
        if( p->list.contains(file) )
            continue;

        temp_list.removeAt(i);
        i--;
    }
    while( p->list != temp_list )
        for( int i=0 ; i<p->list.count() ; i++ )
        {
            const QFileInfo &file = p->list.at(i);
            int nw = temp_list.indexOf(file);
            if( i == nw )
                continue;

            beginMoveRows( QModelIndex(), i, i, QModelIndex(), nw>i?nw+1:nw );
            p->list.move( i, nw );
            endMoveRows();
        }

    for( int i=0 ; i<list.count() ; i++ )
    {
        const QFileInfo &file = list.at(i);
        if( p->list.contains(file) )
            continue;

        beginInsertRows(QModelIndex(), i, i );
        p->list.insert( i, file );
        endInsertRows();
    }

    if(count_changed)
        Q_EMIT countChanged();

    Q_EMIT listChanged();
}

AsemanFileSystemModel::~AsemanFileSystemModel()
{
    delete p;
}
