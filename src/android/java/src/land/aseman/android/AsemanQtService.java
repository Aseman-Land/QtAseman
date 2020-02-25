/*
    Copyright (c) 2016, BogDan Vatra <bogdan@kde.org>
    Contact: http://www.qt.io/licensing/

    Commercial License Usage
    Licensees holding valid commercial Qt licenses may use this file in
    accordance with the commercial license agreement provided with the
    Software or, alternatively, in accordance with the terms contained in
    a written agreement between you and The Qt Company. For licensing terms
    and conditions see http://www.qt.io/terms-conditions. For further
    information use the contact form at http://www.qt.io/contact-us.

    BSD License Usage
    Alternatively, this file may be used under the BSD license as follows:
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

package land.aseman.android;

import android.app.Service;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.IBinder;
import android.app.PendingIntent;
import android.app.Notification;
import android.content.res.Resources;
import land.aseman.android.AsemanActivity;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.res.Resources;
import android.content.Context;
import android.app.NotificationChannel;
import android.graphics.Color;
import android.support.annotation.RequiresApi;
import android.os.Build.VERSION_CODES;
import android.os.Build;

import org.qtproject.qt5.android.bindings.QtService;

public class AsemanQtService extends QtService {

    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static AsemanQtService m_instance = null;

    public static AsemanQtService getServiceInstance() {
        return AsemanQtService.m_instance;
    }

    @Override
    public void onCreate() {
        m_instance = this;
        super.onCreate();
    }

    @RequiresApi(Build.VERSION_CODES.O)
    public String createNotificationChannel(String channelId ,String channelName){
        NotificationChannel chan = new NotificationChannel(channelId,
                channelName, NotificationManager.IMPORTANCE_NONE);
        chan.setLightColor(Color.BLUE);
        chan.setLockscreenVisibility(Notification.VISIBILITY_PRIVATE);
        NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        manager.createNotificationChannel(chan);
        return channelId;
    }

    public boolean startForeground(int id, String title, String msg, String iconPath, String icon, String channelId) {
        Intent notificationIntent = new Intent(this, AsemanActivity.class);
        PendingIntent pendingIntent =
                PendingIntent.getActivity(this, 0, notificationIntent, PendingIntent.FLAG_UPDATE_CURRENT);

        Resources R = getResources();

        Notification.Builder builder = new Notification.Builder(this);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) builder.setChannelId(channelId);
        Notification notification =
            builder
            .setContentTitle(title)
            .setContentText(msg)
            .setSmallIcon(R.getIdentifier(icon, iconPath, getPackageName()))
            .setContentIntent(pendingIntent)
            .build();

        startForeground(id, notification);
        return true;
    }

    public boolean startNotification(int id, String title, String body, String iconPath, String icon, String channelId, boolean sound, boolean vibrate)
    {
        Resources R = getResources();
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
        }

        Intent notificationIntent = new Intent(this, AsemanActivity.class);
        PendingIntent pendingIntent =
                PendingIntent.getActivity(this, 0, notificationIntent, PendingIntent.FLAG_UPDATE_CURRENT);

        Notification.Builder builder = new Notification.Builder(this);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) builder.setChannelId(channelId);
        Notification notification =
             builder
            .setContentTitle(title)
            .setContentText(body)
            .setSmallIcon(R.getIdentifier(icon, iconPath, getPackageName()))
            .setContentIntent(pendingIntent)
            .setAutoCancel(true)
            .build();

        if(sound) notification.defaults |= Notification.DEFAULT_SOUND;
        if(vibrate) notification.defaults |= Notification.DEFAULT_VIBRATE;

        m_notificationManager.notify(id, notification);
        return true;
    }

    public boolean stopNotification(int id)
    {
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
        }
        m_notificationManager.cancel(id);
        return true;
    }
}
