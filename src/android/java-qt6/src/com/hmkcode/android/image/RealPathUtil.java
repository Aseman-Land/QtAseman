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

package com.hmkcode.android.image;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.CursorLoader;
import android.database.Cursor;
import android.net.Uri;
import android.provider.DocumentsContract;
import android.provider.MediaStore;

public class RealPathUtil {

	@SuppressLint("NewApi")
	public static String getRealPathFromURI_API19(Context context, Uri uri){
		String filePath = "";
		String wholeID = DocumentsContract.getDocumentId(uri);

	     // Split at colon, use second item in the array
	     String id = wholeID.split(":")[1];

	     String[] column = { MediaStore.Images.Media.DATA };     

	     // where id is equal to             
	     String sel = MediaStore.Images.Media._ID + "=?";

	     Cursor cursor = context.getContentResolver().query(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, 
	                               column, sel, new String[]{ id }, null);
	     
	     int columnIndex = cursor.getColumnIndex(column[0]);

	     if (cursor.moveToFirst()) {
	         filePath = cursor.getString(columnIndex);
	     }   

	     cursor.close();
	     
	     return filePath;
	}
	
	
	@SuppressLint("NewApi")
	public static String getRealPathFromURI_API11to18(Context context, Uri contentUri) {
		  String[] proj = { MediaStore.Images.Media.DATA };
		  String result = null;
		   
		  CursorLoader cursorLoader = new CursorLoader(
				  context, 
		    contentUri, proj, null, null, null);        
		  Cursor cursor = cursorLoader.loadInBackground();
		  
		  if(cursor != null){
		   int column_index = 
		     cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
		   cursor.moveToFirst();
		   result = cursor.getString(column_index);
		  }
		    
		  return result;  
	}
	
	public static String getRealPathFromURI_BelowAPI11(Context context, Uri contentUri){
		       String[] proj = { MediaStore.Images.Media.DATA };
		       Cursor cursor = context.getContentResolver().query(contentUri, proj, null, null, null);
		       int column_index
		  = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
		       cursor.moveToFirst();
		       return cursor.getString(column_index);
	}
}
