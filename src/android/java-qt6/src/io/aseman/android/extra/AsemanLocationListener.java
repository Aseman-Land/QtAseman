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
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.provider.Settings;
import android.util.Log;
import java.util.HashMap;
import java.io.IOException;
import java.util.List;
import java.util.Locale;
import java.lang.Runnable;
import android.os.Handler;

public class AsemanLocationListener
{
    private final int TWO_MINUTES = 1000 * 60 * 2;
    private final String TAG = "AsemanLocationListener";
    private int lastInterval = -1;

    private LocationManager locationManager;

    public native void _locationListened(double longitude, double latitude, double altitude, String city);

    AsemanLocationListener() {
        locationManager = (LocationManager)getContext().getSystemService(Context.LOCATION_SERVICE);
    }

    private Boolean displayGpsStatus() {
        ContentResolver contentResolver = getContext().getContentResolver();
        boolean gpsStatus = Settings.Secure.isLocationProviderEnabled(contentResolver, LocationManager.GPS_PROVIDER);
        if (gpsStatus) {
            return true;
        } else {
            return false;
        }
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

    public void requestLocationUpdates(final int interval) {
        Handler mainHandler = new Handler(getContext().getMainLooper());
        Runnable myRunnable = new Runnable() {
            @Override
            public void run() {
                if(lastInterval == interval)
                    return;
                if(lastInterval != -1)
                    locationManager.removeUpdates(locationListener);

                lastInterval = interval;
                if(lastInterval == -1)
                    return;

                if(displayGpsStatus())
                    locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, interval, 10, locationListener);
                else
                    locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, interval, 10, locationListener);
            }
        };
        mainHandler.post(myRunnable);
    }

    public void getLastKnownLocation() {
        Location locationGPS = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        Location locationNet = locationManager.getLastKnownLocation(LocationManager.NETWORK_PROVIDER);

        Location loc = locationGPS;
        if(isBetterLocation(locationNet, loc))
            loc = locationNet;

        double longitude = loc.getLongitude();
        double latitude = loc.getLatitude();

        _locationListened(longitude, latitude, 0, "");
    }

    protected boolean isBetterLocation(Location location, Location currentBestLocation) {
        if (currentBestLocation == null)
            return true;
        if (location == null)
            return false;

        // Check whether the new location fix is newer or older
        long timeDelta = location.getTime() - currentBestLocation.getTime();
        boolean isSignificantlyNewer = timeDelta > TWO_MINUTES;
        boolean isSignificantlyOlder = timeDelta < -TWO_MINUTES;
        boolean isNewer = timeDelta > 0;

        // If it's been more than two minutes since the current location, use the new location,
        // because the user has likely moved.
        if (isSignificantlyNewer) {
            return true;
            // If the new location is more than two minutes older, it must be worse.
        } else if (isSignificantlyOlder) {
            return false;
        }

        // Check whether the new location fix is more or less accurate
        int accuracyDelta = (int) (location.getAccuracy() - currentBestLocation.getAccuracy());
        boolean isLessAccurate = accuracyDelta > 0;
        boolean isMoreAccurate = accuracyDelta < 0;
        boolean isSignificantlyLessAccurate = accuracyDelta > 200;

        // Check if the old and new location are from the same provider
        boolean isFromSameProvider = isSameProvider(location.getProvider(),
                                                    currentBestLocation.getProvider());

        // Determine location quality using a combination of timeliness and accuracy
        if (isMoreAccurate) {
            return true;
        } else if (isNewer && !isLessAccurate) {
            return true;
        } else if (isNewer && !isSignificantlyLessAccurate && isFromSameProvider) {
            return true;
        }
        return false;
    }

    /** Checks whether two providers are the same */
    private boolean isSameProvider(String provider1, String provider2) {
        if (provider1 == null) {
            return provider2 == null;
        }
        return provider1.equals(provider2);
    }

    /*---------- Listener class to get coordinates ------------- */
    LocationListener locationListener = new LocationListener() {

        @Override
        public void onLocationChanged(Location loc) {
            double longitude = loc.getLongitude();
            double latitude = loc.getLatitude();

            /*------- To get city name from coordinates -------- */
            String cityName = null;

            _locationListened(longitude, latitude, 0, cityName);
        }

        @Override
        public void onProviderDisabled(String provider) {}

        @Override
        public void onProviderEnabled(String provider) {}

        @Override
        public void onStatusChanged(String provider, int status, Bundle extras) {}
    };
}
