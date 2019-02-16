import QtQuick 2.0
import AsemanQml.Base 2.0

Item {
    id: item

    property string title
    property string description
    property string icon

    property color color: "#0d80ec"

    property color titleColor: "#fff"
    property color descriptionColor: "#fff"
    property color iconColor: "#fff"

    property font titleFont
    property font descriptionFont
    property font iconFont

    property string buttonText: "Next"

    titleFont.pixelSize: 11*Devices.fontDensity
    descriptionFont.pixelSize: 9*Devices.fontDensity

    readonly property string classId: "58826245-ce6d-478a-86c2-efe33477286c"
}
