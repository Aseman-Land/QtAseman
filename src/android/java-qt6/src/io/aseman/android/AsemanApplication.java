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

import org.qtproject.qt.android.bindings.QtApplication;

import android.app.Application;
import android.content.Intent;
import android.content.Context;

public class AsemanApplication extends QtApplication
{
    private static Context context;
    private static Application app_instance = null;

    public void onCreate(){
        super.onCreate();
        app_instance = this;
        AsemanApplication.context = getApplicationContext();
    }

    public static Context getAppContext() {
        return AsemanApplication.context;
    }

    public static Context instance() {
        return app_instance;
    }
}
