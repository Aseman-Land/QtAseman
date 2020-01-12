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
/*!
    \class AsemanEncrypter
    \brief Provides encrypt and decrypt API based on the Serpent32 and CFB encrypt method.
    It's based on the SimpleQtCryptor library.

    \reentrant
    \ingroup AsemanCore
 */

/*!
    \fn AsemanEncrypter::keyChanged
    This signal emits when key value changed.
    \sa count
 */

#include "asemanencrypter.h"


/*!
    Encrypt \a data using serpent32 algorithm and return encrypted data.
    \param data data to encrypt
    \return encrypted data
    \sa setKey
 */
QByteArray AsemanEncrypter::encrypt(const QByteArray &data)
{
    QByteArray result;
    AsemanSimpleQtCryptor::Encryptor enc( _key, AsemanSimpleQtCryptor::SERPENT_32, AsemanSimpleQtCryptor::ModeCFB, AsemanSimpleQtCryptor::NoChecksum );
    if(enc.encrypt( data, result, true ) == AsemanSimpleQtCryptor::NoError)
        return result;
    else
        return data;
}


/*!
    Decrypt \a data using serpent32 algorithm and return decrypted data.
    \param data data to decrypt
    \return Decrypted data
    \sa setKey
 */
QByteArray AsemanEncrypter::decrypt(const QByteArray &data)
{
    QByteArray result;
    AsemanSimpleQtCryptor::Decryptor dec( _key, AsemanSimpleQtCryptor::SERPENT_32, AsemanSimpleQtCryptor::ModeCFB );
    if(dec.decrypt( data, result, true ) == AsemanSimpleQtCryptor::NoError)
        return result;
    else
        return QByteArray();
}


/*!
    Sets key parametrs to \a key argument that using for password of the
    encryption or decryption operation.
    \param key key of the encrypt/decrypt
    \sa key
    \sa encrypt
 */
void AsemanEncrypter::setKey(const QString &key)
{
    if(_keyStr == key)
        return;

    _keyStr = key;
    _key = QSharedPointer<AsemanSimpleQtCryptor::Key>(new AsemanSimpleQtCryptor::Key(_keyStr));
    Q_EMIT keyChanged();
}

/*!
    Return the key value, used for the encrypt/descrupt password.
    \return key value
    \sa setKey
 */
QString AsemanEncrypter::key() const
{
    return _keyStr;
}
