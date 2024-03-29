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

#include "asemansqlobject.h"

#ifdef QT_SQL_LIB
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#endif

#include <QTimer>
#include <QDataStream>
#include <QBuffer>
#include <QCryptographicHash>
#include <QSharedPointer>
#include <QMetaObject>
#include <QMetaProperty>
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QMutex>
#include <QUuid>

#define MSSQL_FIX_VALUE(VALUE) { \
        switch ( static_cast<qint32>(VALUE.type()) ) { \
        case QVariant::DateTime: \
            VALUE = VALUE.toDateTime().toString(QStringLiteral("yyyyMMdd HH:mm:ss")); \
            break; \
        case QVariant::Date: \
            VALUE = VALUE.toDateTime().toString(QStringLiteral("yyyyMMdd")); \
            break; \
        case QVariant::Time: \
            VALUE = VALUE.toDateTime().toString(QStringLiteral("HH:mm:ss")); \
            break; \
        } \
    }

class AsemanSqlObject::Private
{
public:
    QString table;
    QStringList primaryKeys;
    QVariant driver;

    QString driverStr;
    QString databaseName;
    QString databaseNameTemplate;
    QString host;
    qint32 port;
    QString userName;
    QString password;
    QString createQuery;
    QString lastError;

    QTimer *initTimer;

    static QHash<AsemanSqlObject*, Core*> cores;
    QString key;
};

class AsemanSqlObject::Core {
public:
    ~Core() {
        QMutexLocker locker(&mutex);
#ifdef QT_SQL_LIB
        if (_db->isOpen())
            _db->close();

        delete _db;
        if(_connectionName.length()) {
            QSqlDatabase::removeDatabase(_connectionName);
        }
#endif

        objects.remove(_connectionName);
    }

#ifdef QT_SQL_LIB
    QSqlDatabase &get() { return *_db; }
#endif

    static Core *getInstance(const QString &driver, const QString &connectionName) {
        QMutexLocker locker(&mutex);
        Core *res = objects.value(connectionName);
#ifdef QT_SQL_LIB
        if(!res)
        {
            res = new Core(driver, connectionName);
            objects[connectionName] = res;
        }
#else
        Q_UNUSED(driver)
#endif
        return res;
    }

private:
    Core(const QString &driver, const QString &connectionName):
        _connectionName(connectionName)
    {
#ifdef QT_SQL_LIB
        *_db = QSqlDatabase::addDatabase(driver, connectionName);
#endif
        objects.insert(_connectionName, this);
    }

    QString _connectionName;
#ifdef QT_SQL_LIB
    QSqlDatabase *_db = new QSqlDatabase;
#endif

    static QMutex mutex;
    static QHash<QString, Core*> objects;
};

QHash<AsemanSqlObject*, AsemanSqlObject::Core*> AsemanSqlObject::Private::cores;
QHash<QString, AsemanSqlObject::Core*> AsemanSqlObject::Core::objects;
QMutex AsemanSqlObject::Core::mutex;


AsemanSqlObject::AsemanSqlObject(QObject *parent) :
    QObject(parent)
{
    p = new Private;

    p->initTimer = new QTimer(this);
    p->initTimer->setSingleShot(true);
    p->initTimer->setInterval(100);

    connect(p->initTimer, &QTimer::timeout, this, &AsemanSqlObject::initialize);
}

void AsemanSqlObject::initialize()
{
    init();
}

void AsemanSqlObject::setDriver(const QVariant &driver)
{
    if (p->driver == driver)
        return;

    p->driver = driver;
    if (p->driver.type() == QVariant::String)
        p->driverStr = p->driver.toString();
    else
    {
        switch (p->driver.toInt())
        {
        case NoneDriver:
            p->driverStr = QStringLiteral("");
            break;

        case SQLite:
            p->driverStr = QStringLiteral("QSQLITE");
            break;

        case MySQL:
            p->driverStr = QStringLiteral("MYSQL");
            break;

        case PostgreSQL:
            p->driverStr = QStringLiteral("QPSQL");
            break;

        case MSSQL:
            p->databaseNameTemplate = QStringLiteral( "%1;"
                                                      "SERVER=%HOSTADDRESS%;"
                                                      "DATABASE=%DATABASENAME%;"
                                                      "UID=%USERNAME%;"
                                                      "PWD=%PASSWORD%;");
        #ifdef Q_OS_LINUX
            p->databaseNameTemplate = p->databaseNameTemplate.arg("DRIVER={ODBC Driver 17 for SQL Server}");
        #else
            p->databaseNameTemplate = p->databaseNameTemplate.arg("DRIVER={SQL Server}");
        #endif
            p->driverStr = QStringLiteral("QODBC");
            break;

        case ODBC:
            p->driverStr = QStringLiteral("QODBC");
            break;
        }
    }
    refreshKey();

    Q_EMIT driverChanged();
}

QVariant AsemanSqlObject::driver() const
{
    return p->driver;
}

void AsemanSqlObject::setTable(const QString &table)
{
    if (p->table == table)
        return;

    p->table = table;
    Q_EMIT tableChanged();
}

QString AsemanSqlObject::table() const
{
    return p->table;
}

void AsemanSqlObject::setPrimaryKeys(const QStringList &primaryKeys)
{
    if (p->primaryKeys == primaryKeys)
        return;

    p->primaryKeys = primaryKeys;
    Q_EMIT primaryKeysChanged();
}

QStringList AsemanSqlObject::primaryKeys() const
{
    return p->primaryKeys;
}

qint32 AsemanSqlObject::port() const
{
    return p->port;
}

void AsemanSqlObject::setPort(qint32 port)
{
    if (p->port == port)
        return;

    p->port = port;
    refreshKey();
    void portChanged();
}

QString AsemanSqlObject::host() const
{
    return p->host;
}

void AsemanSqlObject::setHost(const QString &host)
{
    if (p->host == host)
        return;

    p->host = host;
    refreshKey();
    void hostChanged();
}

QString AsemanSqlObject::databaseName() const
{
    return p->databaseName;
}

void AsemanSqlObject::setDatabaseName(const QString &databaseName)
{
    if (p->databaseName == databaseName)
        return;

    p->databaseName = databaseName;
    refreshKey();
    void databaseNameChanged();
}

QString AsemanSqlObject::userName() const
{
    return p->userName;
}

void AsemanSqlObject::setUserName(const QString &userName)
{
    if (p->userName == userName)
        return;

    p->userName = userName;
    refreshKey();
    void userNameChanged();
}

QString AsemanSqlObject::password() const
{
    return p->password;
}

void AsemanSqlObject::setPassword(const QString &password)
{
    if (p->password == password)
        return;

    p->password = password;
    refreshKey();
    void passwordChanged();
}

QString AsemanSqlObject::createQuery() const
{
    return p->createQuery;
}

void AsemanSqlObject::setCreateQuery(const QString &createQuery)
{
    if (p->createQuery == createQuery)
        return;

    p->createQuery = createQuery;
    Q_EMIT createQueryChanged();
}

QString AsemanSqlObject::lastError() const
{
    return p->lastError;
}

qint32 AsemanSqlObject::insert(const QString &extra)
{
#ifdef QT_SQL_LIB
    Core *core = init();

    QStringList properties = AsemanSqlObject::properties();
    if(primaryKeys().contains(QStringLiteral("id")) && property("id").type() == QVariant::Int && property("id").toInt() == 0)
        properties.removeAll(QStringLiteral("id"));

    QString queryArgs = properties.join(QStringLiteral(", "));
    QString queryArgsBinds = QStringLiteral(":") + properties.join(QStringLiteral(", :"));

    QString query = QStringLiteral("REPLACE INTO ") + p->table + QStringLiteral(" (") + queryArgs + QStringLiteral(")") +
                    QStringLiteral(" VALUES (") + queryArgsBinds + QStringLiteral(")");

    QSqlQuery q(core->get());
    q.prepare(query + QStringLiteral(" ") + extra);
    for (const QString &key: properties)
    {
        QVariant value = property(key.toUtf8());
        if (p->driver.toInt() == MSSQL)
            MSSQL_FIX_VALUE(value)

        q.bindValue(":" + key, value);
    }

    if (!queryExec(q))
        return 0;
    else
        return q.lastInsertId().toInt();
#else
    return 0;
#endif
}

void AsemanSqlObject::update(const QString &_where, const QVariantMap &binds)
{
    QString query = "UPDATE " + p->table + " SET ";

    QStringList properties = AsemanSqlObject::properties();
    QStringList pkeys = primaryKeys();

    QString set;
    for (const QString &pr: properties)
    {
        if (set.length())
            set += QStringLiteral(", ");
        set += (":" + pr + " = " + pr);
    }

    QString where = _where;
    for (const QString &pk: pkeys)
    {
        if (where.length())
            where += QStringLiteral(" AND ");
        where += (":" + pk + " = " + pk);
    }

    query += set + " WHERE " + where;

    AsemanSqlObject::query(query, binds);
}

QVariantList AsemanSqlObject::select()
{
    QString where;
    QStringList properties = AsemanSqlObject::properties();
    QStringList pkeys = primaryKeys();
    for (const QString &pk: pkeys)
    {
        if (where.length())
            where += QStringLiteral(" AND ");
        where += (":" + pk + " = " + pk);
    }

    return select(QStringLiteral(""), where, QStringLiteral(""), {});
}

QVariantList AsemanSqlObject::select(const QString join, const QString &where, const QString &extra, const QVariantMap &binds)
{
    QString query = QStringLiteral("SELECT * FROM ") + p->table + (join.count()? QStringLiteral(" ") + join : QStringLiteral(""))
                    + (where.count()? QStringLiteral(" WHERE ") + where : QStringLiteral(""))
                    + (extra.count()? QStringLiteral(" ") + extra : QStringLiteral(""));

    return AsemanSqlObject::query(query, binds);
}

void AsemanSqlObject::fetch()
{
    QStringList properties = AsemanSqlObject::properties();
    QStringList pkeys = primaryKeys();
    QVariantList list = select();
    if (list.isEmpty())
        return;

    QVariantMap map = list.first().toMap();
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext())
    {
        i.next();
        const QString &key = i.key();
        if(!properties.contains(key) || pkeys.contains(key))
            continue;

        setProperty(key.toUtf8(), i.value());
    }
}

void AsemanSqlObject::deleteQuery(const QString &where, const QVariantMap &binds)
{
    QString query = QStringLiteral("DELETE FROM ") + p->table + (where.count()? QStringLiteral(" WHERE ") + where : QStringLiteral(""));
    AsemanSqlObject::query(query, binds);
}

QVariantList AsemanSqlObject::query(const QString &query, const QVariantMap &binds)
{
    QVariantList res;
#ifdef QT_SQL_LIB
    Core *core = init();

    QSqlQuery q(core->get());
    q.prepare(query);

    QVariantMap fixedBinds = prepareBinds(binds);
    QMapIterator<QString, QVariant> i(fixedBinds);
    while (i.hasNext())
    {
        i.next();
        q.bindValue(i.key(), i.value());
    }

    if (!queryExec(q))
        return QVariantList();

    return generateResult(q);
#else
    return res;
#endif
}

void AsemanSqlObject::queryAsync(const QString &query, const QVariantMap &binds, std::function<void (QVariantList result, const QString &error)> callback)
{
    Core *core = init(QUuid::createUuid().toString());
    QVariantMap fixedBinds = prepareBinds(binds);

    AsemanSqlObjectAsync *async = new AsemanSqlObjectAsync(core, query, fixedBinds);

    connect(async, &AsemanSqlObjectAsync::error, this, [this, callback](const QString &error){
        setLastError(error);
        callback(QVariantList(), error);
    });
    connect(async, &AsemanSqlObjectAsync::result, this, [callback](const QVariantList &result){
        callback(result, QString());
    });
    connect(async, &AsemanSqlObjectAsync::finished, async, [async](){
        async->deleteLater();
    });

    async->start();
}

QVariantMap AsemanSqlObject::prepareBinds(const QVariantMap &binds) const
{
    QVariantMap res;

    QStringList properties = AsemanSqlObject::properties();
    for (const QString &key: properties)
    {
        QVariant value = property(key.toUtf8());
        if (p->driver.toInt() == MSSQL)
            MSSQL_FIX_VALUE(value)

        res[":" + key] = value;
    }

    QMapIterator<QString, QVariant> i(binds);
    while (i.hasNext())
    {
        i.next();
        QVariant value = i.value();
        if (p->driver.toInt() == MSSQL)
            MSSQL_FIX_VALUE(value)

        res[":" + i.key()] = value;
    }

    return res;
}

QVariantList AsemanSqlObject::generateResult(QSqlQuery &q)
{
    QVariantList res;
#ifdef QT_SQL_LIB
    while (q.next())
    {
        QSqlRecord r = q.record();
        QVariantMap map;
        for (qint32 i=0; i<r.count(); i++)
            map[r.fieldName(i)] = r.value(i);

        res << map;
    }
#endif
    return res;
}

void AsemanSqlObject::create()
{
    QStringList queries = p->createQuery.split(QStringLiteral(";"), Qt::SkipEmptyParts);
    for (const QString &q: queries)
        AsemanSqlObject::query(q);
}

void AsemanSqlObject::drop()
{
    AsemanSqlObject::query("DROP TABLE " + p->table);
}

QVariantMap AsemanSqlObject::getData()
{
    QStringList properties = AsemanSqlObject::properties();
    if(primaryKeys().contains(QStringLiteral("id")) && property("id").type() == QVariant::Int && property("id").toInt() == 0)
        properties.removeAll(QStringLiteral("id"));

    QVariantMap res;
    for (const QString &key: properties)
    {
        QVariant value = property(key.toUtf8());
        if (p->driver.toInt() == MSSQL)
            MSSQL_FIX_VALUE(value)

        res[key] = value;
    }

    return res;
}

void AsemanSqlObject::setLastError(const QString &lastError)
{
    if (p->lastError == lastError)
        return;

    p->lastError = lastError;
    Q_EMIT lastErrorChanged();
}

#ifdef QT_SQL_LIB
int AsemanSqlObject::queryExec(QSqlQuery &q)
{
    bool ret = q.exec();
    if (!ret)
        setLastError(q.lastError().text());

    return ret;
}
#endif

QStringList AsemanSqlObject::properties() const
{
    QStringList res;

    const QMetaObject *meta = metaObject();
    for (int i=0; i<meta->propertyCount(); i++)
    {
        QMetaProperty property = meta->property(i);
        const QByteArray &propertyName = property.name();
        if (propertyName == "table" ||
            propertyName == "driver" ||
            propertyName == "databaseName" ||
            propertyName == "host" ||
            propertyName == "port" ||
            propertyName == "userName" ||
            propertyName == "password" ||
            propertyName == "createQuery" ||
            propertyName == "primaryKeys" ||
            propertyName == "lastError" ||
            propertyName == "objectName")
            continue;

        res << QString::fromUtf8(propertyName);
    }

    return res;
}

AsemanSqlObject::Core *AsemanSqlObject::init(const QString &forceConnectionName)
{
    if (forceConnectionName.isEmpty())
        p->initTimer->stop();

    Core *core = Core::getInstance(p->driverStr, (forceConnectionName.count()? forceConnectionName : p->key));
#ifdef QT_SQL_LIB
    if (!core->get().isOpen())
    {
        if (p->databaseNameTemplate.count())
        {
            QString portStr = QString::number(p->port);
            QString dbName = p->databaseNameTemplate;
            dbName.replace(QStringLiteral("%HOSTADDRESS%"), (p->port? p->host + ":" + portStr : p->host));
            dbName.replace(QStringLiteral("%DATABASENAME%"), p->databaseName);
            dbName.replace(QStringLiteral("%USERNAME%"), p->userName);
            dbName.replace(QStringLiteral("%PASSWORD%"), p->password);

            core->get().setDatabaseName(dbName);
        }
        else
        {
            core->get().setHostName(p->host);
            core->get().setPort(p->port);
            core->get().setUserName(p->userName);
            core->get().setPassword(p->password);
            core->get().setDatabaseName(p->databaseName);
        }

        if (!core->get().open())
            setLastError(core->get().lastError().text());
    }
#endif

    if (forceConnectionName.count())
        return core;

    if (Private::cores.value(this) == core)
        return core;
    if (Private::cores.contains(this))
    {
        Core *oldCore = Private::cores.take(this);
        if (Private::cores.keys(oldCore).isEmpty()) // It means there is no need to this object anymore
            delete oldCore;
    }

    Private::cores[this] = core;
    return core;
}

void AsemanSqlObject::refreshKey()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << p->host << p->port << p->driver
           << p->userName << p->password << p->databaseName
           << p->databaseNameTemplate;

    p->key = QString::fromUtf8( QCryptographicHash::hash(data, QCryptographicHash::Md5).toHex() );
}

AsemanSqlObject::~AsemanSqlObject()
{
    Core *oldCore = Private::cores.take(this);
    if (Private::cores.keys(oldCore).isEmpty()) // It means there is no need to this object anymore
        delete oldCore;

    delete p;
}


AsemanSqlObjectAsync::AsemanSqlObjectAsync(AsemanSqlObject::Core *core, const QString &query, const QVariantMap &binds, QObject *parent) :
    QThread(parent),
    mCore(core),
    mQuery(query),
    mBinds(binds)
{
}

void AsemanSqlObjectAsync::run()
{
#ifdef QT_SQL_LIB
    QSqlDatabase db = mCore->get();
    QSqlQuery q(db);
    q.prepare(mQuery);

    QMapIterator<QString, QVariant> i(mBinds);
    while (i.hasNext())
    {
        i.next();
        q.bindValue(i.key(), i.value());
    }

    if (!q.exec())
        Q_EMIT error(q.lastError().text());
    else
        Q_EMIT result( AsemanSqlObject::generateResult(q) );
#else
    Q_EMIT error(QStringLiteral("SQL not supported. Rebuilt Qt and AsemanQml with sql support."));
#endif
}

AsemanSqlObjectAsync::~AsemanSqlObjectAsync()
{
    delete mCore;
}
