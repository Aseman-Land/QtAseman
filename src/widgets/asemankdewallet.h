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

#ifndef ASEMANKDEWALLET_H
#define ASEMANKDEWALLET_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>
#include <QByteArray>

#include "asemanwidgets_global.h"

class AsemanKdeWalletPrivate;
class LIBQTASEMAN_WIDGETS_EXPORT AsemanKdeWallet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList availableWallets READ availableWallets NOTIFY availableWalletsChanged)
    Q_PROPERTY(bool opened READ opened NOTIFY openedChanged)
    Q_PROPERTY(QString wallet READ wallet WRITE setWallet NOTIFY walletChanged)
    Q_PROPERTY(QStringList folderList READ folderList NOTIFY folderListChanged)

public:
    AsemanKdeWallet(QObject *parent = Q_NULLPTR);
    virtual ~AsemanKdeWallet();

    QStringList availableWallets() const;
    QStringList folderList() const;

    void setWallet(const QString &wallet);
    QString wallet() const;

    bool opened() const;

public Q_SLOTS:
    bool createFolder(const QString &name);
    bool removeFolder(const QString &name);
    QByteArray readEntry(const QString &folder, const QString &key);
    QVariantMap readEntryList(const QString &folder, const QString &key);
    QByteArray readMap(const QString &folder, const QString &key);
    QVariantMap readMapList(const QString &folder, const QString &key);
    QString readPassword(const QString &folder, const QString &key);
    QVariantMap readPasswordList(const QString &folder, const QString &key);
    int removeEntry(const QString &folder, const QString &key);
    int renameEntry(const QString &folder, const QString &oldName, const QString &newName);
    int writeEntry(const QString &folder, const QString &key, const QByteArray &value);
    int writeEntry(const QString &folder, const QString &key, const QByteArray &value, int entryType);
    int writeMap(const QString &folder, const QString &key, const QByteArray &value);
    int writePassword(const QString &folder, const QString &key, const QString &value);
    bool hasEntry(const QString &folder, const QString &key);
    bool hasFolder(const QString &folder);

    bool open();
    bool close();

Q_SIGNALS:
    void availableWalletsChanged();
    void folderListChanged();
    void openedChanged();
    void walletChanged();

private Q_SLOTS:
    void fetchWalletsList();
    void fetchFolderList();

private:
    AsemanKdeWalletPrivate *p;
};

typedef AsemanKdeWallet QAsemanKdeWallet;

#endif // ASEMANKDEWALLET_H
