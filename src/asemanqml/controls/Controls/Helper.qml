import QtQuick 2.0
import AsemanQml.Base 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1 as QtControls
import QtQuick.Layouts 1.2 as QtLayouts

Item {
    id: helper
    anchors.fill: parent

    property real borderPadding: 200*Devices.density
    property alias duration: switchTimer.interval
    property int currentIndex: -1
    readonly property HelperPoint currentItem: {
        if(currentIndex < 0)
            return null

        var cnt = 0
        for(var i=0; i<children.length; i++) {
            var item = children[i]
            if(item.classId != "58826245-ce6d-478a-86c2-efe33477286c" || !item.visible)
                continue

            if(cnt >= currentIndex)
                return item

            cnt++
        }

        return null
    }
    readonly property int count: {
        var cnt = 0
        for(var i=0; i<children.length; i++) {
            var item = children[i]
            if(item.classId == "58826245-ce6d-478a-86c2-efe33477286c" && item.visible)
                cnt++
        }
        return cnt
    }

    readonly property real ratio: prv.ratio

    signal finished()

    onCurrentItemChanged: {
        prv.currentItem = null
        switchTimer.restart()
    }

    QtObject {
        id: prv
        property HelperPoint lastItem
        property HelperPoint currentItem
        property real ratio: prv.currentItem? 1 : 0

        Behavior on ratio {
            NumberAnimation { easing.type: Easing.OutCubic; duration: helper.duration*0.8 }
        }
    }

    Timer {
        id: switchTimer
        interval: 400
        repeat: false
        onTriggered: {
            prv.currentItem = helper.currentItem
            prv.lastItem = helper.currentItem
        }
    }

    Item {
        id: scene
        visible: false
        anchors.fill: parent

        Rectangle {
            width: height
            height: helper.ratio * 2*Math.max(scene.width, scene.height)
            radius: width/2
            opacity: helper.ratio*0.5
            color: prv.lastItem? prv.lastItem.color : "transparent"
            x: {
                var item = prv.lastItem
                if(!item) return 0

                var itemX = item.x + item.width/2
                var centerX = 0
                if(itemX < scene.width/2)
                    centerX = 0
                else
                    centerX = scene.width

                return centerX - width/2
            }
            y: {
                var item = prv.lastItem
                if(!item) return 0

                var itemY = item.y + item.height/2
                var centerY = 0
                if(itemY < scene.height/2)
                    centerY = 0
                else
                    centerY = scene.height

                return centerY - height/2
            }
        }


        Rectangle {
            width: prv.lastItem? Math.max(prv.lastItem.width, prv.lastItem.height) + extraPadding*borderPadding : 0
            height: width
            x: prv.lastItem? prv.lastItem.x + prv.lastItem.width/2 - width/2 : 0
            y: prv.lastItem? prv.lastItem.y + prv.lastItem.height/2 - height/2 : 0
            color: prv.lastItem? prv.lastItem.color : "transparent"
            radius: width/2
            opacity: extraPaddingTimer.turnedOn? 0.7 * (1-extraPadding) : 0.01

            property real extraPadding: extraPaddingTimer.turnedOn? 1 : 0

            Behavior on extraPadding {
                NumberAnimation { easing.type: Easing.OutCubic; duration: 1000 }
            }

            Timer {
                id: extraPaddingTimer
                interval: 1000
                repeat: true
                running: prv.currentItem
                onRunningChanged: turnedOn = false
                onTriggered: turnedOn = !turnedOn
                property bool turnedOn: false
            }
        }
    }

    Item {
        id: mask
        anchors.fill: scene
        visible: false

        Rectangle {
            width: prv.lastItem? Math.max(prv.lastItem.width, prv.lastItem.height) : 0
            height: width
            x: prv.lastItem? prv.lastItem.x + prv.lastItem.width/2 - width/2 : 0
            y: prv.lastItem? prv.lastItem.y + prv.lastItem.height/2 - height/2 : 0
            radius: width/2
        }
    }

    OpacityMask {
        source: scene
        anchors.fill: scene
        maskSource: mask
        invert: true

        QtLayouts.ColumnLayout {
            width: {
                if(!prv.lastItem)
                    return 0

                var pad = 10*Devices.density
                var res = Math.max(prv.lastItem.width, prv.lastItem.height)
                if(res < scene.width/2)
                    res = scene.width/2
                else
                if(res > scene.width - pad*2)
                    res = scene.width - pad*2

                return res
            }
            y: {
                if(!prv.lastItem)
                    return 0

                var pad = 10*Devices.density
                var max = Math.max(prv.lastItem.width, prv.lastItem.height)
                var res = prv.lastItem.y + (prv.lastItem.height - max)/2 + max + pad
                if(res > scene.height - height)
                    res = prv.lastItem.y + (prv.lastItem.height - max)/2 - height - pad

                return res
            }
            x: {
                if(!prv.lastItem)
                    return 0

                var pad = 10*Devices.density
                var max = Math.max(prv.lastItem.width, prv.lastItem.height)
                var res = prv.lastItem.x + (prv.lastItem.width - max)/2 + max/2 - width/2
                if(res < pad)
                    res = pad
                else
                if(res + width + pad > scene.width)
                    res = scene.width - width - pad

                return res
            }
            opacity: prv.currentItem? 1 : 0

            Behavior on opacity {
                NumberAnimation { easing.type: Easing.OutCubic; duration: 400 }
            }

            QtLayouts.RowLayout {
                QtLayouts.Layout.fillWidth: true
                layoutDirection: View.layoutDirection

                QtControls.Label {
                    height: 50*Devices.density
                    width: height
                    color: prv.lastItem? prv.lastItem.iconColor : "transparent"
                    font: prv.lastItem? prv.lastItem.iconFont : AsemanApp.globalFont
                    text: prv.lastItem? prv.lastItem.icon : ""
                }

                QtLayouts.ColumnLayout {
                    QtLayouts.Layout.fillWidth: true

                    QtControls.Label {
                        QtLayouts.Layout.fillWidth: true
                        horizontalAlignment: View.defaultLayout? Text.AlignLeft : Text.AlignRight
                        color: prv.lastItem? prv.lastItem.titleColor : "transparent"
                        font: prv.lastItem? prv.lastItem.titleFont : AsemanApp.globalFont
                        text: prv.lastItem? prv.lastItem.title : ""
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    }

                    QtControls.Label {
                        QtLayouts.Layout.fillWidth: true
                        horizontalAlignment: View.defaultLayout? Text.AlignLeft : Text.AlignRight
                        color: prv.lastItem? prv.lastItem.descriptionColor : "transparent"
                        font: prv.lastItem? prv.lastItem.descriptionFont : AsemanApp.globalFont
                        text: prv.lastItem? prv.lastItem.description : ""
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    }
                }
            }

            QtControls.Button {
                visible: text.length
                text: prv.lastItem? prv.lastItem.buttonText : ""
                onClicked: next()
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: next()
            visible: prv.currentItem
        }
    }

    function next() {
        currentIndex++
        if(currentIndex >= count)
            Tools.jsDelayCall(duration, finished)
    }
}
