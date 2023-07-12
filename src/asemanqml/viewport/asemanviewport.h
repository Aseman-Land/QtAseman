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

#ifndef ASEMANVIEWPORT_H
#define ASEMANVIEWPORT_H

#include <QObject>
#include <QQuickItem>

#include <optional>

#include "asemanviewportitem.h"

class AsemanViewportAttechedProperty;
class AsemanViewport : public QQuickItem
{
    Q_OBJECT
    class Private;
    Q_PROPERTY(QQmlListProperty<AsemanViewportItem> items READ items NOTIFY itemsChanged)
    Q_PROPERTY(QStringList keys READ keys NOTIFY itemsChanged)
    Q_PROPERTY(bool primaryViewport READ primaryViewport WRITE setPrimaryViewport NOTIFY primaryViewportChanged)

public:
    AsemanViewport(QQuickItem *parent = Q_NULLPTR);
    virtual ~AsemanViewport();

    QQmlListProperty<AsemanViewportItem> items();
    QList<AsemanViewportItem*> itemsList() const;
    QStringList keys() const;

    static AsemanViewportAttechedProperty *qmlAttachedProperties(QObject *object);

    bool primaryViewport();
    bool isPrimaryViewport() const;
    void setPrimaryViewport(bool newPrimaryViewport);

public Q_SLOTS:
    QVariant getComponent(const QString &name);
    QQmlComponent *createComponent(const QUrl &fileUrl, bool asyn = false);

Q_SIGNALS:
    void itemsChanged();
    void viewportChanged();
    void primaryViewportChanged();

private:
    static void append(QQmlListProperty<AsemanViewportItem> *p, AsemanViewportItem *v);
    static int count(QQmlListProperty<AsemanViewportItem> *p);
    static AsemanViewportItem *at(QQmlListProperty<AsemanViewportItem> *p, int idx);
    static void clear(QQmlListProperty<AsemanViewportItem> *p);

private:
    Private *p;
    std::optional<bool> mPrimaryViewport;
};

class AsemanViewportController;
class AsemanViewportAttechedProperty : public QObject {
    Q_OBJECT
    Q_PROPERTY(QObject* controller READ controller NOTIFY controllersChanged)
    Q_PROPERTY(QList<QObject *> allControllers READ allControllers NOTIFY controllersChanged)
    Q_PROPERTY(AsemanViewport* viewport READ viewport NOTIFY controllersChanged)
    Q_PROPERTY(AsemanViewport* primaryViewport READ primaryViewport NOTIFY controllersChanged)

public:
    AsemanViewportAttechedProperty(QObject *parent);
    virtual ~AsemanViewportAttechedProperty();

    QObject *controller() const;
    QList<QObject *> allControllers() const;
    AsemanViewport *viewport() const;
    AsemanViewport *primaryViewport() const;

    static AsemanViewport *viewport(QObject *obj, bool primary = false);

Q_SIGNALS:
    void controllersChanged();
};

QML_DECLARE_TYPEINFO(AsemanViewport, QML_HAS_ATTACHED_PROPERTIES)

typedef AsemanViewport QAsemanViewport;

#endif // ASEMANVIEWPORT_H
