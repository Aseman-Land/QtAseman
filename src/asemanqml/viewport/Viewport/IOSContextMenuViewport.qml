import QtQuick 2.0
import QtGraphicalEffects 1.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    background.scale: 1 + ratio * 0.1

    foreground.scale: 0.5 + ratio * 0.5
    foreground.opacity: ratio
    foreground.z: 10
    foregroundScene.color: "transparent"

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
    }

    FastBlur {
        anchors.fill: parent
        radius: Devices.isAndroid? 0 : 64
        cached: true
        source: item.background
        scale: item.background.scale
        opacity: ratio

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: if (item.touchToCloseIsNull || item.touchToClose) item.open = false
        }
    }
}
