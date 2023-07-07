import QtQuick 2.0
import AsemanQml.Viewport 2.0
import AsemanQml.Controls.Beta 3.0

AbstractViewportScene {
    id: dis
    sceneComponent: freeSizeSceneItem

    Component {
        id: freeSizeSceneItem
        Scene {
            id: scene

            property variant prv

            Component.onCompleted: {
                prv.item = delegate.createObject(Viewport.viewport, {"parent": scene});
                prv.item.anchors.fill = scene;
                prv.setupViewportType(scene);
                width = Qt.binding(function(){ return dis.width; });
                height = Qt.binding(function(){ return dis.height; });
            }
            Component.onDestruction: {
                prv.item.destroy()
            }
        }
    }
}
