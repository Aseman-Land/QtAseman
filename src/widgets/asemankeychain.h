/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ASEMANKEYCHAIN_H
#define ASEMANKEYCHAIN_H

#include <QObject>
#include <QJSValue>

#include "asemanwidgets_global.h"

class AsemanKeychainPrivate;
class LIBQTASEMAN_WIDGETS_EXPORT AsemanKeychain : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString service READ service WRITE setService NOTIFY serviceChanged)
public:
    AsemanKeychain(QObject *parent = 0);
    virtual ~AsemanKeychain();

    void setService(const QString &service);
    QString service() const;

public Q_SLOTS:
    QString read(const QString &key, const QJSValue &jsCallback = QJSValue());
    QByteArray readData(const QString &key, const QJSValue &jsCallback = QJSValue());

    bool write(const QString &key, const QString &data, const QJSValue &jsCallback = QJSValue());
    bool writeData(const QString &key, const QByteArray &data, const QJSValue &jsCallback = QJSValue());

    bool remove(const QString &key, const QJSValue &jsCallback = QJSValue());

Q_SIGNALS:
    void serviceChanged();

private:
    AsemanKeychainPrivate *p;
};

#endif // ASEMANKEYCHAIN_H
