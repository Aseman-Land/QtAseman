import QtQuick 2.12
import AsemanQml.Viewport 2.0
import AsemanQml.Controls.Beta 3.0

Viewport {
    id: viewport
    anchors.fill: parent
    mainItem: Scene {
        id: scene
        anchors.fill: parent
    }

    default property alias sceneItems: scene.data
}
