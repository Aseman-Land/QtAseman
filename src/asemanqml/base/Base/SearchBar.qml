import QtQuick 2.4
import QtGraphicalEffects 1.0
import AsemanQml.Base 2.0

Item {
    id: searchBar
    width: 250*Devices.density
    height: 46*Devices.density
    visible: ratio > 0

    property bool show: false
    property real pointX
    property real pointY
    property real ratio: show? 1 : 0

    property alias text: input.text
    property alias font: input.font
    property color background: "#ffffff"
    property alias color: input.color
    property alias placeholder: placeholderTxt.text
    property alias inputMethodHints: input.inputMethodHints
    property alias validator: input.validator
    property alias verticalAlignment: input.verticalAlignment
    property alias horizontalAlignment: input.horizontalAlignment
    property alias selectionColor: input.selectionColor
    property alias selectionTextColor: input.selectedTextColor
    property alias cursorParent: cursorArea.cursorParent

    readonly property int styleAndroid: 0
    readonly property int styleIOS: 1
    property int styleType: Devices.isIOS? styleIOS : styleAndroid

    onStyleTypeChanged: prv.refreshStyle()

    onRatioChanged: {
        if(ratio == 1) {
            Tools.jsDelayCall(200, function(){
                input.focus = true
                input.forceActiveFocus()
            })
        } else {
            input.focus = false
        }
    }

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 400 }
    }

    QtObject {
        id: prv
        property Item styleItem

        function refreshStyle() {
            if(styleItem)
                styleItem.destroy()

            switch(styleType)
            {
            case styleIOS:
                styleItem = ios_component.createObject(searchBar)
                break

            default:
            case styleAndroid:
                styleItem = material_component.createObject(searchBar)
                break
            }
        }

        Component.onCompleted: refreshStyle()
    }

    Item {
        id: textFrame
        anchors.fill: parent
        anchors.margins: 5*Devices.density
        visible: searchBar.ratio==1? true : false
        z: 10

        Text {
            id: placeholderTxt
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10*Devices.density
            anchors.verticalCenter: input.verticalCenter
            font: input.font
            color: input.color
            opacity: 0.5
            visible: input.text.length == 0
        }

        TextInput {
            id: input
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10*Devices.density
            anchors.verticalCenter: parent.verticalCenter
            font.family: AsemanApp.globalFont.family
            font.pixelSize: 10*Devices.fontDensity
            color: "#333333"
            selectionColor: "#0d80ec"

            TextCursorArea {
                id: cursorArea
                textItem: input
            }
        }
    }

    function open() {
        show = true
    }

    function close() {
        show = false
    }

    Component {
        id: ios_component
        Item {
            anchors.fill: parent
            opacity: ratio

            Rectangle {
                anchors.fill: parent
                anchors.margins: 5*Devices.density
                radius: 5*Devices.density
                color: "#000000"
                opacity: 0.1
            }
        }
    }

    Component {
        id: material_component
        Item {
            anchors.fill: parent

            OpacityMask {
                anchors.fill: parent
                source: frame
                maskSource: mask
                cached: true
                visible: searchBar.ratio==1? false : true
            }

            Item {
                id: frame
                anchors.fill: parent
                visible: searchBar.ratio==1? true : false

                MaterialFrame {
                    id: lineFrame
                    color: background
                    anchors.fill: parent
                    anchors.margins: 5*Devices.density
                }
            }


            Item {
                id: mask
                anchors.fill: parent
                visible: false

                Rectangle {
                    id: maskCircle
                    x: searchBar.pointX - width/2
                    y: searchBar.pointY - height/2
                    width: searchBar.ratio*destWidth

                    property real destWidth: {
                        var leftX = Math.abs(mask.x - pointX)
                        var rightX = Math.abs(mask.width - pointX)

                        var topY = Math.abs(mask.y - pointY)
                        var bottomY = Math.abs(mask.height - pointY)

                        var maxX = Math.max(leftX, rightX)
                        var maxY = Math.max(topY, bottomY)
                        var r = Math.sqrt( maxX*maxX, maxY*maxY )
                        return r*2
                    }

                    height: width
                    radius: width/2
                }
            }
        }
    }
}
