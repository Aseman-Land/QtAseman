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

package land.aseman.android;

import org.qtproject.qt5.android.bindings.QtActivity;

import land.aseman.android.store.StoreManager;
import land.aseman.android.store.util.IabHelper;
import land.aseman.android.store.util.IabResult;
import land.aseman.android.store.util.Inventory;
import land.aseman.android.store.util.Purchase;
import com.android.vending.billing.IInAppBillingService;
import com.hmkcode.android.image.RealPathUtil;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Build;
import android.view.WindowManager;
import android.view.Window;
import android.view.View ;
import android.view.ViewTreeObserver ;
import android.provider.MediaStore;
import android.database.Cursor;
import android.graphics.Rect ;
import android.util.Log;
import java.util.HashMap;
import java.util.Iterator;
import android.graphics.Color;
import android.os.IBinder;
import android.content.res.Configuration;
import android.app.PendingIntent;
import android.app.Notification;
import android.content.res.Resources;
import android.app.Notification;
import android.app.NotificationManager;

//import com.google.android.gms.common.api.GoogleApiClient;
//import com.google.android.gms.common.api.GoogleSignInOptions;

public class AsemanActivity extends QtActivity
{
    static final String STORE_MANAGER_TAG = "StoreManager";
    static final int STORE_MANAGER_RC_REQUEST = 0;

    private static AsemanActivity instance;
    private int keyboardExtraHeight = 0;

    public boolean _transparentStatusBar = false;
    public boolean _transparentNavigationBar = false;
    public static final int SELECT_IMAGE = 1;

    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;

    boolean _storeHasFound;
    String _storeManagerLastPurchaseSku;
    IabHelper mStoreManagerHelper;
//    GoogleApiClient mGoogleApiClient;

    public AsemanActivity() {
        AsemanActivity.instance = this;
    }

//    public void initGoogleApiClient() {
//        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
//            .requestEmail()
//            .build();

//        // Build a GoogleApiClient with access to GoogleSignIn.API and the options above.
//        mGoogleApiClient = new GoogleApiClient.Builder(this)
//            .enableAutoManage(this, this)
//            .addApi(Auth.GOOGLE_SIGN_IN_API, gso)
//            .build();
//    }

    public static AsemanActivity getActivityInstance() {
        return AsemanActivity.instance;
    }

    public boolean transparentStatusBar() {
        return _transparentStatusBar;
    }

    public boolean transparentNavigationBar() {
        return _transparentNavigationBar;
    }

    public boolean startNotification(int id, String title, String body, String iconPath, String icon)
    {
        Resources R = getResources();
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)getSystemService(Context.NOTIFICATION_SERVICE);
        }

        Intent notificationIntent = new Intent(this, AsemanActivity.class);
        PendingIntent pendingIntent =
                PendingIntent.getActivity(this, 0, notificationIntent, PendingIntent.FLAG_UPDATE_CURRENT);

        Notification notification =
                  new Notification.Builder(this)
            .setContentTitle(title)
            .setContentText(body)
            .setSmallIcon(R.getIdentifier(icon, iconPath, getPackageName()))
            .setContentIntent(pendingIntent)
            .setAutoCancel(true)
            .build();

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

    boolean setLayoutNoLimit(boolean stt)
    {
        Window w = getWindow();
        if(stt) {
            w.setFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS, WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
            _transparentStatusBar = true;
        } else {
            w.clearFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
            _transparentStatusBar = false;
        }
        _transparentNavigationBar = false;

        return true;
    }

    boolean setStatusBarColor(int color)
    {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.KITKAT)
            return false;

//        Window w = getWindow();
//        w.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
//        w.setStatusBarColor(color);

        return true;
    }

    boolean setTransparentStatusBar(boolean stt)
    {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.KITKAT)
            return false;

        Window w = getWindow();
        if(stt) {
            w.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS, WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
            _transparentStatusBar = true;
        } else {
            w.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
            _transparentStatusBar = false;
        }

        return true;
    }

    boolean setTransparentNavigationBar(boolean stt)
    {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.KITKAT)
            return false;

        Window w = getWindow();
        if(stt) {
            w.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION, WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
            _transparentNavigationBar = true;
        } else {
            w.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
            _transparentNavigationBar = false;
        }

        return true;
    }

    public void setKeepScreenOn(boolean status) {
        Window window = getWindow();
        if (status)
            window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        else
            window.clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (resultCode == RESULT_OK) {
            if (requestCode == AsemanActivity.SELECT_IMAGE) {
                Uri selectedImageUri = data.getData();
                AsemanJavaLayer.selectImageResult( getPath(selectedImageUri) );
            }
        }

        Iterator sm_itrs = StoreManager.instances.iterator();
        while (sm_itrs.hasNext()) {
            StoreManager sm = (StoreManager)sm_itrs.next();
            if(sm != null && sm.mStoreManagerHelper != null)
                sm.mStoreManagerHelper.handleActivityResult(requestCode, resultCode, data);
        }

        super.onActivityResult(requestCode, resultCode, data);
    }

    public String getPath(Uri uri) {
        try {
            String realPath;
            // SDK < API11
            if (Build.VERSION.SDK_INT < 11)
                    realPath = RealPathUtil.getRealPathFromURI_BelowAPI11(this, uri);
            // SDK >= 11 && SDK < 19
            else if (Build.VERSION.SDK_INT < 19)
                    realPath = RealPathUtil.getRealPathFromURI_API11to18(this, uri);
            // SDK > 19 (Android 4.4)
            else
                realPath = RealPathUtil.getRealPathFromURI_API19(this, uri);
            return realPath;
        } catch(Exception e) {
            String selectedImagePath;
            String[] projection = { MediaStore.Images.Media.DATA };
            Cursor cursor = managedQuery(uri, projection, null, null, null);
            if(cursor != null){
                int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
                cursor.moveToFirst();
                selectedImagePath = cursor.getString(column_index);
            }else{
                selectedImagePath = null;
            }

            if(selectedImagePath == null){
                selectedImagePath = uri.getPath();
            }
            return selectedImagePath;
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        Window w = getWindow();
        int resID = getResources().getIdentifier("splash" , "drawable", getPackageName());
        if(resID != 0)
            w.setBackgroundDrawableResource(resID);

//        setTransparentNavigationBar(true);
        if( !setTransparentStatusBar(true) )
            setLayoutNoLimit(true);

        super.onCreate(savedInstanceState);
        final View dview = w.getDecorView();
        dview.getRootView().getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener(){
            public void onGlobalLayout(){
                  Rect r = new Rect();
                  dview.getWindowVisibleDisplayFrame(r);

                  int screenHeight = dview.getRootView().getHeight();
                  int heightDifference = screenHeight - (r.bottom - r.top);
                  if(heightDifference > screenHeight/4) {
                      AsemanJavaLayer.keyboardVisiblityChanged(heightDifference - keyboardExtraHeight);
                  } else {
                      keyboardExtraHeight = heightDifference;
                      AsemanJavaLayer.keyboardVisiblityChanged(0);
                  }
               }
         });

        checkIntent(getIntent());
    }

    @Override
    protected void onNewIntent(Intent intent)
    {
        super.onNewIntent(intent);
        checkIntent(intent);
    }

    protected void checkIntent(Intent intent)
    {
        String action = intent.getAction();
        String type = intent.getType();
        if ( !Intent.ACTION_SEND.equals(action) || type == null)
            return;

        if ("text/plain".equals(type))
            AsemanJavaLayer.sendNote(intent.getStringExtra(Intent.EXTRA_SUBJECT), intent.getStringExtra(Intent.EXTRA_TEXT) );
        else
        if("image/png".equals(type) || "image/jpeg".equals(type))
            AsemanJavaLayer.sendImage( (Uri)intent.getExtras().get(Intent.EXTRA_STREAM) );
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        AsemanJavaLayer.activityStarted();
    }

    @Override
    protected void onRestart()
    {
        super.onRestart();
        AsemanJavaLayer.activityRestarted();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        AsemanJavaLayer.activityResumed();
    }

    @Override
    protected void onPause()
    {
        AsemanJavaLayer.activityPaused();
        super.onPause();
    }

    @Override
    protected void onStop()
    {
        AsemanJavaLayer.activityStopped();
        super.onStop();
    }

    @Override
    protected void onDestroy()
    {
        AsemanJavaLayer.activityDestroyed();
        super.onDestroy();
    }
}
