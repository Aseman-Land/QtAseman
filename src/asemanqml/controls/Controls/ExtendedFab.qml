import QtQuick 2.0
import AsemanQml.Modern 2.0 as Modern
import AsemanQml.Base 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item {
    id: item
    height: 50 * Devices.density
    width: scene.width

    property color color
    property alias icon: fabIcon.text
    property alias textColor: fabIcon.color
    property alias text: fabText.text
    property alias fontFamily: fabText.font.family
    property int fontSize: 20
    property Flickable scrollArea

    Item {
        id: scene
        width: open? extendedWidth : parent.height
        height: open? extendedHeight : parent.height
        anchors.centerIn: parent

        property real extendedHeight: parent.height /** 0.9*/
        property bool open: false
        property int lastY: 0
        property int listY: scrollArea ? scrollArea.contentY : 0
        property int extendedWidth: rows.width + parent.height

        onListYChanged: {
            if(listY < 0)
                return
            if (lastY - listY > 5 ) {
                open = true
                lastY = listY
            } else if(listY - lastY > 20)   {
                open = false
                lastY = listY
            }

        }

        Modern.FastDropShadow {
            anchors.fill: fab
            horizontalOffset: 1*Devices.density
            verticalOffset: 1*Devices.density
            radius: 20*Devices.density
            color: "#000"
            opacity: 0.6
            source: fab
        }

        Rectangle {
            id: fab
            anchors.fill: parent
            radius: height / 2
            color: mouseArea.pressed? Qt.darker(item.color, 1.3) : item.color

            Behavior on color {
                ColorAnimation {
                    easing: {
                        type: Easing.OutCubic
                    }
                    duration: 200
                }
            }

            Row {
                id: rows
                anchors.verticalCenter: parent.verticalCenter
                x: scene.open? scene.height/2 : scene.height/2 - fabIcon.width/2

                Behavior on x {
                    NumberAnimation {
                        easing {
                            type: Easing.OutCubic
                        }
                        duration: 300
                    }
                }

                spacing: 8 * Devices.density
                Text {
                    id: fabIcon
                    text: icon
                    color: textColor
                    font.pixelSize: fontSize * Devices.fontDensity
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: fabText
                    text: text
                    color: textColor
                    font.pixelSize: (fabIcon.font.pixelSize - 6) * Devices.fontDensity
                    opacity: scene.open? 1 : 0
                    anchors.verticalCenter: parent.verticalCenter

                    Behavior on opacity {
                        NumberAnimation {
                            easing {
                                type: Easing.OutCubic
                            }
                            duration: 300
                        }
                    }
                }
            }
        }

        Behavior on width {
            NumberAnimation {
                easing {
                    type: Easing.OutCubic
                }
                duration: 300
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }
}

