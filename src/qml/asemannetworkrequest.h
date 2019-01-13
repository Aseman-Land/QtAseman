#ifndef ASEMANNETWORKREQUEST_H
#define ASEMANNETWORKREQUEST_H

#include <QJSValue>
#include <QObject>

#include "asemantools_global.h"

class LIBQTASEMAN_QML_EXPORT AsemanNetworkRequest : public QObject
{
    Q_OBJECT
    class Private;

public:
    AsemanNetworkRequest(QObject *parent = Q_NULLPTR);
    ~AsemanNetworkRequest();

Q_SIGNALS:

public Q_SLOTS:
    void post(const QString &url, const QVariantMap &query, const QString &data, const QJSValue &callback, const QString &type = "application/json");
    void get(const QString &url, const QVariantMap &query, const QJSValue &callback);

private:
    Private *p;
};

#endif // ASEMANNETWORKREQUEST_H
