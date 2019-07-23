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

import QtQuick 2.9
import QtQuick.Controls 2.0
import AsemanQml.Base 2.0

ApplicationWindow {
    id: appWin

    property bool backController: true
    property bool try_close: false
    property alias masterPalette: palette
    readonly property bool portrait: width<height
    property alias tooltip: tool_tip

    signal closeRequest()

    onCloseRequest: if(backController) AsemanApp.back()

    SystemPalette {
        id: palette
    }

    Timer {
        id: timer_delayer
        interval: 300
        repeat: false
    }

    Tooltip {
        id: tool_tip
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 32*Devices.density + View.navigationBarHeight
        z: 100000001
    }

    Connections {
        target: AsemanApp
        onBackRequest: {
            if(timer_delayer.running)
                return

            timer_delayer.start()
            var res = BackHandler.back()
            if( !res && !Devices.isDesktop )
                appWin.tryClose()
        }
    }

    function tryClose() {
        try_close = true
        close()
    }

    function showTooltip( text ){
        tool_tip.showText(text)
    }

    function showGlobalWait(text, blockBack) {
        var component = Qt.createComponent("private/GlobalBusyDialog.qml")
        var obj = component.createObject(appWin)
        obj.z = 100000000
        obj.text = text
        obj.blockBack = blockBack
        return obj
    }

    Component.onCompleted: {
        View.registerWindow(appWin)
        View.root = appWin
    }
}
