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

#include "asemanautostartmanager.h"

#if defined(Q_OS_MAC) && defined(OSX_CORE_SERVICES_AVAILABLE)
#include <CoreServices/CoreServices.h>
#endif

#include <QFile>
#include <QDir>
#include <QSettings>

class AsemanAutoStartManagerPrivate
{
public:
    QString type;
    bool active;
    QString name;
    QString command;
    QString comment;

    QString source;
};

AsemanAutoStartManager::AsemanAutoStartManager(QObject *parent) :
    QObject(parent)
{
    p = new AsemanAutoStartManagerPrivate;
    p->type = QStringLiteral("Application");
    p->active = true;
}

void AsemanAutoStartManager::setCommand(const QString &cmd)
{
    if(p->command == cmd)
        return;

    p->command = cmd;
    Q_EMIT commandChanged();

    save();
}

QString AsemanAutoStartManager::command() const
{
    return p->command;
}

void AsemanAutoStartManager::setSource(const QString &fileName)
{
    if(p->source == fileName)
        return;

    p->source = fileName;
    Q_EMIT sourceChanged();

    refresh();
}

QString AsemanAutoStartManager::source() const
{
    return p->source;
}

void AsemanAutoStartManager::setComment(const QString &txt)
{
    if(p->comment == txt)
        return;

    p->comment = txt;
    Q_EMIT commentChanged();

    save();
}

QString AsemanAutoStartManager::comment() const
{
    return p->comment;
}

void AsemanAutoStartManager::setName(const QString &name)
{
    if(p->name == name)
        return;

    p->name = name;
    Q_EMIT nameChanged();

    save();
}

QString AsemanAutoStartManager::name() const
{
    return p->name;
}

void AsemanAutoStartManager::setType(const QString &t)
{
    if(p->type == t)
        return;

    p->type = t;
    Q_EMIT typeChanged();

    save();
}

QString AsemanAutoStartManager::type() const
{
    return p->type;
}

void AsemanAutoStartManager::setActive(bool active)
{
    if(p->active == active)
        return;

    p->active = active;
    Q_EMIT activeChanged();

    save();
}

bool AsemanAutoStartManager::active() const
{
    return p->active;
}

#if defined(Q_OS_MAC) && defined(OSX_CORE_SERVICES_AVAILABLE)
CFURLRef prepareURL(const QString& path)
{
    QByteArray app_path_byte_array = path.toLatin1();
    // checking for .app
    int appIdx = app_path_byte_array.indexOf(".app");

    bool isDir = false;

    if (appIdx > 0)
    {
        app_path_byte_array = app_path_byte_array.mid(0, appIdx + 4);
        isDir = true;
    }

    CFURLRef url = CFURLCreateFromFileSystemRepresentation(
        NULL, (const UInt8 *)app_path_byte_array.constData(), app_path_byte_array.size(), isDir);
    if (!url)
    {
        qWarning("unable to create CFURLRef");
        return NULL;
    }

    return url;
}

bool hasLoginItem(const QString& name)
{
    LSSharedFileListRef login_items = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
    if (!login_items)
    {
        qWarning("unable to get login items");
        return false;
    }

    CFArrayRef login_items_array = LSSharedFileListCopySnapshot(login_items, NULL);
    if (!login_items_array)
    {
        qWarning("unable to get login items array");
        CFRelease(login_items);
        return false;
    }
    CFIndex count = CFArrayGetCount(login_items_array);
    for (CFIndex i = 0; i < count; i += 1)
    {
        LSSharedFileListItemRef item = (LSSharedFileListItemRef) CFArrayGetValueAtIndex(login_items_array, i);
        CFStringRef displayName = LSSharedFileListItemCopyDisplayName(item);
        CFComparisonResult result = CFStringCompare(displayName, name.toCFString(), 0);
        CFRelease(displayName);
        if (result == kCFCompareEqualTo)
        {
            CFRelease(login_items_array);
            CFRelease(login_items);
            return true;
        }
    }

    CFRelease(login_items_array);
    CFRelease(login_items);
    return false;
}
#endif

void AsemanAutoStartManager::refresh()
{
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
    const QString &pathDir = QDir::homePath() + QStringLiteral("/.config/autostart");
    const QString &path = pathDir + QStringLiteral("/") + p->source + QStringLiteral(".desktop");

    QDir().mkpath(pathDir);

    QFile file(path);
    if(!file.open(QFile::ReadOnly))
        return;

    const QString data = QString::fromUtf8(file.readAll());
    p->active = !data.contains(QStringLiteral("Hidden=true"));

    Q_EMIT activeChanged();
#elif defined(Q_OS_WIN)
    QSettings autoStartSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    p->active = autoStartSettings.contains(p->source);

    Q_EMIT activeChanged();
#elif defined(Q_OS_MAC) && defined(OSX_CORE_SERVICES_AVAILABLE)
    p->active = hasLoginItem(p->name);

    Q_EMIT activeChanged();
#endif
}

void AsemanAutoStartManager::save()
{
#if defined(Q_OS_LINUX) || defined(Q_OS_OPENBSD)
    const QString &pathDir = QDir::homePath() + QStringLiteral("/.config/autostart");
    const QString &path = pathDir + QStringLiteral("/") + p->source + QStringLiteral(".desktop");

    QDir().mkpath(pathDir);

    QString data = QStringLiteral("[Desktop Entry]") +
            "\nHidden=" + (p->active?"false":"true") +
            "\nX-GNOME-Autostart-enabled=" + (p->active?"true":"false") +
            "\nName=" + p->name +
            "\nName[en_US]=" + p->name +
            "\nComment=" + p->comment +
            "\nComment[en_US]=" + p->comment +
            "\nType=" + p->type +
            "\nExec=" + p->command +
            "\nNoDisplay=false\n";

    QFile file(path);
    if(!file.open(QFile::WriteOnly))
        return;

    file.write(data.toUtf8());
    file.close();
#elif defined(Q_OS_WIN)
    QSettings autoStartSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    if(p->active)
    {
        autoStartSettings.setValue(p->source, QDir::toNativeSeparators(QDir::cleanPath(p->command)));
    }
    else
    {
        autoStartSettings.remove(p->source);
    }
#elif defined(Q_OS_MAC) && defined(OSX_CORE_SERVICES_AVAILABLE)
    CFURLRef url = prepareURL(p->command);
    if (!url)
    {
        qWarning("unable to create CFURLRef");
        return;
    }

    LSSharedFileListRef login_items = LSSharedFileListCreate(NULL, kLSSharedFileListSessionLoginItems, NULL);
    if (!login_items)
    {
        qWarning("unable to get login items");
        return;
    }

    CFArrayRef login_items_array = LSSharedFileListCopySnapshot(login_items, NULL);
    if (!login_items_array)
    {
        qWarning("unable to get login items array");
        CFRelease(login_items);
        return;
    }
    CFIndex count = CFArrayGetCount(login_items_array);
    CFStringRef url_string = CFURLGetString(url);
    CFURLRef item_url = NULL;
    for (CFIndex i = 0; i < count; i += 1)
    {
        LSSharedFileListItemRef item = (LSSharedFileListItemRef) CFArrayGetValueAtIndex(login_items_array, i);
        if (LSSharedFileListItemResolve(item, 0, &item_url, NULL) != 0)
        {
            qWarning("unable to resolve login item");
            CFRelease(login_items_array);
            CFRelease(login_items);
            return;
        }
        CFStringRef item_url_string = CFURLGetString(item_url);

        CFComparisonResult result = CFStringCompare(url_string, item_url_string, 0);
        CFRelease(item_url);
        if (result == kCFCompareEqualTo)
        {
            if (!p->active)
            {
                LSSharedFileListItemRemove(login_items, item);
                CFRelease(login_items_array);
                CFRelease(login_items);
                return;
            }

            qWarning("found in login items already");
            CFRelease(login_items_array);
            CFRelease(login_items);
            return;
        }
    }

    if (p->active)
    {
        LSSharedFileListItemRef item = LSSharedFileListInsertItemURL(
            login_items, kLSSharedFileListItemLast, p->name.toCFString(), NULL, url, NULL, NULL);
        if (!item)
        {
            qWarning("Unable to add to login items");
            CFRelease(login_items_array);
            CFRelease(login_items);
            return;
        }
        CFRelease(item);
    }

    CFRelease(login_items_array);
    CFRelease(login_items);
#endif
}

AsemanAutoStartManager::~AsemanAutoStartManager()
{
    delete p;
}
