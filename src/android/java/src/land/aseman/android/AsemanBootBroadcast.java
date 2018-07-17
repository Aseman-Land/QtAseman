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

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import land.aseman.android.AsemanService;

public class AsemanBootBroadcast extends BroadcastReceiver {
    @Override
    public void onReceive(Context ctx, Intent intent) {
        if(intent.getAction().equalsIgnoreCase(Intent.ACTION_BOOT_COMPLETED)) {
            Intent i = new Intent(ctx, AsemanService.class);
            i.putExtra("name", "SurvivingwithAndroid");
            try {
                ctx.startService(i);
            } catch(Exception e) {
                return;
            }
        }
    }
}
