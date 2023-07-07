import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0
import AsemanQml.Base 2.0
import AsemanQml.Viewport 2.0

AbstractViewportScene {
    id: dis
    sceneComponent: freeSceneItem

    Component {
        id: freeSceneItem
        Scene {
            id: scene

            property variant prv

            PointMapListener {
                id: mapListener
                source: dis.parent
                dest: Viewport.viewport
            }

            Component.onCompleted: {
                prv.item = delegate.createObject(Viewport.viewport, {"parent": scene});
                prv.item.anchors.fill = scene;
                prv.setupViewportType(scene);
                x = Qt.binding(function(){ return mapListener.result.x + dis.x; });
                y = Qt.binding(function(){ return mapListener.result.y + dis.y; });
                width = Qt.binding(function(){ return dis.width; });
                height = Qt.binding(function(){ return dis.height; });
            }
            Component.onDestruction: {
                prv.item.destroy()
            }
        }
    }

}
