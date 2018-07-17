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

Item {
    id: get_pass
    x: 0
    y: 0
    width: parent.width
    height: parent.height

    property string password
    property bool getPassOnly: false
    property alias allowBack: title.visible
    property alias inputMethodHints: pass.inputMethodHints

    property variant backBlur
    property variant parentItem

    signal success()
    signal passGiven( string pass )

    Keys.onEscapePressed: BackHandler.back()

    onParentItemChanged: if( !parentItem ) destroy()

    Behavior on x {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
    }

    Rectangle {
        anchors.fill: parent
        color: "#cc000000"
    }

    Timer{
        id: focus_timer
        interval: 250
        repeat: false
        onTriggered: {
            pass.focus = true
        }
    }

    Timer{
        id: get_again_timer
        interval: 1250
        repeat: false
        onTriggered: {
            main_frame.x = 0
            main_frame.opacity = 1
            focus_timer.restart()
        }
    }

    Timer{
        id: destroy_timer
        interval: 250
        repeat: false
        onTriggered: get_pass.destroy()
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
    }

    Header {
        id: title
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        light: true
        visible: false
    }

    Item{
        id: main_frame
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        opacity: 1

        Behavior on x {
            NumberAnimation { easing.type: Easing.InOutCubic; duration: 250 }
        }
        Behavior on opacity {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
        }

        Text{
            id: message
            y: parent.height/2- (message.height + pass_frame.height + 2*done_btn.height )/2
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 40*Devices.density
            font.pixelSize: Math.floor(15*Devices.fontDensity)
            font.family: AsemanApp.globalFont.family
            color: "#ffffff"
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Rectangle {
            id: pass_frame
            color: "white"
            smooth: true
            radius: 3*Devices.density
            height: 40*Devices.density
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: message.bottom
            anchors.topMargin: 10*Devices.density
            anchors.leftMargin: 40*Devices.density
            anchors.rightMargin: 40*Devices.density

            STextInput{
                id: pass_placeholder
                color: "#bbbbbb"
                font.pixelSize: pass.font.pixelSize
                font.family: AsemanApp.globalFont.family
                y: pass.y
                anchors.left: pass.left
                anchors.right: pass.right
                anchors.margins: pass.anchors.margins
                visible: (!pass.focus && pass.text == "")
            }

            STextInput{
                id: pass
                color: "#333333"
                font.pixelSize: Math.floor(11*Devices.fontDensity)
                font.family: AsemanApp.globalFont.family
                y: pass_frame.height/2-height/2
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10*Devices.density
                echoMode: TextInput.Password
                inputMethodHints: Qt.ImhDigitsOnly
                onAccepted: get_pass.done()
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.margins: 4*Devices.density
                height: 32*Devices.density
                radius: 2*Devices.density
                textFont.bold: false
                normalColor: "#888888"
                highlightColor: "#444444"
                textColor: "#ffffff"
                text: qsTr("Paste")
                onClicked: {
                    pass.text = ""
                    pass.paste()
                }
            }
        }

        Button{
            id: done_btn
            height: 40*Devices.density
            width: parent.width/2 - 50*Devices.density
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: pass_frame.bottom
            anchors.topMargin: 10*Devices.density
            anchors.leftMargin: 40*Devices.density
            anchors.rightMargin: 40*Devices.density
            fontSize: Math.floor(9*Devices.fontDensity)
            normalColor: "#3B97EC"
            highlightColor: masterPalette.highlight
            textColor: "#333333"
            onClicked: get_pass.done()
        }
    }

    Item{
        id: error_frame
        y: 0
        width: parent.width
        height: parent.height
        anchors.left: main_frame.right
        opacity: 1 - main_frame.opacity

        Image{
            id: warn_image
            source: "files/warning.png"
            width: 42*Devices.density
            height: 42*Devices.density
            y: error_frame.height/2 - height/2 - 5*Devices.density
            anchors.right: warn_txt.left
            anchors.rightMargin: 10*Devices.density
            anchors.bottom: error_frame.verticalCenter
            anchors.bottomMargin: -height/2 +5*Devices.density
        }

        Text{
            id: warn_txt
            font.pixelSize: Math.floor(20*Devices.fontDensity)
            font.family: AsemanApp.globalFont.family
            color: "#ffffff"
            wrapMode: Text.WordWrap
            anchors.left: error_frame.horizontalCenter
            anchors.leftMargin: -width/2 + warn_image.width/2
            anchors.verticalCenter: error_frame.verticalCenter
        }
    }

    function done(){
        if( get_again_timer.running )
            return
        if( getPassOnly ) {
            destroy_timer.restart()
            error_frame.visible = false
            get_pass.x = -get_pass.width
            Devices.hideKeyboard()
            get_pass.passGiven(pass.text)
            return
        }

        if( Tools.passToMd5(pass.text) === get_pass.password )
        {
            destroy_timer.restart()
            error_frame.visible = false
            get_pass.x = -get_pass.width
            Devices.hideKeyboard()
            get_pass.success()
        }
        else
        {
            pass.text = ""
            main_frame.x = -get_pass.width
            main_frame.opacity = 0
            get_again_timer.restart()
        }
    }

    function initTranslations(){
        message.text = qsTr("Please enter the password")
        pass_placeholder.text = qsTr("password")
        done_btn.text = qsTr("Done")
        warn_txt.text = qsTr("Incorrect!")
    }

    Connections{
        target: AsemanApp
        onLanguageUpdated: initTranslations()
    }

    Component.onCompleted: {
        focus_timer.restart()
        initTranslations()
    }

    Component.onDestruction: {
        if( backBlur )
            backBlur.destroy()
        View.root.focus = true
    }
}
