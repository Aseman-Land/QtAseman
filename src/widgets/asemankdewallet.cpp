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

#define APP_ID AsemanApplication::applicationDisplayName()
#define DBUS_SERVICE QStringLiteral("org.kde.kwalletd")
#define DBUS_PATH    QStringLiteral("/modules/kwalletd")
#define DBUS_OBJECT  QStringLiteral("org.kde.KWallet")
#define DBUS_SIGNAL_WALLET_CREATED QStringLiteral("walletCreated")
#define DBUS_SIGNAL_WALLET_DELETED QStringLiteral("walletDeleted")
#define DBUS_SIGNAL_FOLDERLIST_UPDATED QStringLiteral("folderListUpdated")
#define DBUS_SLOT_WALLETS QStringLiteral("wallets")
#define DBUS_SLOT_OPEN QStringLiteral("open")
#define DBUS_SLOT_CLOSE QStringLiteral("close")
#define DBUS_SLOT_FOLDERLIST QStringLiteral("folderList")
#define DBUS_NCLOSE  QStringLiteral("CloseNotification")

#include "asemankdewallet.h"
#include "asemanapplication.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDebug>

class AsemanKdeWalletPrivate
{
public:
    QStringList availableWallets;
    QStringList folderList;

    QDBusConnection *connection;
    bool open;
    int handle;
    QString wallet;
};

AsemanKdeWallet::AsemanKdeWallet(QObject *parent) :
    QObject(parent)
{
    p = new AsemanKdeWalletPrivate;
    p->handle = 0;

    p->connection = new QDBusConnection( QDBusConnection::sessionBus() );
    p->connection->connect( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_SIGNAL_WALLET_CREATED , this , SLOT(fetchWalletsList()));
    p->connection->connect( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_SIGNAL_WALLET_DELETED , this , SLOT(fetchWalletsList()));
    p->connection->connect( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_SIGNAL_FOLDERLIST_UPDATED , this , SLOT(fetchFolderList()));

    fetchWalletsList();
}

QStringList AsemanKdeWallet::availableWallets() const
{
    return p->availableWallets;
}

QStringList AsemanKdeWallet::folderList() const
{
    return p->folderList;
}

void AsemanKdeWallet::setWallet(const QString &wallet)
{
    if(p->wallet == wallet)
        return;

    p->wallet = wallet;
    Q_EMIT walletChanged();
}

QString AsemanKdeWallet::wallet() const
{
    return p->wallet;
}

bool AsemanKdeWallet::opened() const
{
    return p->handle;
}

bool AsemanKdeWallet::createFolder(const QString &name)
{
    if(!p->handle)
        return false;

    QVariantList args;
    args << p->handle;
    args << name;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return false;

    qint64 ok = res.first().toBool();
    if(!ok)
        return false;

    p->folderList << name;
    Q_EMIT folderListChanged();
    return true;
}

bool AsemanKdeWallet::removeFolder(const QString &name)
{
    if(!p->handle)
        return false;

    QVariantList args;
    args << p->handle;
    args << name;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return false;

    qint64 ok = res.first().toBool();
    if(!ok)
        return false;

    p->folderList.removeAll(name);
    Q_EMIT folderListChanged();
    return true;
}

QByteArray AsemanKdeWallet::readEntry(const QString &folder, const QString &key)
{
    if(!p->handle)
        return QByteArray();

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return QByteArray();

    return res.first().toByteArray();
}

QVariantMap AsemanKdeWallet::readEntryList(const QString &folder, const QString &key)
{
    if(!p->handle)
        return QVariantMap();

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return QVariantMap();

    return res.first().toMap();
}

QByteArray AsemanKdeWallet::readMap(const QString &folder, const QString &key)
{
    if(!p->handle)
        return QByteArray();

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return QByteArray();

    return res.first().toByteArray();
}

QVariantMap AsemanKdeWallet::readMapList(const QString &folder, const QString &key)
{
    if(!p->handle)
        return QVariantMap();

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return QVariantMap();

    return res.first().toMap();
}

QString AsemanKdeWallet::readPassword(const QString &folder, const QString &key)
{
    if(!p->handle)
        return QString();

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return QString();

    return res.first().toString();
}

QVariantMap AsemanKdeWallet::readPasswordList(const QString &folder, const QString &key)
{
    if(!p->handle)
        return QVariantMap();

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return QVariantMap();

    return res.first().toMap();
}

int AsemanKdeWallet::removeEntry(const QString &folder, const QString &key)
{
    if(!p->handle)
        return 0;

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    return res.first().toInt();
}

int AsemanKdeWallet::renameEntry(const QString &folder, const QString &oldName, const QString &newName)
{
    if(!p->handle)
        return 0;

    QVariantList args;
    args << p->handle;
    args << folder;
    args << oldName;
    args << newName;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    return res.first().toInt();
}

int AsemanKdeWallet::writeEntry(const QString &folder, const QString &key, const QByteArray &value)
{
    if(!p->handle)
        return 0;

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << value;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    return res.first().toInt();
}

int AsemanKdeWallet::writeEntry(const QString &folder, const QString &key, const QByteArray &value, int entryType)
{
    if(!p->handle)
        return 0;

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << value;
    args << entryType;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    return res.first().toInt();
}

int AsemanKdeWallet::writeMap(const QString &folder, const QString &key, const QByteArray &value)
{
    if(!p->handle)
        return 0;

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << value;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    return res.first().toInt();
}

int AsemanKdeWallet::writePassword(const QString &folder, const QString &key, const QString &value)
{
    if(!p->handle)
        return 0;

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << value;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    return res.first().toInt();
}

bool AsemanKdeWallet::hasEntry(const QString &folder, const QString &key)
{
    if(!p->handle)
        return 0;

    QVariantList args;
    args << p->handle;
    args << folder;
    args << key;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    return res.first().toBool();
}

bool AsemanKdeWallet::hasFolder(const QString &folder)
{
    if(!p->handle)
        return 0;

    QVariantList args;
    args << p->handle;
    args << folder;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , QString::fromUtf8(__FUNCTION__) );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return 0;

    return res.first().toBool();
}

bool AsemanKdeWallet::open()
{
    if(p->handle)
        close();
    if(p->wallet.isEmpty())
        return false;

    QVariantList args;
    args << p->wallet;
    args << (qint64)0;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_SLOT_OPEN );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return false;

    int hid = res.first().toInt();
    p->handle = hid<=0? 0 : hid;

    fetchFolderList();

    Q_EMIT openedChanged();
    return opened();
}

bool AsemanKdeWallet::close()
{
    if(!p->handle)
        return true;

    QVariantList args;
    args << p->handle;
    args << true;
    args << APP_ID;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_SLOT_CLOSE );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return false;

    bool ok = res.first().toBool();
    if(ok)
        p->handle = false;

    Q_EMIT openedChanged();
    return true;
}

void AsemanKdeWallet::fetchWalletsList()
{
    QVariantList args;

    QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_SLOT_WALLETS );
    omsg.setArguments( args );

    const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
    const QVariantList & res = imsg.arguments();
    if( res.isEmpty() )
        return;

    p->availableWallets = res.first().toStringList();
    Q_EMIT availableWalletsChanged();
}

void AsemanKdeWallet::fetchFolderList()
{
    p->folderList.clear();
    if(p->handle)
    {
        QVariantList args;
        args << p->handle;
        args << APP_ID;

        QDBusMessage omsg = QDBusMessage::createMethodCall( DBUS_SERVICE , DBUS_PATH , DBUS_OBJECT , DBUS_SLOT_FOLDERLIST );
        omsg.setArguments( args );

        const QDBusMessage & imsg = p->connection->call( omsg , QDBus::BlockWithGui );
        const QVariantList & res = imsg.arguments();
        if( res.isEmpty() )
            return;

        p->folderList = res.first().toStringList();
    }

    Q_EMIT folderListChanged();
}

AsemanKdeWallet::~AsemanKdeWallet()
{
    delete p;
}
