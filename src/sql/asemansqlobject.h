/*
    Copyright (C) 2019 Aseman Team
    http://aseman.io

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANSQLOBJECT_H
#define ASEMANSQLOBJECT_H

#include <QObject>
#include <QVariant>

#include "asemansql_global.h"

class LIBQTASEMAN_SQL_EXPORT AsemanSqlObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString table READ table WRITE setTable NOTIFY tableChanged)
    Q_PROPERTY(QVariant driver READ driver WRITE setDriver NOTIFY driverChanged)
    Q_PROPERTY(QString databaseName READ databaseName WRITE setDatabaseName NOTIFY databaseNameChanged)
    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(qint32 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString createQuery READ createQuery WRITE setCreateQuery NOTIFY createQueryChanged)
    Q_PROPERTY(QStringList primaryKeys READ primaryKeys WRITE setPrimaryKeys NOTIFY primaryKeysChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_ENUMS(DriverTypes)

    class Private;
    class Core;

public:
    enum DriverTypes {
        NoneDriver,
        SQLite,
        MySQL,
        PostgreSQL,
        ODBC,
        MSSQL
    };

    AsemanSqlObject(QObject *parent = Q_NULLPTR);
    virtual ~AsemanSqlObject();

    void setTable(const QString &table);
    QString table() const;

    void setPrimaryKeys(const QStringList &primaryKeys);
    QStringList primaryKeys() const;

    void setDriver(const QVariant &driver);
    QVariant driver() const;

    QString databaseName() const;
    void setDatabaseName(const QString &databaseName);

    QString host() const;
    void setHost(const QString &host);

    qint32 port() const;
    void setPort(qint32 port);

    QString userName() const;
    void setUserName(const QString &userName);

    QString password() const;
    void setPassword(const QString &password);

    QString createQuery() const;
    void setCreateQuery(const QString &createQuery);

    QString lastError() const;

public Q_SLOTS:
    qint32 insert(const QString &extra = QString());
    void update(const QString &where = QString(), const QVariantMap &binds = QVariantMap());

    QVariantList select();
    QVariantList select(const QString &where, const QVariantMap &binds) { return select(QStringLiteral(""), where, QStringLiteral(""), binds); }
    QVariantList select(const QString join, const QString &where, const QVariantMap &binds) { return select(join, where, QStringLiteral(""), binds); }
    QVariantList select(const QString join, const QString &where, const QString &extra, const QVariantMap &binds);

    void push() { insert(); }
    void fetch();

    void deleteQuery(const QString &where, const QVariantMap &binds = QVariantMap());

    QVariantList query(const QString &query, const QVariantMap &binds = QVariantMap());

    void create();
    void drop();

    QVariantMap getData();

Q_SIGNALS:
    void tableChanged();
    void databaseNameChanged();
    void hostChanged();
    void portChanged();
    void driverChanged();
    void userNameChanged();
    void passwordChanged();
    void primaryKeysChanged();
    void createQueryChanged();
    void lastErrorChanged();

private:
    Core *init();
    void refreshKey();

    void setLastError(const QString &lastError);
    int queryExec(class QSqlQuery &q);

    QStringList properties();

private:
    Private *p;
};

#endif // ASEMANSQLOBJECT_H
