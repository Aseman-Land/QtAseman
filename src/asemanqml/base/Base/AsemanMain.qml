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

import QtQuick 2.0
import AsemanQml.Base 2.0

AsemanMainQt {
    id: smain
    focus: true

    property bool portrait: width<height

    property alias pasteButton: paste_btn
    property alias rollerDialog: roller_dialog
    property alias bottomPanel: bottom_panel
    property alias pointerDialog: point_dialog
    property alias tooltip: tool_tip
    property alias messageDialog: message_dialog
    property alias masterPalette: palette

    property color subMessageBackground: "#66ffffff"
    property bool subMessageBlur: true

    property variant mainFrame
    property SubMessage subMessage

    property real panelWidth: width

    Keys.onEscapePressed: if(View.backController) AsemanApp.back()

    Connections {
        target: View
        onCloseRequest: AsemanApp.back()
    }

    Connections {
        target: AsemanApp
        onBackRequest: {
            if(!View.backController)
                return
            if(timer_delayer.running)
                return

            timer_delayer.start()
            var res = BackHandler.back()
            if( !res && !Devices.isDesktop )
                View.tryClose()
        }
    }

    Timer {
        id: timer_delayer
        interval: 300
        repeat: false
    }

    SystemPalette {
        id: palette
        colorGroup: View.window.active? SystemPalette.Active : SystemPalette.Inactive
    }

    PointingDialog{
        id: point_dialog
        z: 9
    }

    BottomPanel {
        id: bottom_panel
        z: 10
    }

    RollerDialog {
        id: roller_dialog
        anchors.fill: parent
        z: 10
    }

    MessageDialog {
        id: message_dialog
        anchors.fill: parent
        z: 10
    }

    PasteButton {
        id: paste_btn
        z: 10
    }

    Tooltip {
        id: tool_tip
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 32*Devices.density + View.navigationBarHeight
        z: 11
    }

    function showTooltip( text ){
        tooltip.showText(text)
    }

    function showSubMessage( item_component ){
        var item = item_component.createObject(View.root);
        var msg = sub_msg_component.createObject(View.root);
        msg.source = mainFrame
        msg.item = item
        subMessage = msg
        return item
    }

    function hideSubMessage(){
        if( !subMessage )
            return

        subMessage.hide()
    }

    function showBottomPanel( component, fullWidth ){
        hideBottomPanel()
        bottom_panel.anchors.rightMargin = fullWidth? 0 : panelWidth

        var item = component.createObject(bottom_panel);
        bottom_panel.item = item
        return item
    }

    function hideBottomPanel() {
        if( bottom_panel.item )
            bottom_panel.hide()
    }

    function newModernProgressBar(){
        var item = modern_pbar_component.createObject(View.root);
        item.source = main_frame
        return item
    }

    function showPointDialog( item, x, y, width, height ){
        point_dialog.item = item
        point_dialog.pointingTo(x,y,width,height)
    }

    function hidePointDialog(){
        point_dialog.hide()
    }

    function showRollerDialog( y1, y2, item ){
        roller_dialog.show(y1,y2,item)
    }

    function hideRollerDialog(){
        roller_dialog.hide()
    }

    Component {
        id: sub_msg_component

        SubMessage {
            id: sub_msg
            backgroundColor: subMessageBackground
            blurBack: subMessageBlur
        }
    }

    Component {
        id: modern_pbar_component
        ModernProgressBar {
        }
    }

    Component.onCompleted: {
        View.root = smain
    }
}
