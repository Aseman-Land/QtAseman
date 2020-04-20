import QtQuick 2.0
import QtGraphicalEffects 1.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    foreground.height: foregroundItem? foregroundItem.height : item.height
    foreground.width: foregroundItem? foregroundItem.width : item.width
    foreground.scale: 1.1 - ratio * 0.1
    foreground.opacity: ratio
    foreground.anchors.centerIn: foreground.parent
    foreground.z: 10
    foreground.radius: Devices.isAndroid? 0 : 10 * Devices.density
    foregroundScene.color: "transparent"

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
    }

    Rectangle {
        anchors.fill: item.background
        color: "#000"
        opacity: item.ratio * 0.2
        visible: item.ratio

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: if (item.touchToCloseIsNull || item.touchToClose) item.open = false
        }
    }

    RoundedItem {
        anchors.centerIn: item.foreground
        width: item.foreground.width
        height: item.foreground.height
        scale: item.foreground.scale
        z: 8
        opacity: item.ratio
        radius: item.foreground.radius
        clip: true
        visible: !Devices.isAndroid

        FastBlur {
            anchors.centerIn: parent
            height: item.background.height
            width: item.background.width
            radius: Devices.isAndroid? 0 : 64
            cached: true
            source: item.background
        }
    }
}
