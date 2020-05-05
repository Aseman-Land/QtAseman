import QtQuick 2.12
import AsemanQml.Base 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import globals 1.0

Item {
    id: element
    width: 200 * Devices.density
    height: 150 * Devices.density

    Frame {
        id: dialogBackground
        anchors.fill: parent
        opacity: 0.7
    }

    ColumnLayout {
        id: dialogLayout
        spacing: 4 * Devices.density
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        BusyIndicator {
            id: busyIndicator
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            running: element.visible
        }

        Label {
            id: waitLabel
            text: qsTr("Please Wait...") + Translations.refresher
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pixelSize: 9 * Devices.fontDensity
        }
    }
}
