import QtQuick 2.12
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import AsemanQml.Viewport 2.0
import QtQuick.Controls 2.3

AsemanWindow {
    width: 500
    height: 820

    Viewport {
        id: viewport
        anchors.fill: parent
        mainItem: MainForm {
            anchors.fill: parent
            menuButton.onClicked: drawer.percent? drawer.discard() : drawer.show()
            btn.onClicked: Viewport.controller.trigger("popup:/hello/world", {extra: " :)"})
            menuBtn.onClicked: Viewport.controller.trigger("menu:/hello/world", {extra: " :)"})
        }
    }

    ViewportController {
        viewport: viewport

        ViewportControllerRoute {
            route: /popup\\:\\/hello\\/world.*/
            sourceComponent: Label {
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: qsTr("Hello World!") + Translations.refresher + extra
                property string extra
            }
        }

        ViewportControllerRoute {
            route: /menu\\:\\/hello\\/world.*/
            sourceComponent: Rectangle {
                radius: 10
                anchors.top: parent.verticalCenter
                anchors.left: parent.horizontalCenter
                width: 200
                height: 200
                color: "#eee"

                MouseArea { anchors.fill: parent }

                Button {
                    anchors.centerIn: parent
                    text: qsTr("Close") + Translations.refresher
                    onClicked: Viewport.viewport.closeLast()
                }
            }
        }
    }
}
