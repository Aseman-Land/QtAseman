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

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.DataOutputStream;
import java.io.DataInputStream;
import java.lang.reflect.Field;

import dalvik.system.DexClassLoader;

import android.content.res.AssetManager;
import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.pm.PackageInfo;
import android.content.pm.ServiceInfo;
import android.content.Intent;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.os.Process;
import android.widget.Toast;

import land.aseman.android.AsemanActivity;
import land.aseman.android.AsemanServiceDelegate;
import org.qtproject.qt5.android.bindings.QtApplication;

public class AsemanService extends Service
{
    public Boolean started=false;
    private String[] m_qtLibs = null;
    private DexClassLoader m_classLoader = null;

    private static final int BUFFER_SIZE = 1024;

    private String[] m_sources = {"https://download.qt-project.org/ministro/android/qt5/qt-5.2"}; // Make sure you are using ONLY secure locations
    private String m_repository = "default";

    private ServiceInfo m_serviceInfo = null;
    protected NotificationManager m_notificationManager;
    protected Notification.Builder m_builder;
    protected PendingIntent pi;
    private static AsemanService m_instance = null;
    private String m_lib_name;

    private static final String ERROR_CODE_KEY = "error.code";
    private static final String DEX_PATH_KEY = "dex.path";
    private static final String STATIC_INIT_CLASSES_KEY = "static.init.classes";
    private static final String NATIVE_LIBRARIES_KEY = "native.libraries";
    private static final String MAIN_LIBRARY_KEY = "main.library";
    private static final String APPLICATION_PARAMETERS_KEY = "application.parameters";
    private static final String BUNDLED_LIBRARIES_KEY = "bundled.libraries";
    private static final String BUNDLED_IN_LIB_RESOURCE_ID_KEY = "android.app.bundled_in_lib_resource_id";
    private static final String BUNDLED_IN_ASSETS_RESOURCE_ID_KEY = "android.app.bundled_in_assets_resource_id";
    private static final String LOADER_CLASS_NAME_KEY = "loader.class.name";
    private static final String LIB_PATH_KEY = "lib.path";
    private static final String ENVIRONMENT_VARIABLES_KEY = "env.variable";

    public String APPLICATION_PARAMETERS = null;
    public String ENVIRONMENT_VARIABLES = "QT_USE_ANDROID_NATIVE_STYLE=1\tQT_USE_ANDROID_NATIVE_DIALOGS=1\t";

    @Override
    public void onCreate() {
        m_instance = this;

        try{
            ComponentName myService = new ComponentName(this, this.getClass());
            m_serviceInfo = getPackageManager().getServiceInfo(myService, PackageManager.GET_META_DATA);
            m_lib_name = splitCamelCase (m_serviceInfo.metaData.getString("android.app.lib_name"));
        }
        catch (Exception e) {
            e.printStackTrace();
        }

        super.onCreate();
    }

    public static AsemanService getServiceInstance() {
        return AsemanService.m_instance;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        startApp();
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {
        AsemanServiceDelegate.finishQtApplication();
        m_serviceInfo = null;
        m_instance = null;
        m_classLoader = null;
        super.onDestroy();
    }

    private void startApp(){
        if (!started){
            started = true;
//            Toast.makeText(getBaseContext(), m_lib_name + " starting", Toast.LENGTH_LONG).show();

            try{
                if (m_serviceInfo.metaData.containsKey("android.app.qt_sources_resource_id")) {
                    int resourceId = m_serviceInfo.metaData.getInt("android.app.qt_sources_resource_id");
                    m_sources = getResources().getStringArray(resourceId);
                }

                if (m_serviceInfo.metaData.containsKey("android.app.repository"))
                    m_repository = m_serviceInfo.metaData.getString("android.app.repository");

                if (m_serviceInfo.metaData.containsKey("android.app.qt_libs_resource_id")) {
                    int resourceId = m_serviceInfo.metaData.getInt("android.app.qt_libs_resource_id");
                    m_qtLibs = getResources().getStringArray(resourceId);
                }

                if (m_serviceInfo.metaData.containsKey("android.app.use_local_qt_libs")
                        && m_serviceInfo.metaData.getInt("android.app.use_local_qt_libs") == 1) {
                    ArrayList<String> libraryList = new ArrayList<String>();


                    String localPrefix = "/data/local/tmp/qt/";
                    if (m_serviceInfo.metaData.containsKey("android.app.libs_prefix"))
                        localPrefix = m_serviceInfo.metaData.getString("android.app.libs_prefix");

                    String pluginsPrefix = localPrefix;

                    boolean bundlingQtLibs = false;
                    if (m_serviceInfo.metaData.containsKey("android.app.bundle_local_qt_libs")
                        && m_serviceInfo.metaData.getInt("android.app.bundle_local_qt_libs") == 1) {
                        localPrefix = getApplicationInfo().dataDir + "/";
                        pluginsPrefix = localPrefix + "qt-reserved-files/";
                        cleanOldCacheIfNecessary(localPrefix, pluginsPrefix);
                        extractBundledPluginsAndImports(pluginsPrefix);
                        bundlingQtLibs = true;
                    }

                    if (m_qtLibs != null) {
                        for (int i=0;i<m_qtLibs.length;i++) {
                            libraryList.add(localPrefix
                                            + "lib/lib"
                                            + m_qtLibs[i]
                                            + ".so");
                        }
                    }

                    if (m_serviceInfo.metaData.containsKey("android.app.load_local_libs")) {
                        String[] extraLibs = m_serviceInfo.metaData.getString("android.app.load_local_libs").split(":");
                        for (String lib : extraLibs) {
                            if (lib.length() > 0) {
                                if (lib.startsWith("lib/"))
                                    libraryList.add(localPrefix + lib);
                                else
                                    libraryList.add(pluginsPrefix + lib);
                            }
                        }
                    }


                    String dexPaths = new String();
                    String pathSeparator = System.getProperty("path.separator", ":");
                    if (!bundlingQtLibs && m_serviceInfo.metaData.containsKey("android.app.load_local_jars")) {
                        String[] jarFiles = m_serviceInfo.metaData.getString("android.app.load_local_jars").split(":");
                        for (String jar:jarFiles) {
                            if (jar.length() > 0) {
                                if (dexPaths.length() > 0)
                                    dexPaths += pathSeparator;
                                dexPaths += localPrefix + jar;
                            }
                        }
                    }

                    Bundle loaderParams = new Bundle();
                    loaderParams.putInt(ERROR_CODE_KEY, 0);
                    loaderParams.putString(DEX_PATH_KEY, dexPaths);
                    loaderParams.putString(LOADER_CLASS_NAME_KEY, "land.aseman.android.AsemanServiceDelegate");
                    if (m_serviceInfo.metaData.containsKey("android.app.static_init_classes")) {
                        loaderParams.putStringArray(STATIC_INIT_CLASSES_KEY,
                                                    m_serviceInfo.metaData.getString("android.app.static_init_classes").split(":"));
                    }
                    loaderParams.putStringArrayList(NATIVE_LIBRARIES_KEY, libraryList);

                    loaderParams.putString(ENVIRONMENT_VARIABLES_KEY, ENVIRONMENT_VARIABLES
                                                                      + "\tQML2_IMPORT_PATH=" + pluginsPrefix + "/qml"
                                                                      + "\tQML_IMPORT_PATH=" + pluginsPrefix + "/imports"
                                                                      + "\tQT_PLUGIN_PATH=" + pluginsPrefix + "/plugins");

                    if (APPLICATION_PARAMETERS != null) {
                        loaderParams.putString(APPLICATION_PARAMETERS_KEY, APPLICATION_PARAMETERS);
                    }

                    loadApplication(loaderParams);
                    return;
                }
            }
            catch (Exception e) {
                started = false;
                e.printStackTrace();
            }
        }
    }

    @SuppressLint("NewApi")
    public void loadApplication(Bundle loaderParams){

        try{

            ArrayList<String> libs = new ArrayList<String>();
            if ( m_serviceInfo.metaData.containsKey("android.app.bundled_libs_resource_id") )
                libs.addAll(Arrays.asList(getResources().getStringArray(m_serviceInfo.metaData.getInt("android.app.bundled_libs_resource_id"))));

            String libName = null;
            if ( m_serviceInfo.metaData.containsKey("android.app.lib_name") ) {
                libName = m_serviceInfo.metaData.getString("android.app.lib_name");
                loaderParams.putString(MAIN_LIBRARY_KEY, libName); //main library contains main() function
            }

            loaderParams.putStringArrayList(BUNDLED_LIBRARIES_KEY, libs);
            loaderParams.putString(ENVIRONMENT_VARIABLES_KEY, "");

            m_classLoader = new DexClassLoader(loaderParams.getString(DEX_PATH_KEY), // .jar/.apk files
                    getDir("outdex", Context.MODE_PRIVATE).getAbsolutePath(), // directory where optimized DEX files should be written.
                    loaderParams.containsKey(LIB_PATH_KEY) ? loaderParams.getString(LIB_PATH_KEY) : null, // libs folder (if exists)
                    getClassLoader()); // parent loader

            String loaderClassName = loaderParams.getString(LOADER_CLASS_NAME_KEY);

            Log.w(getClass().getName(), "Loader : " + loaderClassName);

            Class<?> loaderClass = m_classLoader.loadClass(loaderClassName); // load QtLoader class
            Object qtLoader = loaderClass.newInstance(); // create an instance

            Method perpareAppMethod = qtLoader.getClass().getMethod("loadApplication",
                                                                    Service.class,
                                                                    ClassLoader.class,
                                                                    Bundle.class);

            if (!(Boolean)perpareAppMethod.invoke(qtLoader, this, m_classLoader, loaderParams))
                throw new Exception("");

            // now load the application library so it's accessible from this class loader
            if (libName != null)
                System.loadLibrary(libName);

            Method startAppMethod=qtLoader.getClass().getMethod("startApplication");
            if (!(Boolean)startAppMethod.invoke(qtLoader))
                throw new Exception("");
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    static private void copyFile(InputStream inputStream, OutputStream outputStream)
        throws IOException
    {
        byte[] buffer = new byte[BUFFER_SIZE];

        int count;
        while ((count = inputStream.read(buffer)) > 0)
            outputStream.write(buffer, 0, count);
    }


    private void copyAsset(String source, String destination)
        throws IOException
    {
        // Already exists, we don't have to do anything
        File destinationFile = new File(destination);
        if (destinationFile.exists())
            return;

        File parentDirectory = destinationFile.getParentFile();
        if (!parentDirectory.exists())
            parentDirectory.mkdirs();

        destinationFile.createNewFile();

        AssetManager assetsManager = getAssets();
        InputStream inputStream = assetsManager.open(source);
        OutputStream outputStream = new FileOutputStream(destinationFile);
        copyFile(inputStream, outputStream);

        inputStream.close();
        outputStream.close();
    }

    private static void createBundledBinary(String source, String destination)
        throws IOException
    {
        // Already exists, we don't have to do anything
        File destinationFile = new File(destination);
        if (destinationFile.exists())
            return;

        File parentDirectory = destinationFile.getParentFile();
        if (!parentDirectory.exists())
            parentDirectory.mkdirs();

        destinationFile.createNewFile();

        InputStream inputStream = new FileInputStream(source);
        OutputStream outputStream = new FileOutputStream(destinationFile);
        copyFile(inputStream, outputStream);

        inputStream.close();
        outputStream.close();
    }

    private boolean cleanCacheIfNecessary(String pluginsPrefix, long packageVersion)
    {
        File versionFile = new File(pluginsPrefix + "cache.version");

        long cacheVersion = 0;
        if (versionFile.exists() && versionFile.canRead()) {
            try {
                DataInputStream inputStream = new DataInputStream(new FileInputStream(versionFile));
                cacheVersion = inputStream.readLong();
                inputStream.close();
             } catch (Exception e) {
                e.printStackTrace();
             }
        }

        if (cacheVersion != packageVersion) {
            deleteRecursively(new File(pluginsPrefix));
            return true;
        } else {
            return false;
        }
    }

    private void extractBundledPluginsAndImports(String pluginsPrefix)
        throws IOException
    {
        ArrayList<String> libs = new ArrayList<String>();

        String dataDir = getApplicationInfo().dataDir + "/";

        long packageVersion = -1;
        try {
            PackageInfo packageInfo = getPackageManager().getPackageInfo(getPackageName(), 0);
            packageVersion = packageInfo.lastUpdateTime;
        } catch (Exception e) {
            e.printStackTrace();
        }

        if (!cleanCacheIfNecessary(pluginsPrefix, packageVersion))
            return;

        {
            File versionFile = new File(pluginsPrefix + "cache.version");

            File parentDirectory = versionFile.getParentFile();
            if (!parentDirectory.exists())
                parentDirectory.mkdirs();

            versionFile.createNewFile();

            DataOutputStream outputStream = new DataOutputStream(new FileOutputStream(versionFile));
            outputStream.writeLong(packageVersion);
            outputStream.close();
        }

        {
            String key = BUNDLED_IN_LIB_RESOURCE_ID_KEY;
            java.util.Set<String> keys = m_serviceInfo.metaData.keySet();
            if (m_serviceInfo.metaData.containsKey(key)) {
                String[] list = getResources().getStringArray(m_serviceInfo.metaData.getInt(key));

                for (String bundledImportBinary : list) {
                    String[] split = bundledImportBinary.split(":");
                    String sourceFileName = dataDir + "lib/" + split[0];
                    String destinationFileName = pluginsPrefix + split[1];
                    createBundledBinary(sourceFileName, destinationFileName);
                }
            }
        }

        {
            String key = BUNDLED_IN_ASSETS_RESOURCE_ID_KEY;
            if (m_serviceInfo.metaData.containsKey(key)) {
                String[] list = getResources().getStringArray(m_serviceInfo.metaData.getInt(key));

                for (String fileName : list) {
                    String[] split = fileName.split(":");
                    String sourceFileName = split[0];
                    String destinationFileName = pluginsPrefix + split[1];
                    copyAsset(sourceFileName, destinationFileName);
                }
            }

        }
    }

    private void deleteRecursively(File directory)
    {
        File[] files = directory.listFiles();
        if (files != null) {
            for (File file : files) {
                if (file.isDirectory())
                    deleteRecursively(file);
                else
                    file.delete();
            }

            directory.delete();
        }
    }

    private void cleanOldCacheIfNecessary(String oldLocalPrefix, String localPrefix)
    {
        File newCache = new File(localPrefix);
        if (!newCache.exists()) {
            {
                File oldPluginsCache = new File(oldLocalPrefix + "plugins/");
                if (oldPluginsCache.exists() && oldPluginsCache.isDirectory())
                    deleteRecursively(oldPluginsCache);
            }

            {
                File oldImportsCache = new File(oldLocalPrefix + "imports/");
                if (oldImportsCache.exists() && oldImportsCache.isDirectory())
                    deleteRecursively(oldImportsCache);
            }

            {
                File oldQmlCache = new File(oldLocalPrefix + "qml/");
                if (oldQmlCache.exists() && oldQmlCache.isDirectory())
                    deleteRecursively(oldQmlCache);
            }
        }
    }

    static String splitCamelCase(String sp) {

        String s = Character.toUpperCase(sp.charAt(0)) + sp.substring(1);

        return s.replaceAll(
          String.format("%s|%s|%s",
             "(?<=[A-Z])(?=[A-Z][a-z])",
             "(?<=[^A-Z])(?=[A-Z])",
             "(?<=[A-Za-z])(?=[^A-Za-z])"
          ),
          " "
       );
    }
}
