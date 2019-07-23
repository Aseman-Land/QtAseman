import QtQuick 2.9
import AsemanQml.Base 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

AsemanApplicationBase {
    id: app
    property url source
    readonly property alias appMain: prv.appMain

    AsemanObject {
        id: prv
        property Window appMain
    }

    onSourceChanged: {
        if(prv.appMain)
            prv.appMain.destroy()

        if(source.length == 0)
            return

        var component = Qt.createComponent(source, Component.Asynchronous);
        var callback = function(){
            if(component.status == Component.Ready)
                prv.appMain = component.createObject(app)
            else if(component.status == Component.Error) {
                console.error(component.errorString())

                var er = errorComponent.createObject(app)
                er.showError(component.errorString())
            }
        }
        component.statusChanged.connect(callback)
        callback()
    }


    Component {
        id: errorComponent
        ApplicationWindow {
            visible: true

            Rectangle {
                anchors.fill: parent
                color: "#000000"
            }

            Text {
                id: errorDialog
                anchors.centerIn: parent
                width: parent.width - 20*Devices.density
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: 10*Devices.fontDensity
                color: "#eeeeee"
                text: "<b>Fatal Error</b><br />Application could not be started. Additional information:"
            }

            function showError(str) {
                errorDialog.text += "<br />" + str
            }
        }
    }
}
