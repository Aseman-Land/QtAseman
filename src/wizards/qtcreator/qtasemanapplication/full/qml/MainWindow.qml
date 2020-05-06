import QtQuick 2.12
import AsemanQml.Controls 2.0
import AsemanQml.Viewport 2.0
import QtQuick.Controls 2.3
import forms 1.0
import models 1.0
import "routes"

AsemanWindow {
    width: 500
    height: 820

    Viewport {
        id: viewport
        anchors.fill: parent
        mainItem: MainForm {
            anchors.fill: parent
            listView.model: ExampleModel {}
            onItemClicked: Viewport.controller.trigger("popup:/dialog/example", {"id": id})
        }
    }

    ViewController {
        viewport: viewport
    }
}
