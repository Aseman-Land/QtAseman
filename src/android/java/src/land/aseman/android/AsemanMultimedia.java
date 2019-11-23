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
import org.json.JSONArray;
import org.json.JSONObject;

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
        MediaStore.Audio.Albums.ARTIST_ID
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
        MediaStore.Audio.Media.ARTIST_ID,
        MediaStore.Audio.Media.ALBUM_ID
    };
    private static String[] artistsProjection = {
        MediaStore.Audio.Artists._ID,
        MediaStore.Audio.Artists.ARTIST
    };

    private String cursorToMusicJson(Cursor cursor) {
        JSONArray jsonArray = new JSONArray();
        while(cursor.moveToNext()){

            JSONObject obj = new JSONObject();
            try {
                obj.put("id", cursor.getString(0));
                obj.put("artist", cursor.getString(1));
                obj.put("album", cursor.getString(2));
                obj.put("art", cursor.getString(3));
                obj.put("title", cursor.getString(4));
                obj.put("data", cursor.getString(5));
                obj.put("displayName", cursor.getString(6));
                obj.put("duration", cursor.getString(7));
                obj.put("artistID", cursor.getString(8));
                obj.put("albumID", cursor.getString(9));

                jsonArray.put(obj);
            } catch (Exception e) {
            }
        }

        return jsonArray.toString();
    }

    private String cursorToAlbumJson(Cursor cursor) {
        JSONArray jsonArray = new JSONArray();
        while(cursor.moveToNext()){

            JSONObject obj = new JSONObject();
            try {
                obj.put("id", cursor.getString(0));
                obj.put("artist", cursor.getString(1));
                obj.put("album", cursor.getString(2));
                obj.put("art", cursor.getString(3));
                obj.put("songs", cursor.getString(4));
                obj.put("artistId", cursor.getString(5));

                jsonArray.put(obj);
            } catch (Exception e) {
            }
        }

        return jsonArray.toString();
    }

    private String cursorToArtistJson(Cursor cursor) {
        JSONArray jsonArray = new JSONArray();
        while(cursor.moveToNext()){

            JSONObject obj = new JSONObject();
            try {
                obj.put("id", cursor.getString(0));
                obj.put("artist", cursor.getString(1));

                jsonArray.put(obj);
            } catch (Exception e) {
            }
        }

        return jsonArray.toString();
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
