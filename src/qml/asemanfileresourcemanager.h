#ifndef ASEMANFILERESOURCEMANAGER_H
#define ASEMANFILERESOURCEMANAGER_H

#include <QObject>
#include <QJSValue>
#include <QThread>
#include <QQmlEngine>

#include "asemantools_global.h"

class LIBQTASEMAN_QML_EXPORT AsemanFileResourceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString root READ root WRITE setRoot NOTIFY rootChanged)

    class Private;
    class FileThread;

public:
    AsemanFileResourceManager(QQmlEngine *parent = Q_NULLPTR);
    virtual ~AsemanFileResourceManager();

    void setRoot(const QString &root);
    QString root() const;

public Q_SLOTS:
    /*!
     * Callback is a js function that is (path, copiedByteSize, totalSize) signature
     * that send progress of the copy process to the js area.
     */
    void insert(const QString &file, const QJSValue &callback);
    bool remove(const QString &id);
    QString get(const QString &id);

Q_SIGNALS:
    void rootChanged();

private:
    Private *p;
};

class AsemanFileResourceManager::FileThread: public QObject
{
    Q_OBJECT
public:
    FileThread(): QObject() {}
    virtual ~FileThread() {}

public Q_SLOTS:
    void copy(const QString &src, const QString &root);

Q_SIGNALS:
    void copyFinished();
    void copyProgress(const QString &id, qint64 bytes, qint64 total);
};

typedef AsemanFileResourceManager QAsemanFileResourceManager;

#endif // ASEMANFILERESOURCEMANAGER_H
