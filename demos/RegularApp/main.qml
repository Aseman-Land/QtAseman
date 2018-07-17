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

import QtQuick 2.7
import AsemanTools 1.0

AsemanApplication {
    id: app
    applicationName: "Regular App"
    applicationAbout: "It's an regular app"
    applicationDisplayName: "Regular App"
    applicationVersion: "1.0.0"
    applicationId: "5371c896-7f09-4013-a657-e6338fae82b0"
    organizationDomain: "co.aseman"
    organizationName: "Aseman Team"

    property variant appMain

    Component.onCompleted: { // Control app to run one instance
        if(app.isRunning) {
            console.debug("Another instance is running. Trying to make that visible...")
            Tools.jsDelayCall(1, function(){
                app.sendMessage("show")
                app.exit(0)
            })
        } else {
            var component = Qt.createComponent("AppWindow.qml", Component.Asynchronous);
            var callback = function(){
                if(component.status == Component.Ready)
                    appMain = component.createObject(app)
                else if(component.status == Component.Error) {
                    console.error(component.errorString())
                }
            }
            component.statusChanged.connect(callback)
            callback()
        }
    }
}
