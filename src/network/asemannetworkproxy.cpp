#include "asemannetworkproxy.h"

class AsemanNetworkProxy::Private
{
public:
    QNetworkProxy proxy;
};

AsemanNetworkProxy::AsemanNetworkProxy(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->proxy = QNetworkProxy::applicationProxy();
}

qint32 AsemanNetworkProxy::type() const
{
    return p->proxy.type();
}

void AsemanNetworkProxy::setType(qint32 type)
{
    if(p->proxy.type() == type)
        return;

    p->proxy.setType( static_cast<QNetworkProxy::ProxyType>(type) );
    refresh();
    Q_EMIT typeChanged();
}

QString AsemanNetworkProxy::hostName() const
{
    return p->proxy.hostName();
}

void AsemanNetworkProxy::setHostName(const QString &hostName)
{
    if(p->proxy.hostName() == hostName)
        return;

    p->proxy.setHostName(hostName);
    refresh();
    Q_EMIT hostNameChanged();
}

quint16 AsemanNetworkProxy::port() const
{
    return p->proxy.port();
}

void AsemanNetworkProxy::setPort(const quint16 &port)
{
    if(p->proxy.port() == port)
        return;

    p->proxy.setPort(port);
    refresh();
    Q_EMIT portChanged();
}

QString AsemanNetworkProxy::user() const
{
    return p->proxy.user();
}

void AsemanNetworkProxy::setUser(const QString &user)
{
    if(p->proxy.user() == user)
        return;

    p->proxy.setUser(user);
    refresh();
    Q_EMIT userChanged();
}

QString AsemanNetworkProxy::password() const
{
    return p->proxy.password();
}

void AsemanNetworkProxy::setPassword(const QString &password)
{
    if(p->proxy.password() == password)
        return;

    p->proxy.setPassword(password);
    refresh();
    Q_EMIT passwordChanged();
}

void AsemanNetworkProxy::refresh()
{
    QNetworkProxy::setApplicationProxy(p->proxy);
}

AsemanNetworkProxy::~AsemanNetworkProxy()
{
    delete p;
}
