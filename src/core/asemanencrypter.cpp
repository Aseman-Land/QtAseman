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

#include "asemanencrypter.h"

QByteArray AsemanEncrypter::encrypt(const QByteArray &data)
{
    QByteArray result;
    AsemanSimpleQtCryptor::Encryptor enc( _key, AsemanSimpleQtCryptor::SERPENT_32, AsemanSimpleQtCryptor::ModeCFB, AsemanSimpleQtCryptor::NoChecksum );
    if(enc.encrypt( data, result, true ) == AsemanSimpleQtCryptor::NoError)
        return result;
    else
        return data;
}

QByteArray AsemanEncrypter::decrypt(const QByteArray &data)
{
    QByteArray result;
    AsemanSimpleQtCryptor::Decryptor dec( _key, AsemanSimpleQtCryptor::SERPENT_32, AsemanSimpleQtCryptor::ModeCFB );
    if(dec.decrypt( data, result, true ) == AsemanSimpleQtCryptor::NoError)
        return result;
    else
        return QByteArray();
}

void AsemanEncrypter::setKey(const QString &key)
{
    if(_keyStr == key)
        return;

    _keyStr = key;
    _key = QSharedPointer<AsemanSimpleQtCryptor::Key>(new AsemanSimpleQtCryptor::Key(_keyStr));
    Q_EMIT keyChanged();
}

QString AsemanEncrypter::key() const
{
    return _keyStr;
}
