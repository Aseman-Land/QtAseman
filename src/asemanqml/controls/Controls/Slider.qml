import QtQuick 2.9
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import QtQuick.Controls 2.2 as QtControls
import QtQuick.Controls.Material 2.1

/*!
    \class Slider
    \brief Inherited QtControls Slider that show a beautiful label above it.
 */
QtControls.Slider {
    id: slider
    orientation: Qt.Horizontal

    /*!
        type:bool Sets the slider upper label is visible or not. This label shows current value of the slider.
    */
    property alias labelVisible: lblScene.visible


    property alias labelOpacity: lblScene.opacity
    property int labelDecimals: 1
    property string labelUnit: ""

    Rectangle {
        id: lblScene
        parent: slider.handle
        width: lbl.width + 20*Devices.density
        height: lbl.height + 20*Devices.density
        anchors.bottom: parent.top
        anchors.bottomMargin: 10*Devices.density
        anchors.horizontalCenter: parent.horizontalCenter
        color: Material.accent
        radius: 8*Devices.density
        scale: slider.pressed? 1.2 : 1
        transformOrigin: Item.Bottom
        visible: labelVisible

        Behavior on scale {
            NumberAnimation { easing.type: Easing.OutCubic; duration: 250 }
        }

        QtControls.Label {
            id: lbl
            anchors.centerIn: parent
            color: "#fff"
            text: Math.floor(slider.value*Math.pow(10, labelDecimals))/Math.pow(10, labelDecimals) + labelUnit
        }
    }
}
