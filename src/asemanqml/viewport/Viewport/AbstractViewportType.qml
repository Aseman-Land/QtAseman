import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

AbstractViewportTypeCore {
    id: item
    anchors.fill: parent

    property ListObject list

    property bool fillForeground: false

    property int index
    property int count
    property real ratio: open? 1 : 0

    property alias background: background
    property alias backgroundScene: backgroundScene
    property alias foreground: foreground
    property alias foregroundScene: foregroundScene
    property bool open

    onOpenChanged: {
        if (open)
            BackHandler.pushHandler(this, function(){ open = false })
        else
            BackHandler.removeHandler(this)
    }
    onRatioChanged: if (ratio == 0 && !open) { foregroundItem.destroy(); item.destroy();}

    RoundedItem {
        id: background
        width: parent.width
        height: parent.height

        Rectangle {
            id: backgroundScene
            anchors.fill: parent
        }
    }

    RoundedItem {
        id: foreground
        width: parent.width
        height: parent.height

        Rectangle {
            id: foregroundScene
            anchors.fill: parent
        }
    }
}
