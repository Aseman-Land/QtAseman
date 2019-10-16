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

import android.app.Activity;
import android.content.Context;
import android.net.Uri;
import android.provider.MediaStore;
import android.database.Cursor;
import android.graphics.Rect ;
import android.util.Log;
import java.util.Iterator;

import land.aseman.android.AsemanActivity;

public class AsemanMultimedia
{
    private static boolean implemented = false;

    private static String[] albumsProjection = {
        MediaStore.Audio.Albums._ID,
        MediaStore.Audio.Albums.ARTIST,
        MediaStore.Audio.Albums.ALBUM,
        MediaStore.Audio.Albums.ALBUM_ART,
        MediaStore.Audio.Albums.NUMBER_OF_SONGS,
        MediaStore.Audio.Albums.ARTIST_ID,
        MediaStore.Audio.Albums.ALBUM_KEY
    };
    private static String[] musicsProjection = {
        MediaStore.Audio.Media._ID,
        MediaStore.Audio.Media.ARTIST,
        MediaStore.Audio.Media.ALBUM,
        MediaStore.Audio.Media.YEAR,
        MediaStore.Audio.Media.TITLE,
        MediaStore.Audio.Media.DATA,
        MediaStore.Audio.Media.DISPLAY_NAME,
        MediaStore.Audio.Media.DURATION,
        MediaStore.Audio.Media.ALBUM_KEY,
        MediaStore.Audio.Media.ARTIST_KEY,
        MediaStore.Audio.Media.ARTIST_ID,
        MediaStore.Audio.Media.ALBUM_ID
    };
    private static String[] artistsProjection = {
        MediaStore.Audio.Artists._ID,
        MediaStore.Audio.Artists.ARTIST,
        MediaStore.Audio.Artists.ARTIST_KEY
    };

    private String cursorToMusicJson(Cursor cursor) {
        String result = "[";
        boolean firstItem = true;
        while(cursor.moveToNext()){
            if (!firstItem) {
                result += ",";
            } else {
                firstItem = false;
            }
            result += "{";
            result += "\"id\":\"" + cursor.getString(0) + "\",";
            result += "\"artist\":\"" + cursor.getString(1) + "\",";
            result += "\"album\":\"" + cursor.getString(2) + "\",";
            result += "\"art\":\"" + cursor.getString(3) + "\",";
            result += "\"title\":\"" + cursor.getString(4) + "\",";
            result += "\"data\":\"" + cursor.getString(5) + "\",";
            result += "\"displayName\":\"" + cursor.getString(6) + "\",";
            result += "\"duration\":\"" + cursor.getString(7) + "\",";
            result += "\"albumKey\":\"" + cursor.getString(8) + "\",";
            result += "\"artistKey\":\"" + cursor.getString(9) + "\",";
            result += "\"artistID\":\"" + cursor.getString(10) + "\",";
            result += "\"albumID\":\"" + cursor.getString(11) + "\"}";
        }

        result += "]";
        return result;
    }

    private String cursorToAlbumJson(Cursor cursor) {
        String result = "[";
        boolean firstItem = true;
        while(cursor.moveToNext()){
            if (!firstItem) {
                result += ",";
            } else {
                firstItem = false;
            }
            result += "{";
            result += "\"id\":\"" + cursor.getString(0) + "\",";
            result += "\"artist\":\"" + cursor.getString(1) + "\",";
            result += "\"album\":\"" + cursor.getString(2) + "\",";
            result += "\"art\":\"" + cursor.getString(3) + "\",";
            result += "\"songs\":\"" + cursor.getString(4) + "\",";
            result += "\"artistId\":\"" + cursor.getString(5) + "\",";
            result += "\"albumKey\":\"" + cursor.getString(6) + "\"}";
        }

        result += "]";
        return result;
    }

    private String cursorToArtistJson(Cursor cursor) {
        String result = "[";
        boolean firstItem = true;
        while(cursor.moveToNext()){
            if (!firstItem) {
                result += ",";
            } else {
                firstItem = false;
            }
            result += "{";
            result += "\"id\":\"" + cursor.getString(0) + "\",";
            result += "\"artist\":\"" + cursor.getString(1) + "\",";
            result += "\"artistKey\":\"" + cursor.getString(2) + "\"}";
        }

        result += "]";
        return result;
    }

    public String getAllMusics() {
        String selection = MediaStore.Audio.Media.IS_MUSIC + " != 0";

        Cursor cursor;
        try {
            cursor = AsemanActivity.getActivityInstance().managedQuery(
                MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,
                musicsProjection,
                selection,
                null,
                null);
        } catch (Exception e) {
            return "";
        }

        return cursorToMusicJson(cursor);
    }

    public String getAllAlbums() {
        String selection = MediaStore.Audio.Albums._ID + " != 0";

        Cursor cursor;
        try {
            cursor = AsemanActivity.getActivityInstance().managedQuery(
                MediaStore.Audio.Albums.EXTERNAL_CONTENT_URI,
                albumsProjection,
                selection,
                null,
                null);
        } catch (Exception e) {
            return "";
        }

        return cursorToAlbumJson(cursor);
    }

    public String getAllArtists() {
        String selection = MediaStore.Audio.Artists._ID + " != 0";

        Cursor cursor;
        try {
            cursor = AsemanActivity.getActivityInstance().managedQuery(
                MediaStore.Audio.Artists.EXTERNAL_CONTENT_URI,
                artistsProjection,
                selection,
                null,
                null);
        } catch (Exception e) {
            return "";
        }

        return cursorToArtistJson(cursor);
    }

    public String getArtistAlbums(String artistId) {
        String selection = MediaStore.Audio.Albums.ARTIST_ID + " = " + artistId;

        Cursor cursor;
        try {
            cursor = AsemanActivity.getActivityInstance().managedQuery(
                MediaStore.Audio.Albums.EXTERNAL_CONTENT_URI,
                albumsProjection,
                selection,
                null,
                null);
        } catch (Exception e) {
            return "";
        }

        return cursorToAlbumJson(cursor);
    }

    public String getArtistSongs(String artistId) {
        String selection = MediaStore.Audio.Media.ARTIST_ID + " = " + artistId;

        Cursor cursor;
        try {
            cursor = AsemanActivity.getActivityInstance().managedQuery(
                MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,
                musicsProjection,
                selection,
                null,
                null);
        } catch (Exception e) {
            return "";
        }

        return cursorToMusicJson(cursor);
    }

    public String getAlbumSongs(String albumId) {
        String selection = MediaStore.Audio.Media.ALBUM_ID + " = " + albumId;

        Cursor cursor;
        try {
            cursor = AsemanActivity.getActivityInstance().managedQuery(
                MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,
                musicsProjection,
                selection,
                null,
                null);
        } catch (Exception e) {
            return "";
        }

        return cursorToMusicJson(cursor);
    }

    public boolean setImplemented(boolean stt) {
        implemented = stt;
        return true;
    }
}
