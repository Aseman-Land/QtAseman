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

/*
 *  SimpleQtCryptor is an encryption library for Qt.
 *
 *  Copyright (C) 2010,2011 Gunnar Thorburn
 *
 *  SimpleQtCrypto is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ParrotShare is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// remove this line if you do not want RC5
#define WITHRC5

// this line enables the print serpent_sbox.h functionality
// #define WITH_SERPENT_PRINT_SBOX_H

// remove this line if you want a slightly smaller and much slower
// binary (serpent only)
#define WITH_SERPENT_INCLUDE_FAST_SBOX

#ifndef ASEMANSIMPLEQTCRYPTOR_H
#define ASEMANSIMPLEQTCRYPTOR_H

#include <QtGlobal>
#include <QByteArray>
#include <QSharedPointer>
#include <QObject>

#include "asemancore_global.h"

class QString;

namespace AsemanSimpleQtCryptor {

class Encryptor;
class Decryptor;
class LayerMode;
class CFB;
class CBC;

enum Algorithm {
    NoAlgorithm = 0,
    DetectAlgorithm,
#ifdef WITHRC5
    RC5_FAST_32_20,
    RC5_32_32_20,
    RC5_64_32_20,
#endif
    SERPENT_32
};

enum Mode {
    NoMode = 0,
    DetectMode,
    ModeCBC,
    ModeCFB
};

enum Checksum {
    NoChecksum = 0,
    DetectChecksum,
    ChecksumSoft,
    ChecksumHard
};

enum Error {
    NoError = 0,
    // ErrorNoKey,
    ErrorNoAlgorithm,
    ErrorNoMode,
    ErrorInvalidKey,
    ErrorNotEnoughData,
    ErrorModeNotImplemented,
    ErrorAlgorithmNotImplemented,
    ErrorChecksumNotImplemented,
    ErrorAlreadyError
};


enum State {
    StateReset = 0,
    StateOn,
    StateError
};


class Info {
public:
    static Algorithm fastRC5();
    static QString errorText(Error e);
};



class LIBQTASEMAN_CORE_EXPORT Key : public QObject {
    Q_OBJECT
public:
    Key();
    Key(const QByteArray &key);
    Key(const QString &key);
    virtual ~Key();

    // not for use by end application
#ifdef WITHRC5
    void expandKeyRc532();
    void expandKeyRc564();
#endif
    void expandKeySerpent();

    // variables
    QByteArray key;
#ifdef WITHRC5
    QByteArray keyRc5;
    quint32 *s32;
    quint64 *s64;
#endif
    QByteArray keySerpent;
    quint32 *serpent;
private:
    QByteArray resizeKey(int ks);
};


/*
 * About end and reset()
 *  - If you encrypt/decrypt a piece of data (ie a file) in one chunk
 *    make sure end=true. After this, you can use the same LayerMode
 *    object to encrypt/decrypt something else
 *  - If you encrypt/decrypt i piece of data (ie a file or a network
 *    conversation) in more than one chunk, make sure the last chunk
 *    only has end=true.
 *  - Call reset() only if you want to start over after an error
 *    (typically ErrorInvalidKey or ErrorNotEnoughData);
 *    as long as you use end=true, you never need to reset().
 */
class Encryptor : public QObject {
    Q_OBJECT
public:
    Encryptor(QSharedPointer<Key> k, Algorithm a, Mode m, Checksum c);
    virtual ~Encryptor();   
    Error encrypt(const QByteArray &plain, QByteArray &cipher, bool end);
    void reset();
private:
    QSharedPointer<Key> key;
    Algorithm algorithm;
    Mode mode;
    Checksum checksum;
    State state;
    LayerMode *modex;
};


// will attempt all different combinations, and give you a
// Decryptor back to decrypt rest of data or more messages
// from the same source
class DecryptorWizardEntry;
class DecryptorWizard {
public:
    DecryptorWizard();
    DecryptorWizard(QSharedPointer<Key> k, Algorithm a = DetectAlgorithm, Mode m = DetectMode);
    virtual ~DecryptorWizard();

    void addParameters(QSharedPointer<Key> k, Algorithm a = DetectAlgorithm, Mode m = DetectMode);

    Error decrypt(const QByteArray &cipher, QByteArray &plain, QSharedPointer<Decryptor> &decryptor, bool end = false);
    Error decryptToEnd(const QByteArray &cipher, QByteArray &plain);
private:
    QList<DecryptorWizardEntry*> entries;
};



class Decryptor : public QObject {
    Q_OBJECT
public:
    Decryptor(QSharedPointer<Key> k, Algorithm a, Mode m);
    virtual ~Decryptor();
    Error decrypt(const QByteArray &cipher, QByteArray &plain, bool end);
    void reset();
    Checksum getChecksumType();
private:
    QSharedPointer<Key> key;
    Algorithm algorithm;
    Mode mode;
    State state;
    Checksum checksum;
    LayerMode *modex;
};



class InitializationVector {
public:
    static QByteArray getVector8();
    static QByteArray getVector16();
    static void initiate();
};



/* *** Layer 2 : mode layer *** */

/*
 * A single LayerMode object can handle only one encrypt OR decrypt
 * at a time
 */
class LayerMode {
public:
    virtual QByteArray encrypt(const QByteArray plain, bool end) = 0;
    virtual QByteArray decrypt(const QByteArray cipher, bool end) = 0;
    virtual void reset() = 0;
    virtual ~LayerMode() {};
};

class CFB : public LayerMode {
public:
    CFB(QSharedPointer<Key> k, Algorithm a);
    virtual ~CFB();
    QByteArray encrypt(const QByteArray plain, bool end = false) Q_DECL_OVERRIDE;
    QByteArray decrypt(const QByteArray cipher, bool end = false) Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;
private:
    QByteArray buffer;
    int bufferpos;
    Algorithm algorithm;
    QSharedPointer<Key> key;
};

class CBC : public LayerMode {
public:
    CBC(QSharedPointer<Key> k, Algorithm a);
    virtual ~CBC();
    QByteArray encrypt(const QByteArray plain, bool end) Q_DECL_OVERRIDE;
    QByteArray decrypt(const QByteArray cipher, bool end) Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;
private:
    QByteArray buffer;
    QByteArray cbcBuffer;
    QByteArray padHostageBuffer;
    int worksize;
    Algorithm algorithm;
    QSharedPointer<Key> key;
};


/* *** Layer 1 : block layer - experts only *** */

#ifdef WITHRC5
// input replaced by output
void rc5_32_encrypt_2w(quint32 &X1, quint32 &X2, const quint32 *s);
void rc5_64_encrypt_2w(quint64 &X1, quint64 &X2, const quint64 *s);
void rc5_32_decrypt_2w(quint32 &X1, quint32 &X2, const quint32 *s);
void rc5_64_decrypt_2w(quint64 &X1, quint64 &X2, const quint64 *s);

void rc5_32_encrypt_8b(const uchar *plain8, uchar *cipher8, const quint32 *s);
void rc5_64_encrypt_16b(const uchar *plain16, uchar *cipher16, const quint64 *s);
void rc5_32_decrypt_8b(const uchar *cipher8, uchar *plain8, const quint32 *s);
void rc5_64_decrypt_16b(const uchar *cipher16, uchar *plain16, const quint64 *s);
#endif

void serpent_encrypt_4w(quint32 &X1, quint32 &X2,
                        quint32 &X3, quint32 &X4, const quint32 *s);

void serpent_decrypt_4w(quint32 &X1, quint32 &X2,
                        quint32 &X3, quint32 &X4, const quint32 *s);

void serpent_encrypt_16b(const uchar *plain16, uchar *cipher16, const quint32 *s);
void serpent_decrypt_16b(const uchar *cipher16, uchar *plain16, const quint32 *s);

#ifdef WITH_SERPENT_PRINT_SBOX_H
void serpent_print_sbox_h();
#endif

} // namespace


#endif // ASEMANSIMPLEQTCRYPTOR_H
