import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.1
import "."

AsemanFullWindow {
    id: appWindow
    width: 480
    height: 720
    visible: true

    Material.theme: Material.Light

    main: Page { 
        anchors.fill: parent
        
        Column {
            anchors.centerIn: parent
            spacing: 20*Devices.density
            
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Hello World") + translationManager.refresher
            }
            
            ComboBox {
                anchors.horizontalCenter: parent.horizontalCenter
                model: {
                    var res = new Array
                    console.debug( Tools.variantToJson(translationManager.translations) )
                    for(var lang in translationManager.translations)
                        res[res.length] = lang
                    return res
                }
                onCurrentTextChanged: settings.localeName = currentText
            }
        }
    }

    sidebar.delegate: Rectangle {
        anchors.fill: parent
    }

    forceActiveBackButton: searchAction.active
    headerButton.onClicked: {
        if(pageManager.count || forceActiveBackButton)
            BackHandler.back()
        else
        if(sidebar.showed)
            sidebar.discard()
        else
            sidebar.show()
    }
    headerButton.buttonColor: "#333333"

    BackAction {
        id: searchAction
    }
}
