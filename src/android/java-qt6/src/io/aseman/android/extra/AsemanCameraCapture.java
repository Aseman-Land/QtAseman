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

package io.aseman.android.extra;

import io.aseman.android.AsemanApplication;
import io.aseman.android.AsemanActivity;
import io.aseman.android.AsemanService;

import android.os.Bundle;
import android.content.Context;
import android.content.ContentResolver;
import android.provider.Settings;
import android.util.Log;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.WindowManager;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.hardware.Camera.PictureCallback;
import android.os.Environment;
import java.util.HashMap;
import java.io.IOException;
import java.io.File;
import java.io.FileOutputStream;
import java.util.List;
import java.util.Locale;
import java.util.Date;
import java.util.TimerTask;
import java.util.Timer;
import java.lang.Runnable;
import java.text.SimpleDateFormat;
import android.os.Handler;

public class AsemanCameraCapture
{
    private static final String TAG = "AsemanCameraCapture";

    public native void _imageCaptured(int id, String path);

    public void capture(final int id, final String path, final boolean frontCamera) {
        Handler mainHandler = new Handler(getContext().getMainLooper());
        Runnable myRunnable = new Runnable() {
            @Override
            public void run() {
                try {
                    takePhoto(id, path,
                              frontCamera? Camera.CameraInfo.CAMERA_FACING_FRONT :
                                           Camera.CameraInfo.CAMERA_FACING_BACK);
                } catch (Exception e) {
                    _imageCaptured(id, "");
                }
            }
        };
        mainHandler.post(myRunnable);
    }

    public static Context getContext() {
        if(AsemanActivity.getActivityInstance() != null)
            return AsemanActivity.getActivityInstance();
        else
        if(AsemanService.getServiceInstance() != null)
            return AsemanService.getServiceInstance();
        else
            return AsemanApplication.getAppContext();
    }

    private void takePhoto(final int actionId, final String path, final int cameraType) {
        Context context = getContext();
        final SurfaceView view = new SurfaceView(context);
        final Camera camera = openCamera(cameraType);
        if(camera == null) {
            camera.release();
            _imageCaptured(actionId, "");
            return;
        }

        Log.d(TAG, "Opened camera");

        SurfaceHolder holder = view.getHolder();
        holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

        holder.addCallback(new Callback() {
            @Override
            //The preview must happen at or after this point or takePicture fails
            public void surfaceCreated(SurfaceHolder holder) {

                try {
                    camera.setPreviewDisplay(holder);
                } catch (Exception e) {
                    if (camera != null)
                        camera.release();
                    _imageCaptured(actionId, "");
                    throw new RuntimeException(e);
                }

                Log.d(TAG, "Started preview");
                Timer timer = new Timer();
                timer.schedule( new TimerTask() {
                    @Override
                    public void run() {
                        try {
                            camera.takePicture(null, null, new PictureCallback() {
                                @Override
                                public void onPictureTaken(byte[] data, Camera camera) {
                                    Log.d(TAG, "Took picture");
                                    savePicture(data, path);
                                    camera.release();
                                    _imageCaptured(actionId, path);
                                }
                            });
                        } catch (Exception e) {
                            if (camera != null)
                                camera.release();
                            _imageCaptured(actionId, "");
                            throw new RuntimeException(e);
                        }
                    }
                } , 3000);
            }

            @Override public void surfaceDestroyed(SurfaceHolder holder) {}
            @Override public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {}
        });

        WindowManager wm = (WindowManager)context
            .getSystemService(Context.WINDOW_SERVICE);
        WindowManager.LayoutParams params = new WindowManager.LayoutParams(
                1, 1, //Must be at least 1x1
                WindowManager.LayoutParams.TYPE_SYSTEM_OVERLAY,
                0,
                //Don't know if this is a safe default
                PixelFormat.UNKNOWN);

        //Don't set the preview visibility to GONE or INVISIBLE
        wm.addView(view, params);
    }

    /** null if unable to save the file */
    public boolean savePicture(byte[] data, String filePath) {
        try {
            File pictureFile = new File(filePath);

            FileOutputStream fos = new FileOutputStream(pictureFile);
            fos.write(data);
            fos.close();

            return true;
        } catch (Exception e) {
            return false;
        }
    }

    private Camera openCamera(final int type) {
        int cameraCount = 0;
        Camera cam = null;
        Camera.CameraInfo cameraInfo = new Camera.CameraInfo();
        cameraCount = Camera.getNumberOfCameras();

        boolean typeFounded = false;
        for (int camIdx = 0; camIdx < cameraCount; camIdx++) {
            Camera.getCameraInfo(camIdx, cameraInfo);
            if (cameraInfo.facing == type) {
                typeFounded = true;
                try {
                    cam = Camera.open(camIdx);
                } catch (RuntimeException e) {
                    Log.e(TAG, "Camera failed to open: " + e.getLocalizedMessage());
                }
            }
        }
        if(!typeFounded) {
            Log.d(TAG, "Can't find requested camera. Try to open default camera.");
            try {
                cam = Camera.open();
            } catch (RuntimeException e) {
                Log.e(TAG, "Default camera failed to open: " + e.getLocalizedMessage());
            }
        }

        return cam;
    }
}
