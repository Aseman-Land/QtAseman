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

#ifndef ASEMANTOOLS_H
#define ASEMANTOOLS_H

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QDateTime>
#include <QSize>
#include <QStringList>
#include <QUrl>

#define ASEMAN_TYPE_NAME(TYPE) #TYPE

#include "asemangui_global.h"

class AsemanToolsPrivate;
class LIBQTASEMAN_GUI_EXPORT AsemanTools : public QObject
{
    Q_OBJECT
public:
    AsemanTools(QObject *parent = 0);
    virtual ~AsemanTools();

    static void imageResize(const QString &path, const QSize &size, const QString &dest, QObject *base, std::function<void(bool)> callback);

public Q_SLOTS:
    static void debug( const QVariant & var );

    static QDateTime currentDate();
    static QString dateToMSec(const QDateTime &dt);
    static QDateTime mSecToDate(const QString &ms);
    static qint64 dateToSec(const QDateTime &dt);
    static QDateTime dateFromSec(qint64 date);
    static QString dateToString(const QDateTime &dt, const QString &format = QString());
    static QDateTime datefromString(const QString &dt, const QString &format = QString());
    static QDate dateAddDays(const QDate &date, int days);

    static QStringList toStringList(const QVariant &value);
    static QVariantMap toVariantMap(const QVariant &value);
    static QVariantList toVariantList(const QVariant &value);

    static QString byteArrayToString(const QVariant &value);

    static QByteArray compress(const QByteArray &data, int level = -1);
    static QByteArray uncompress(const QByteArray &data);

    QVariant bytesToVariant(const QByteArray &data);
    QByteArray variantToBytes(const QVariant &var);

    static QString fileName( const QString & path );
    static QString fileSuffix( const QString & path );
    static QString fileMime(const QString &path);
    static QString fileParent( const QString & path );
    static QString readText( const QString & path );
    static bool writeText(const QString & path , const QString &text);
    static bool fileExists(const QString & path);
    static QStringList filesOf(const QString &path);

    static QSize imageSize(const QString &path);

    static bool writeFile(const QString &path, const QVariant &data, bool compress = false);
    static QByteArray readFile(const QString &path, bool uncompress = false);

    static QString className(QObject *obj);

    static QStringList stringLinks(const QString &str);
    static QString stringRemove(QString str, const QString &text, bool regExp = false);
    static QString stringReplace(QString str, const QString &text, const QString &replace, bool regExp = false);
    static QVariantList stringRegExp(QString str, const QString &regExp, bool minimal = true);

    static QUrl stringToUrl(const QString &path);
    static QString urlToLocalPath(const QUrl &url);

    static QString qtVersion();
    static QString aboutAseman();

    static void deleteItemDelay( QObject *o, int ms );

    static qreal colorHue( const QColor & clr );
    static qreal colorLightness( const QColor & clr );
    static qreal colorSaturation( const QColor & clr );

    static void mkDir(const QString &dir);

    static QVariantMap colorHsl( const QColor & clr );

    static bool createVideoThumbnail(const QString &video, const QString &output, QString ffmpegPath = QString());

    static QString translateNumbers( QString input );
    static QString trNums(QString input);
    static QString passToMd5( const QString & pass );
    static QString md5(const QString & str );
    static QString createUuid();

    static QString htmlToPlaintText(const QString &html);

    static void copyDirectory( const QString & src, const QString & dst );
    static bool copy( const QString & src, const QString & dst );
    static bool rename( const QString & src, const QString & dst );
    static void deleteFile(const QString &file);
    static void clearDirectory(const QString &dir);

    static void setProperty( QObject *obj, const QString & property, const QVariant & v );
    static QVariant property( QObject *obj, const QString & property );

    static Qt::LayoutDirection directionOf( const QString & str );
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
                                                                const QVariant & v9 = QVariant() );

private:
    AsemanToolsPrivate *p;
};

#endif // ASEMANTOOLS_H
