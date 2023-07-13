import QtQuick 2.0
import AsemanQml.Controls.Beta 3.0

Control {
    id: dis
    styleFileName: "ComboBoxStyle.qml"
    property string delegateStyleFileName: "ComboBoxDelegateStyle.qml"

    property string textRole
    property string displayText: currentText
    readonly property string currentText: prv.currentText
    property alias currentIndex: prv.currentIndex
    property int count: 0

    property bool flat
    property variant model: new Array
    property alias popup: popup

    property real radius: 8

    property alias pressedX: marea.mouseX
    property alias pressedY: marea.mouseY
    property alias pressed: marea.pressed
    property alias hovered: marea.containsMouse

    signal activated(int index)

    Keys.onReturnPressed: popup.open()
    Keys.onEnterPressed: popup.open()
    Keys.onSpacePressed: popup.open()

    QtObject {
        id: prv
        property int currentIndex
        property string currentText: {
            var modelData = Array.isArray(dis.model)? dis.model[currentIndex] : dis.model.get? dis.model.get(currentIndex) : dis.model;
            if (modelData == dis.model)
                return currentIndex;
            return dis.textRole ? modelData[dis.textRole] : modelData;
        }
    }

    MouseArea {
        id: marea
        hoverEnabled: true
        anchors.fill: parent
        onPressed: {
            if (!dis.focusable)
                return;

            dis.focus = true;
            dis.forceActiveFocus();
        }
        onClicked: popup.open()
    }

    MenuPopup {
        id: popup
        width: dis.width + 20
        height: item? Math.min(item.contentHeight, 200) : 200
        x: dis.width/2 - width/2
        transformOrigin: Item.Top
        styleFileName: "ComboBoxPopupStyle.qml"

        ListView {
            id: listv
            model: dis.model
            clip: true
            currentIndex: prv.currentIndex
            delegate: ComboBoxDelegate {
                width: listv.width
                styleFileName: delegateStyleFileName
                text: dis.textRole ? (Array.isArray(dis.model) ? modelData[dis.textRole] : model[dis.textRole]) : modelData
                selected: prv.currentIndex == model.index
                onClicked: {
                    prv.currentIndex = model.index;
                    dis.activated(model.index);
                    popup.close();
                }
            }
        }
    }
}
