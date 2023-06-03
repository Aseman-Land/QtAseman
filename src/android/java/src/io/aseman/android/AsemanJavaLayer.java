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

package io.aseman.android;

import io.aseman.android.AsemanApplication;
import io.aseman.android.AsemanActivity;
import io.aseman.android.AsemanQtService;

import org.qtproject.qt5.android.bindings.QtService;

import android.util.Log;
import android.content.Intent;
import android.content.Context;
import android.app.Activity;
import android.net.Uri;
import android.util.DisplayMetrics;
import android.provider.MediaStore;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.text.TextUtils;
import android.view.WindowManager;
import android.os.Build;
import android.content.res.Configuration;
import android.view.View;
import android.view.Window;
import android.graphics.Rect;
import android.provider.Settings.Secure;
import java.lang.Runnable;
import android.os.Handler;
import android.database.Cursor;
import android.provider.ContactsContract;
import android.content.ContentResolver;
import androidx.core.content.FileProvider;

import java.io.File;
import java.io.InputStream;
import java.io.FileOutputStream;

import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.ActivityManager ;
import android.os.Process;
import java.util.List;
import java.util.Iterator;

import org.json.JSONArray;
import org.json.JSONObject;

//import com.google.android.gms.auth.api.signin.GoogleSignInOptions;

public class AsemanJavaLayer
{
    private static native void _sendNote( String title, String msg );
    private static native void _sendImage( String path );
    private static native void _sendDeepLink(String link);
    private static native void _activityPaused();
    private static native void _activityStopped();
    private static native void _activityResumed();
    private static native void _activityStarted();
    private static native void _activityRestarted();
    private static native void _activityDestroyed();
    private static native void _selectImageResult( String path );
    private static native void _keyboardVisiblityChanged(int height);
    private static boolean implemented = false;

    public AsemanJavaLayer() {
    }

    public static void activityPaused(){
        if(implemented)
            _activityPaused();
    }

    public static void activityStopped(){
        if(implemented)
            _activityStopped();
    }

    public static void activityResumed(){
        if(implemented)
            _activityResumed();
    }

    public static void activityStarted(){
        if(implemented)
            _activityStarted();
    }

    public static void activityRestarted(){
        if(implemented)
            _activityRestarted();
    }

    public static void activityDestroyed(){
        if(implemented)
            _activityDestroyed();
    }

    public static void keyboardVisiblityChanged(int height){
        if(implemented)
            _keyboardVisiblityChanged(height);
    }

    public static void sendDeepLink(String link){
        if(implemented)
            _sendDeepLink(link);
    }

    public static void sendNote( String title, String msg ) {
        if( title == null )
            title = "";
        if( msg == null )
            msg = "";

        if(implemented)
            _sendNote(title,msg);
    }

    public static void setKeepScreenOn(boolean status) {
        final boolean fstatus = status;
        final AsemanActivity activtiy = AsemanActivity.getActivityInstance();
        Handler mainHandler = new Handler(activtiy.getMainLooper());
        Runnable myRunnable = new Runnable() {
            @Override
            public void run() {
                activtiy.setKeepScreenOn(fstatus);
            }
        };
        mainHandler.post(myRunnable);
    }

    public static int menuHeight()
    {
        Rect r = new Rect();
        Window window = AsemanActivity.getActivityInstance().getWindow();
        View rootview = window.getDecorView();
        rootview.getWindowVisibleDisplayFrame(r);

        return r.top;
    }

    public static void sendImage( Uri data ) {
        String imagePath = "/sdcard/Aseman/tmp_input_image.jpg";

        File file = new File(imagePath);
        file.delete();

        try {
            InputStream stream = AsemanApplication.instance().getContentResolver().openInputStream(data);
            Bitmap bitmap = BitmapFactory.decodeStream(stream);
            stream.close();

            FileOutputStream out = new FileOutputStream(imagePath);
            bitmap.compress(Bitmap.CompressFormat.JPEG, 90, out);
            out.close();
        } catch(Exception e) {
            return;
        }

        if(implemented)
            _sendImage(imagePath);
    }

    public static void selectImageResult( String path ) {
        if( path == null )
            path = "";

        if(implemented)
            _selectImageResult(path);
    }

    public String packageName()
    {
        Context oContext;
        oContext = AsemanApplication.getAppContext();
        return oContext.getPackageName();
    }

    public String deviceName() {
        String manufacturer = Build.MANUFACTURER;
        String model = Build.MODEL;
        if (model.startsWith(manufacturer)) {
            return capitalize(model);
        } else {
            return capitalize(manufacturer) + " " + model;
        }
    }

    boolean setImplemented(boolean stt) {
        implemented = stt;
        return true;
    }

    public String deviceId() {
        return Secure.getString(getContext().getContentResolver(), Secure.ANDROID_ID);
    }


    private String capitalize(String s) {
        if (s == null || s.length() == 0) {
            return "";
        }
        char first = s.charAt(0);
        if (Character.isUpperCase(first)) {
            return s;
        } else {
            return Character.toUpperCase(first) + s.substring(1);
        }
    }

    public static Context getContext() {
        if(AsemanActivity.getActivityInstance() != null)
            return AsemanActivity.getActivityInstance();
        else
        if(AsemanQtService.getServiceInstance() != null)
            return AsemanQtService.getServiceInstance();
        else
            return AsemanApplication.getAppContext();
    }

    public String getLastImages(int offset, int count)
    {
        String result = new String();
        final String[] imageColumns = { MediaStore.Images.Media._ID, MediaStore.Images.Media.DATA };
        final String imageOrderBy = MediaStore.Images.Media._ID + " DESC";
        Cursor imageCursor = getContext().getContentResolver().query(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, imageColumns, null, null, imageOrderBy);
        imageCursor.moveToFirst();
        do {
            String fullPath = imageCursor.getString(imageCursor.getColumnIndex(MediaStore.Images.Media.DATA));
            File imageFile = new File(fullPath);
            if (imageFile.canRead() && imageFile.exists()) {
                offset--;
                if(offset >= 0) {
                    imageCursor.moveToNext();
                    continue;
                }

                result = result + fullPath + "\n";
                count--;
                if(count <= 0)
                break;
            }
        } while (imageCursor.moveToNext());

        return result;
    }

    boolean killService(String serviceName)
    {
        Context oContext;
        oContext = AsemanApplication.getAppContext();
        ActivityManager am = (ActivityManager) oContext.getSystemService(oContext.ACTIVITY_SERVICE);
        List<RunningAppProcessInfo> runningAppProcesses = am.getRunningAppProcesses();

        Iterator<RunningAppProcessInfo> iter = runningAppProcesses.iterator();

        while(iter.hasNext()){
            RunningAppProcessInfo next = iter.next();

            String pricessName = oContext.getPackageName() + serviceName;

            if(next.processName.equals(pricessName)){
                Process.killProcess(next.pid);
                break;
            }
        }

        return true;
    }

    boolean startQtService()
    {
        Context oContext;
        oContext = AsemanApplication.getAppContext();
        Intent i = new Intent(oContext, AsemanQtService.class);
        i.putExtra("name", "SurvivingwithAndroid");
        try {
            oContext.startService(i);
        } catch(Exception e) {
            return false;
        }

        return true;
    }

    boolean stopQtService()
    {
        Context oContext;
        oContext = AsemanApplication.getAppContext();
        Intent i = new Intent(oContext, AsemanQtService.class);
        try {
        oContext.stopService(i);
        } catch(Exception e) {
            return false;
        }
        return true;
    }

    boolean sharePaper( String title, String msg )
    {
        Context oContext;
        oContext = AsemanApplication.getAppContext();

        Intent intent = new Intent(Intent.ACTION_SEND);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.setType("text/plain");
        intent.putExtra(Intent.EXTRA_TEXT, msg);
        intent.putExtra(Intent.EXTRA_SUBJECT, title);

        try {
            oContext.startActivity(intent);
        } catch(Exception e) {
            return false;
        }
        return true;
    }

    boolean shareFile(String path, String type)
    {
        Context oContext;
        oContext = AsemanApplication.getAppContext();

        File file = new File(path);
        Uri photoURI = FileProvider.getUriForFile(oContext, oContext.getApplicationContext().getPackageName() + ".provider", file);

        Intent intent = new Intent(Intent.ACTION_SEND);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
        intent.setType(type);
        intent.putExtra(Intent.EXTRA_STREAM, photoURI);

        try {

            Intent new_intent = Intent.createChooser(intent , "Share Via");
            new_intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            oContext.startActivity(new_intent);

        } catch(Exception e) {
            Log.e("Share File" , "Exception:" , e);
            return false;
        }
        return true;
    }


    boolean openFile( String path, String type )
    {
        Context oContext;
        oContext = AsemanApplication.getAppContext();

        File file = new File(path);
        Uri photoURI = FileProvider.getUriForFile(oContext, oContext.getApplicationContext().getPackageName() + ".provider", file);

        Intent intent = new Intent(android.content.Intent.ACTION_VIEW);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
        intent.setType(type);
        intent.setDataAndType(photoURI,type);

        try {
            oContext.startActivity(intent);
        } catch(Exception e) {
            Log.e("Open File" , "Exception:" , e);
            return false;
        }
        return true;
    }

    DisplayMetrics getMetrics()
    {
        DisplayMetrics dm = new DisplayMetrics();
        try {
            AsemanActivity.getActivityInstance().getWindowManager().getDefaultDisplay().getMetrics(dm);
        } catch(Exception e) {
            return dm;
        }
        return dm;
    }

    double lcdDpiX()
    {
        return getMetrics().densityDpi;
    }

    int densityDpi()
    {
        return getMetrics().densityDpi;
    }

    float density()
    {
        return getMetrics().density;
    }

    int screenSizeWidth()
    {
        return getMetrics().widthPixels;
    }

    int screenSizeHeight()
    {
        return getMetrics().heightPixels;
    }

    int statusBarHeight() {
        int result = 0;
        Context context = AsemanApplication.getAppContext();
        int resourceId = context.getResources().getIdentifier("status_bar_height", "dimen", "android");
        if (resourceId > 0) {
            result = context.getResources().getDimensionPixelSize(resourceId);
        }
        return result;
    }

    int navigationBarHeight() {
        int result = 0;
        Context context = AsemanApplication.getAppContext();
        int resourceId = context.getResources().getIdentifier("navigation_bar_height", "dimen", "android");
        if (resourceId > 0) {
            return context.getResources().getDimensionPixelSize(resourceId);
        }
        return 0;
    }

    boolean isTablet()
    {
        Context context = AsemanApplication.getAppContext();
        return (context.getResources().getConfiguration().screenLayout
                & Configuration.SCREENLAYOUT_SIZE_MASK)
                >= Configuration.SCREENLAYOUT_SIZE_LARGE;
    }

    int getSizeName()
    {
        Context context = AsemanApplication.getAppContext();
        int screenLayout = context.getResources().getConfiguration().screenLayout;
        screenLayout &= Configuration.SCREENLAYOUT_SIZE_MASK;

        switch (screenLayout) {
        case Configuration.SCREENLAYOUT_SIZE_SMALL:
            return 0;
        case Configuration.SCREENLAYOUT_SIZE_NORMAL:
            return 1;
        case Configuration.SCREENLAYOUT_SIZE_LARGE:
            return 2;
        case 4: // Configuration.SCREENLAYOUT_SIZE_XLARGE is API >= 9
            return 3;
        default:
            return -1;
        }
    }

    boolean getOpenPictures()
    {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("image/*");

        try {
            AsemanActivity.getActivityInstance().startActivityForResult(intent, AsemanActivity.SELECT_IMAGE);
        } catch(Exception e) {
            return false;
        }

        return true;
    }

    boolean startCamera( String output )
    {
        Intent intent = new Intent("android.media.action.IMAGE_CAPTURE");
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(new File(output)));

        try {
            AsemanActivity.getActivityInstance().startActivityForResult(intent, 0);
        } catch(Exception e) {
            return false;
        }
        return true;
    }

    boolean callNumber( String number )
    {
        Intent intent = new Intent(Intent.ACTION_CALL);
        intent.setData(Uri.parse("tel:" + number));

        try {
            AsemanActivity.getActivityInstance().startActivity(intent);
        } catch(Exception e) {
            return false;
        }
        return true;
    }

    boolean transparentStatusBar()
    {
        return AsemanActivity.getActivityInstance().transparentStatusBar();
    }

    boolean transparentNavigationBar()
    {
        return AsemanActivity.getActivityInstance().transparentNavigationBar();
    }

    boolean release()
    {
        return true;
    }

    boolean setTransparentNavigationBar(boolean stt)
    {
        final boolean _stt = stt;
        Handler mainHandler = new Handler(AsemanActivity.getActivityInstance().getMainLooper());
        Runnable myRunnable = new Runnable() {
            @Override
            public void run() {
                AsemanActivity.getActivityInstance().setTransparentNavigationBar(_stt);
            }
        };
        mainHandler.post(myRunnable);
        return true;
    }

    boolean setTransparentStatusBar(boolean stt)
    {
        final boolean _stt = stt;
        Handler mainHandler = new Handler(AsemanActivity.getActivityInstance().getMainLooper());
        Runnable myRunnable = new Runnable() {
            @Override
            public void run() {
                AsemanActivity.getActivityInstance().setTransparentStatusBar(_stt);
            }
        };
        mainHandler.post(myRunnable);
        return true;
    }

    public String createNotificationChannel(String channelId ,String channelName, int importance){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            if(AsemanActivity.getActivityInstance() != null)
                return AsemanActivity.getActivityInstance().createNotificationChannel(channelId, channelName, importance);
            else
            if(AsemanQtService.getServiceInstance() != null)
                return AsemanQtService.getServiceInstance().createNotificationChannel(channelId, channelName, importance);
        } else {
            return "";
        }
        return channelId;
    }

    boolean startForeground(int id, String title, String body, String iconPath, String icon, String channelId)
    {
        if(AsemanQtService.getServiceInstance() != null)
            return AsemanQtService.getServiceInstance().startForeground(id, title, body, iconPath, icon, channelId);
        return false;
    }

    boolean stopForeground(boolean removeNotification)
    {
        if(AsemanQtService.getServiceInstance() != null) {
            AsemanQtService.getServiceInstance().stopForeground(removeNotification);
            return true;
        }
        return false;
    }

    boolean startNotification(int id, String title, String body, String iconPath, String icon, String channelId, boolean sound, boolean vibrate)
    {
        if(AsemanActivity.getActivityInstance() != null)
            return AsemanActivity.getActivityInstance().startNotification(id, title, body, iconPath, icon, channelId, sound, vibrate);
        else
        if(AsemanQtService.getServiceInstance() != null)
            return AsemanQtService.getServiceInstance().startNotification(id, title, body, iconPath, icon, channelId, sound, vibrate);
        return false;
    }

    boolean stopNotification(int id)
    {
        if(AsemanActivity.getActivityInstance() != null)
            return AsemanActivity.getActivityInstance().stopNotification(id);
        else
        if(AsemanQtService.getServiceInstance() != null)
            return AsemanQtService.getServiceInstance().stopNotification(id);
        return false;
    }

    String getContactList() {
        Context ctx = getContext();
        ContentResolver cr = ctx.getContentResolver();
        Cursor cur = cr.query(ContactsContract.Contacts.CONTENT_URI,
                null, null, null, null);

        JSONArray jsonArray = new JSONArray();

        if ((cur != null ? cur.getCount() : 0) > 0) {
            while (cur != null && cur.moveToNext()) {
                String id = cur.getString(
                        cur.getColumnIndex(ContactsContract.Contacts._ID));
                String name = cur.getString(cur.getColumnIndex(
                        ContactsContract.Contacts.DISPLAY_NAME));

                if (cur.getInt(cur.getColumnIndex(
                        ContactsContract.Contacts.HAS_PHONE_NUMBER)) > 0) {
                    Cursor pCur = cr.query(
                            ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
                            null,
                            ContactsContract.CommonDataKinds.Phone.CONTACT_ID + " = ?",
                            new String[]{id}, null);
                    while (pCur.moveToNext()) {
                        String phoneNo = pCur.getString(pCur.getColumnIndex(
                                ContactsContract.CommonDataKinds.Phone.NUMBER));

                        JSONObject obj = new JSONObject();
                        try {
                            obj.put("id", id);
                            obj.put("name", name);
                            obj.put("phone", phoneNo);

                            jsonArray.put(obj);
                        } catch (Exception e) {
                        }
                    }
                    pCur.close();
                }
            }
        }
        if(cur!=null){
            cur.close();
        }

        return jsonArray.toString();
    }

//    public static String getUniquePsuedoID() {
//        String m_szDevIDShort = "35" + (Build.BOARD.length() % 10) + (Build.BRAND.length() % 10) + (Build.CPU_ABI.length() % 10) + (Build.DEVICE.length() % 10) + (Build.MANUFACTURER.length() % 10) + (Build.MODEL.length() % 10) + (Build.PRODUCT.length() % 10);
//        String serial = null;
//        try {
//            serial = android.os.Build.class.getField("SERIAL").get(null).toString();
//            return new UUID(m_szDevIDShort.hashCode(), serial.hashCode()).toString();
//        } catch (Exception exception) {
//            serial = "3077139d-9dde-4ee1-afb5-ecc43f5d1524";
//        }
//        return new UUID(m_szDevIDShort.hashCode(), serial.hashCode()).toString();
//    }

//    boolean googleSignIn(String clientId)
//    {
//        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
//            .requestIdToken(getString(clientId))
//            .build();
//    }
}
