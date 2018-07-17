#ifndef ASEMANNETWORKPROXY_H
#define ASEMANNETWORKPROXY_H

#include <QObject>
#include <QNetworkProxy>

#include "asemannetwork_global.h"

class LIBQTASEMAN_NETWORK_EXPORT AsemanNetworkProxy : public QObject
{
    Q_OBJECT
    Q_ENUMS(ProxyType)

    class Private;

    Q_PROPERTY(qint32 type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
    Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:
    enum ProxyType {
        DefaultProxy = QNetworkProxy::DefaultProxy,
        Socks5Proxy = QNetworkProxy::Socks5Proxy,
        NoProxy = QNetworkProxy::NoProxy,
        HttpProxy = QNetworkProxy::HttpProxy,
        HttpCachingProxy = QNetworkProxy::HttpCachingProxy,
        FtpCachingProxy = QNetworkProxy::FtpCachingProxy
    };

    AsemanNetworkProxy(QObject *parent = Q_NULLPTR);
    virtual ~AsemanNetworkProxy();

    qint32 type() const;
    void setType(qint32 type);

    QString hostName() const;
    void setHostName(const QString &hostName);

    quint16 port() const;
    void setPort(const quint16 &port);

    QString user() const;
    void setUser(const QString &user);

    QString password() const;
    void setPassword(const QString &password);

Q_SIGNALS:
    void typeChanged();
    void hostNameChanged();
    void portChanged();
    void userChanged();
    void passwordChanged();

private:
    void refresh();

private:
    Private *p;
};

#endif // ASEMANNETWORKPROXY_H
