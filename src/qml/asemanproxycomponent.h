#ifndef ASEMANPROXYCOMPONENT_H
#define ASEMANPROXYCOMPONENT_H

#include <QObject>
#include <QQmlComponent>

#include "asemantools_global.h"

class LIBQTASEMAN_QML_EXPORT AsemanProxyComponent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlComponent* source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QObject* object READ object NOTIFY objectChanged)

    class Private;

public:
    AsemanProxyComponent(QObject *parent = Q_NULLPTR);
    virtual ~AsemanProxyComponent();

    QQmlComponent *source() const;
    void setSource(QQmlComponent *component);

    QObject *object() const;

Q_SIGNALS:
    void sourceChanged();
    void objectChanged();

private:
    void create();
    void setObject(QObject *object);

private:
    Private *p;
};

#endif // ASEMANPROXYCOMPONENT_H
