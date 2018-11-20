/*
    Copyright (C) 2018 Aseman Team
    http://aseman.co

    This file copied from AsemanServer project.
    AsemanServer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanServer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANSOCKETINTERFACE_H
#define ASEMANSOCKETINTERFACE_H

#include <QObject>
#include <QIODevice>
#include <QVariant>

#include <functional>

#include "asemannetwork_global.h"

/*!
 * \brief The AsemanSocketInterface class
 * It's an IPC (Inter process communication) interface that connect
 * two process and transfare data between them using an IODevice like
 * QLocalSocket.
 * You can call Slots from other side of the connection using call method and
 * Get results using callback or result signal. It's easy to use :)
 * Just read about IPC systems.
 */
class LIBQTASEMAN_NETWORK_EXPORT AsemanSocketInterface : public QObject
{
    Q_OBJECT
    class Private;

public:
    AsemanSocketInterface(QIODevice *device, QObject *parent = Q_NULLPTR);
    AsemanSocketInterface(QObject *destObj, QIODevice *device, QObject *parent = Q_NULLPTR);
    virtual ~AsemanSocketInterface();

    qint64 call(const QString &method, const QVariantList &args = QVariantList());
    void call(const QString &method, const QVariantList &args, std::function<void (QVariant)> callback);
    QVariant callSync(const QString &method, const QVariantList &args = QVariantList());
    void callTimer(const QString &method, const QVariantList &args, std::function<void (QVariant)> callback);

Q_SIGNALS:
    void result(qint64 id, const QVariant &result);

public Q_SLOTS:

private:
    void readyRead();
    QByteArray call(QByteArray data);
    void result(QByteArray data);
    void onResult(qint64 id, const QVariant &result);

    static QVariant call( QObject *obj, const QString & member, Qt::ConnectionType type,
                                                                const QVariant & v0 = QVariant(),
                                                                const QVariant & v1 = QVariant(),
                                                                const QVariant & v2 = QVariant(),
                                                                const QVariant & v3 = QVariant(),
                                                                const QVariant & v4 = QVariant(),
                                                                const QVariant & v5 = QVariant(),
                                                                const QVariant & v6 = QVariant(),
                                                                const QVariant & v7 = QVariant(),
                                                                const QVariant & v8 = QVariant(),
                                                                const QVariant & v9 = QVariant(),
                                                                bool *isVoid = 0);

private:
    Private *p;
};

#endif // ASEMANSOCKETINTERFACE_H
