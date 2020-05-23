import QtQuick 2.0
import QtGraphicalEffects 1.0
import AsemanQml.Base 2.0

AbstractViewportType {
    id: item

    background.transform: Scale {
        origin.x: listener.result.x
        origin.y: listener.result.y
        xScale: 1 + ratio * 0.1
        yScale: 1 + ratio * 0.1
    }

    foreground.transform: Scale {
        origin.x: listener.result.x
        origin.y: listener.result.y
        xScale: 0.5 + ratio * 0.5
        yScale: 0.5 + ratio * 0.5
    }
    foreground.opacity: ratio
    foreground.z: 10
    foregroundScene.color: "transparent"

    PointMapListener {
        id: listener
        source: item.foregroundItem
        dest: item
        x: item.typeTransformOriginIsNull? 0 : item.typeTransformOrigin.x
        y: item.typeTransformOriginIsNull? 0 : item.typeTransformOrigin.y
    }

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
        transform: Scale {
            origin.x: listener.result.x
            origin.y: listener.result.y
            xScale: 1 + ratio * 0.1
            yScale: 1 + ratio * 0.1
        }

        Rectangle {
            anchors.fill: parent
            opacity: Devices.isAndroid? 0.7 : 0.3
            color: Devices.isAndroid? "#000" : "#888"
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: if (item.touchToCloseIsNull || item.touchToClose) item.open = false
        }
    }
}
