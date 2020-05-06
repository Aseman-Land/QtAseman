import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import AsemanQml.Viewport 2.0
import globals 1.0

Page {
    width: Constants.width
    height: Constants.height

    property alias listView: listView

    signal itemClicked(int id)

    Label {
        anchors.centerIn: parent
        font.pixelSize: 12 * Devices.fontDensity
        text: qsTr("List is empty") + Translations.refresher
        visible: listView.count == 0
    }

    ListView {
        id: listView
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        delegate: ItemDelegate {
            id: del
            height: 60
            width: listView.width
            text: model.title

            Connections {
                target: del
                onClicked: itemClicked(model.id)
            }
        }
    }

    Header {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        color: Material.primary
        text: qsTr("App") + Translations.refresher
    }
}
