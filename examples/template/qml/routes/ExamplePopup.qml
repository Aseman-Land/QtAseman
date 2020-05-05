import QtQuick 2.0
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import AsemanQml.Viewport 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

Page {
    RowLayout {
        anchors.centerIn: parent

        Button {
            text: qsTr("Popup") + Translations.refresher
            onClicked: Viewport.controller.trigger("popup:/dialog/example")
            highlighted: true
        }

        Button {
            text: qsTr("Page") + Translations.refresher
            onClicked: Viewport.controller.trigger("page:/dialog/example")
        }
    }

    Header {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        color: Material.primary
        text: qsTr("App") + Translations.refresher

        HeaderMenuButton {
            ratio: 1
            onClicked: Viewport.viewport.closeLast()
        }
    }
}
