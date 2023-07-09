import QtQuick 2.15
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0
import AsemanQml.Controls.Beta 3.0

Item {
    id: dis

    property string styleFileName
    default property Component delegate
    property Component sceneComponent

    readonly property Item item: prv.item

    property bool opened: false

    property real gestureWidth: -1
    property real maximumWidth: 0
    property bool touchToClose: true
    property bool blockBack: false

    property bool openToPrimaryViewport

    function open() {
        opened = true;
    }
    function close() {
        opened = false;
    }

    onOpenedChanged: {
        if (prv.scene)
            prv.scene.ViewportType.open = false;
        if (!opened)
            return;

        var viewport = (openToPrimaryViewport? Viewport.primaryViewport : Viewport.viewport);
        prv.scene = viewport.append(sceneComponent, {"prv": prv}, dis.Style.styleUrl + '/' + styleFileName)
    }

    onStyleFileNameChanged: {
        if (opened) {
            close();
            open();
        }
    }

    QtObject {
        id: prv

        property Item item
        property Item scene
        property point transformPoint: {
            switch (dis.transformOrigin) {
            case Item.Left:
                return Qt.point(0, dis.height/2);
            default:
            case Item.TopLeft:
                return Qt.point(0, 0);
            case Item.Top:
                return Qt.point(dis.width/2, 0);
            case Item.TopRight:
                return Qt.point(dis.width, 0);
            case Item.Right:
                return Qt.point(dis.width, dis.height/2);
            case Item.BottomRight:
                return Qt.point(dis.width, dis.height);
            case Item.Bottom:
                return Qt.point(dis.width/2, dis.height);
            case Item.BottomLeft:
                return Qt.point(0, dis.height);
            case Item.Center:
                return Qt.point(dis.width/2, dis.height/2);
            }
        }

        function setupViewportType(item) {
            item.ViewportType.transformOrigin = Qt.binding(function(){ return prv.transformPoint; });
            item.ViewportType.gestureWidth = Qt.binding(function(){ return dis.gestureWidth<0? item.width : dis.gestureWidth; });
            item.ViewportType.maximumWidth = Qt.binding(function(){ return dis.maximumWidth; });
            item.ViewportType.touchToClose = Qt.binding(function(){ return dis.touchToClose; });
            item.ViewportType.blockBack = Qt.binding(function(){ return dis.blockBack; });
        }

        onSceneChanged: if (!scene) opened = false
    }
}
