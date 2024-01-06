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

#ifndef ASEMANJAVALAYER_H
#define ASEMANJAVALAYER_H

#include <QObject>

#include "asemancore_global.h"

class AsemanJavaLayerPrivate;
class LIBQTASEMAN_CORE_EXPORT AsemanJavaLayer : public QObject
{
    Q_OBJECT
    Q_ENUMS(ImportanceTypes)

public:
    AsemanJavaLayer();
    virtual ~AsemanJavaLayer();

    enum ImportanceTypes {
        ImportanceDefault = 3,
        ImportanceHigh = 4,
        ImportanceLow = 2,
        ImportanceMax = 5,
        ImportanceMin = 1,
        ImportanceNone = 0,
    };

    static AsemanJavaLayer *instance();

    bool sharePaper( const QString & title, const QString & msg );
    bool shareFile( const QString & path, const QString & type );
    bool openFile( const QString & path, const QString & type );
    bool startCamera( const QString & output );
    bool callNumber( const QString & number );
    bool getOpenPictures();

    bool transparentStatusBar();
    bool setTransparentStatusBar(bool stt);

    bool transparentNavigationBar();
    bool setTransparentNavigationBar(bool stt);

    int densityDpi();
    int screenSizeWidth();
    int screenSizeHeight();
    int getSizeName();
    int statusBarHeight();
    int navigationBarHeight();
    bool isTablet();
    qreal density();

    QString packageName();
    QString deviceName();
    QString deviceId();

    QRect keyboardRect();

    QString getLastImages(qint32 offset, qint32 count);
    QString getContactList();

    void setKeepScreenOn(bool stt);

public Q_SLOTS:
    void reloadBuffer();
    bool startService();
    bool stopService();
    bool killService(const QString &serviceName);

    bool startQtService();
    bool stopQtService();

    bool startForeground(qint32 id, const QString &title, const QString &msg, const QString &iconPath, const QString &icon, const QString &channelId);
    bool stopForeground(bool removeNotification);
    bool startNotification(qint32 id, const QString &title, const QString &msg, const QString &iconPath, const QString &icon, const QString &channelId, bool sound = false, bool vibrate = false);
    bool stopNotification(qint32 id);
    QString createNotificationChannel(const QString &channelId ,const QString &channelName, int importance = ImportanceLow);

Q_SIGNALS:
    void incomingShare( const QString & title, const QString & msg );
    void incomingImage( const QString & path );
    void deepLinkReceived(const QString &link);
    void selectImageResult( const QString & path );
    void keyboardVisiblityChanged(qint32 height);
    void activityPaused();
    void activityStopped();
    void activityResumed();
    void activityStarted();
    void activityRestarted();
    void activityDestroyed();

private Q_SLOTS:
    void load_buffer();
    void registerObject();

protected:
    void setImplemented(bool stt);

private:
    AsemanJavaLayerPrivate *p;
};

typedef AsemanJavaLayer QAsemanJavaLayer;

#endif // ASEMANJAVALAYER_H
