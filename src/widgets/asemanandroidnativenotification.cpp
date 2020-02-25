#include "asemanandroidnativenotification.h"

#include <asemanjavalayer.h>

class AsemanAndroidNativeNotification::Private
{
public:
    QColor color;
    quint32 id;
};

AsemanAndroidNativeNotification::AsemanAndroidNativeNotification(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->id = 1000;
}

void AsemanAndroidNativeNotification::setColor(const QColor &color)
{
    if(p->color == color)
        return;

    p->color = color;
    Q_EMIT colorChanged();
}

QColor AsemanAndroidNativeNotification::color() const
{
    return p->color;
}

quint32 AsemanAndroidNativeNotification::sendNotify(const QString &title, const QString &body, const QString &icon, quint32 replace_id, int timeOut, const QStringList &actions)
{
    qint32 iconPathIdx = icon.lastIndexOf(QStringLiteral("/"));
    if(iconPathIdx == -1)
        return -1;

    QString iconPath = icon.left(iconPathIdx);
    QString iconName = icon.mid(iconPathIdx+1);

    qint32 id = replace_id? replace_id : p->id;
    if(!AsemanJavaLayer::instance()->startNotification(id, title, body, iconPath, iconName, "default", true) )
        return -1;

    if(replace_id == 0) p->id++;
    return id;
}

void AsemanAndroidNativeNotification::closeNotification(quint32 id)
{
    AsemanJavaLayer::instance()->stopNotification(id);
}

AsemanAndroidNativeNotification::~AsemanAndroidNativeNotification()
{
    delete p;
}
