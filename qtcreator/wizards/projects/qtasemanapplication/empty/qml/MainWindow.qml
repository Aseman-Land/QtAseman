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
    }
}
