import QtQuick 2.0
import QtGraphicalEffects 1.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    background.transformOrigin: item.transformOriginIsNull? Qt.point(width/2, height/2) : item.transformOrigin
    background.transform: Scale {
        origin.x: item.transformOriginIsNull? item.width/2 : item.transformOrigin.x
        origin.y: item.transformOriginIsNull? item.height/2 : item.transformOrigin.y
        xScale: 1 + ratio * 0.1
        yScale: 1 + ratio * 0.1
    }

    foreground.transformOrigin: item.transformOriginIsNull? Qt.point(width/2, height/2) : item.transformOrigin
    foreground.transform: Scale {
        origin.x: item.transformOriginIsNull? item.width/2 : item.transformOrigin.x
        origin.y: item.transformOriginIsNull? item.height/2 : item.transformOrigin.y
        xScale: 0.5 + ratio * 0.5
        yScale: 0.5 + ratio * 0.5
    }
    foreground.opacity: ratio
    foreground.z: 10
    foregroundScene.color: "transparent"

    Behavior on ratio {
        NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
    }

    FastBlur {
        anchors.fill: parent
        radius: 64
        cached: true
        source: item.background
        scale: item.background.scale
        opacity: ratio
        transform: Scale {
            origin.x: item.transformOriginIsNull? item.width/2 : item.transformOrigin.x
            origin.y: item.transformOriginIsNull? item.height/2 : item.transformOrigin.y
            xScale: 1 + ratio * 0.1
            yScale: 1 + ratio * 0.1
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: if (item.touchToCloseIsNull || item.touchToClose) item.open = false
        }
    }
}
