#define GET_PATH(ROOT, ID) [](const QString &root, const QString &id) -> QString { \
        QString path = root + "/" + id; \
        return path; \
    }(ROOT, ID)

#include "asemanfileresourcemanager.h"

#include <QDir>
#include <QThread>
#include <QFile>
#include <QCryptographicHash>
#include <QCoreApplication>
#include <QQmlEngine>
#include <QDebug>
#include <QUuid>

class AsemanFileResourceManager::Private
{
public:
    QString root;
    QMap<QThread*, AsemanFileResourceManager::FileThread*> threads;
    QQmlEngine *engine;
};

AsemanFileResourceManager::AsemanFileResourceManager(QQmlEngine *engine) :
    QObject(engine)
{
    p = new Private;
    p->engine = engine;
}

void AsemanFileResourceManager::setRoot(const QString &root)
{
    if(p->root == root)
        return;

    p->root = root;
    QDir().mkpath(p->root);

    Q_EMIT rootChanged();
}

QString AsemanFileResourceManager::root() const
{
    return p->root;
}

void AsemanFileResourceManager::insert(const QString &file, const QJSValue &callback)
{
    const QString root = p->root;

    QThread *thread = new QThread();
    thread->start();

    FileThread *copy = new FileThread();
    copy->moveToThread(thread);

    connect(copy, &AsemanFileResourceManager::FileThread::copyProgress, this, [this, callback](const QString &id, qint64 bytes, qint64 total){

        QQmlEngine *engine = p->engine;
        if(!engine)
            engine = qmlEngine(this);

        if(!engine)
            return;

        QJSValueList args = { engine->toScriptValue<QString>(id),
                              engine->toScriptValue<qint64>(bytes),
                              engine->toScriptValue<qint64>(total) };

        if(callback.isCallable())
            QJSValue(callback).call(args);
    }, Qt::QueuedConnection);
    connect(copy, &AsemanFileResourceManager::FileThread::copyFinished, this, [this, copy, thread](){
        copy->deleteLater();
        thread->quit();
        thread->wait();
        delete thread;
        p->threads.remove(thread);
    }, Qt::QueuedConnection);

    p->threads[thread] = copy;

    QMetaObject::invokeMethod(copy, "copy", Qt::QueuedConnection, Q_ARG(QString, file), Q_ARG(QString, root));
}

bool AsemanFileResourceManager::remove(const QString &id)
{
    return QFile::remove( GET_PATH(p->root, id) );
}

QString AsemanFileResourceManager::get(const QString &id)
{
    return GET_PATH(p->root, id);
}

AsemanFileResourceManager::~AsemanFileResourceManager()
{
    QMapIterator<QThread*, AsemanFileResourceManager::FileThread*> i(p->threads);
    while(i.hasNext())
    {
        i.next();
        i.value()->deleteLater();
        i.key()->quit();
        i.key()->wait();
        delete i.key();
    }

    delete p;
}



void AsemanFileResourceManager::FileThread::copy(const QString &src, const QString &root)
{
    QFileInfo info(src);
    const QString tmpId = QUuid::createUuid().toString();
    const QString &tmpDst = GET_PATH(root, tmpId);

    QFile srcFile(src);
    if(!srcFile.open(QFile::ReadOnly)) {
        Q_EMIT copyFinished();
        return;
    }

    QFile dstFile(tmpDst);
    if(!dstFile.open(QFile::WriteOnly)) {
        Q_EMIT copyFinished();
        return;
    }

    QCryptographicHash hash(QCryptographicHash::Md5);

    qint64 bytes = 0;
    while(!srcFile.atEnd()) {
        QByteArray data = srcFile.read(512*1024);

        hash.addData(data);
        dstFile.write(data);

        bytes += data.size();
        Q_EMIT copyProgress(QString(), bytes, srcFile.size());
    }

    dstFile.close();
    srcFile.close();

    const QString id = hash.result().toHex() + "." + info.suffix();
    const QString &dst = GET_PATH(root, id);

    QFile::remove(dst);
    QFile::rename(tmpDst, dst);

    Q_EMIT copyProgress(id, srcFile.size(), srcFile.size());
    Q_EMIT copyFinished();
}
