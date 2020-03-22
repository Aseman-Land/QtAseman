import QtQuick 2.0
import QtGraphicalEffects 1.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    foreground.height: childItem? childItem.height : item.height
    foreground.y: height - foreground.height * ratio
    foreground.z: 10

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 350 }
    }

    Rectangle {
        anchors.fill: item.background
        color: "#000"
        opacity: item.ratio * 0.1
        visible: item.index <= 3
    }

    Item {
        width: item.foreground.width
        height: item.foreground.height * ratio
        anchors.bottom: parent.bottom
        z: 5
        visible: !Devices.isAndroid
        clip: true

        FastBlur {
            anchors.bottom: parent.bottom
            height: item.background.height
            width: item.background.width
            radius: Devices.isAndroid? 0 : 64
            cached: true
            source: item.background
        }
    }
}
