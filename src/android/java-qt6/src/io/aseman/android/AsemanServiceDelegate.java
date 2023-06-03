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

import org.qtproject.qt.android.QtNative;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Iterator;

import android.app.Service;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;

public class AsemanServiceDelegate
{
    private Service m_service = null;

    private static final String NATIVE_LIBRARIES_KEY = "native.libraries";
    private static final String BUNDLED_LIBRARIES_KEY = "bundled.libraries";
    private static final String MAIN_LIBRARY_KEY = "main.library";
    private static final String ENVIRONMENT_VARIABLES_KEY = "environment.variables";
    private static final String APPLICATION_PARAMETERS_KEY = "application.parameters";
    private static final String STATIC_INIT_CLASSES_KEY = "static.init.classes";
    private static final String NECESSITAS_API_LEVEL_KEY = "necessitas.api.level";

    private String m_environmentVariables = null;
    private String m_applicationParameters = null;

    private String m_mainLib;

    public boolean loadApplication(Service service, ClassLoader classLoader, Bundle loaderParams)
    {
        if (!loaderParams.containsKey(NATIVE_LIBRARIES_KEY))
            Log.w(getClass().getName(), "Missing parameters1 in loaderParams");

        if (!loaderParams.containsKey(BUNDLED_LIBRARIES_KEY))
            Log.w(getClass().getName(), "Missing parameters2 in loaderParams");

        /// check parameters integrity
        if (!loaderParams.containsKey(NATIVE_LIBRARIES_KEY)
                || !loaderParams.containsKey(BUNDLED_LIBRARIES_KEY)) {

            Log.w(getClass().getName(), "Missing parameters in loaderParams");
            return false;
        }

        m_service = service;
        //QtNative.setActivity(m_activity, this);
        QtNative.setClassLoader(classLoader);
        if (loaderParams.containsKey(STATIC_INIT_CLASSES_KEY)) {
            for (String className: loaderParams.getStringArray(STATIC_INIT_CLASSES_KEY)) {
                Log.w(getClass().getName(), className);
                if (className.length() == 0)
                    continue;

                try {
                    @SuppressWarnings("rawtypes")
                    Class initClass = classLoader.loadClass(className);
                    Object staticInitDataObject = initClass.newInstance(); // create an instance
                    //Method m = initClass.getMethod("setActivity", Activity.class, Object.class);
                    //m.invoke(staticInitDataObject, m_activity, this);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }

        QtNative.loadQtLibraries(loaderParams.getStringArrayList(NATIVE_LIBRARIES_KEY));
        ArrayList<String> libraries = loaderParams.getStringArrayList(BUNDLED_LIBRARIES_KEY);
        QtNative.loadBundledLibraries(libraries, QtNativeNativeLibrariesDir(m_service));
        m_mainLib = loaderParams.getString(MAIN_LIBRARY_KEY);
        // older apps provide the main library as the last bundled library; look for this if the main library isn't provided
        if (null == m_mainLib && libraries.size() > 0)
            m_mainLib = libraries.get(libraries.size() - 1);


        int necessitasApiLevel = 1;
        if (loaderParams.containsKey(NECESSITAS_API_LEVEL_KEY))
            necessitasApiLevel = loaderParams.getInt(NECESSITAS_API_LEVEL_KEY);

        m_environmentVariables = "";

        if (loaderParams.containsKey(APPLICATION_PARAMETERS_KEY))
            m_applicationParameters = loaderParams.getString(APPLICATION_PARAMETERS_KEY);
        else
            m_applicationParameters = "";

        return true;
    }

    public void debugLog(String msg)
    {
        Log.i(QtNative.QtTAG, "DEBUGGER: " + msg);
    }

    public boolean startApplication()
    {

        try {

            String nativeLibraryDir = QtNativeNativeLibrariesDir(m_service);

            Log.i(QtNative.QtTAG, "LIB DIR : " + nativeLibraryDir);

//            QtNative.startApplication
            QtNativeStartApplication
                    (  m_applicationParameters,
                                        m_environmentVariables,
                                        m_mainLib,
                                        nativeLibraryDir);
            return true;
        }
        catch (Exception e) {

            e.printStackTrace();
            return false;
        }
    }

    public static String QtNativeNativeLibrariesDir(Service service)
    {
        String m_nativeLibraryDir = null;
        try {
            ApplicationInfo ai = service.getPackageManager().getApplicationInfo(service.getPackageName(), 0);
            m_nativeLibraryDir = ai.nativeLibraryDir+"/";
        } catch (NameNotFoundException e) {
            e.printStackTrace();
        }
        return m_nativeLibraryDir;
    }


    public static boolean QtNativeStartApplication(String params,
                                           String environment,
                                           String mainLibrary,
                                           String nativeLibraryDir) throws Exception
    {
        File f = new File(nativeLibraryDir + "lib" + mainLibrary + ".so");
        if (!f.exists())
            throw new Exception("Can't find main library '" + mainLibrary + "'");

        if (params == null)
            params = "-platform\tandroid";

        boolean res = false;

        if (params.length() > 0 && !params.startsWith("\t"))
            params = "\t" + params;
        startQtApplication(f.getAbsolutePath() + params, environment);

        return res;
    }

    public static native void startQtApplication(String params, String env);
    public static native void finishQtApplication();
}
