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

#ifndef ASEMANENCRYPTER_H
#define ASEMANENCRYPTER_H

#include "asemansimpleqtcryptor.h"

#include "asemancore_global.h"

class LIBQTASEMAN_CORE_EXPORT AsemanEncrypter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)

public:
    AsemanEncrypter(QObject *parent = 0): QObject(parent){}
    virtual ~AsemanEncrypter(){}

    void setKey(const QString &key);
    QString key() const;

public Q_SLOTS:
    QByteArray encrypt(const QByteArray &data);
    QByteArray decrypt(const QByteArray &data);

Q_SIGNALS:
    void keyChanged();

private:
    QString _keyStr;
    QSharedPointer<AsemanSimpleQtCryptor::Key> _key;
};

#endif // ASEMANENCRYPTER_H
