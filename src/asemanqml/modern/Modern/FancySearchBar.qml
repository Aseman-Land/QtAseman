import QtQuick 2.7
import AsemanQml.Base 2.0
import QtGraphicalEffects 1.0

Item {
    id: item

    property alias toolbarHeight: toolbar.height
    property alias toolbarTopMargin: toolbar.y
    property alias searchBarButton: searchIcon
    property alias clearButton: clearIcon

    property alias panelColor: panelRect.color
    property alias searchBarColor: searchbarArea.color

    property Item mainScene
    property Item mainList

    property bool opened: false

    readonly property real ratio: searchbar.ratio
    property alias textInput: text_input
    property alias placeholder: searchPlaceholder.text

    property string keyword

    onMainListChanged: {
        if(!mainList)
            return

        mainList.parent = scene
    }

    onRatioChanged: {
        if(ratio == 1)
            focusTimer.restart()
        else
        if(ratio == 0)
            text_input.focus = false
    }

    Item {
        id: privateScene
        anchors.fill: parent

        Timer {
            id: focusTimer
            interval: 200
            repeat: false
            onTriggered: text_input.forceActiveFocus()
        }

        FastBlur {
            anchors.centerIn: parent
            width: mainScene? mainScene.width : parent.width
            height: mainScene? mainScene.height : parent.height
            source: mainScene
            radius: keyword.length && opened? 64 : 0
            visible: keyword.length && opened
            opacity: item.ratio
            cached: true
            onSourceChanged: transform = mainScene? mainScene.transform : null
        }

        Rectangle {
            anchors.fill: parent
            color: "#000"
            opacity: searchbar.ratio * 0.6
        }

        MouseArea {
            anchors.fill: parent
            visible: opened
            onClicked: opened = false
        }

        Item {
            id: scene
            anchors.topMargin: searchbar.height
            anchors.fill: parent
        }

        FastRectengleShadow {
            anchors.fill: searchbar
            radius: 48
            opacity: searchbar.ratio
            visible: opacity > 0
        }

        Item {
            id: searchbar
            width: parent.width
            height: toolbarTopMargin + toolbarHeight*1.2
            clip: true
            y: -height * (1-ratio)

            property real ratio: opened? 1 : 0

            Behavior on ratio {
                NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
            }

            MouseArea {
                anchors.fill: parent
            }

            FastBlur {
                source: mainScene
                y: -searchbar.y - (mainScene? width - item.width : 0)/2
                x: -searchbar.x - (mainScene? height - item.height : 0)/2
                width: mainScene? mainScene.width : 0
                height: mainScene? mainScene.height : 0
                radius: searchbar.ratio == 0? 0 : 64
                visible: searchbar.ratio != 0
                cached: true
                onSourceChanged: transform = mainScene? mainScene.transform : null
            }

            Rectangle {
                id: panelRect
                anchors.fill: parent
                opacity: mainScene? 0.7 : 1
            }

            Item {
                id: searchbarScene
                anchors.fill: parent
                transform: Scale {
                    xScale: 0.5 + item.ratio*0.5
                    origin.x: searchbarScene.width/2
                }

                opacity: item.ratio

                Rectangle {
                    id: searchbarArea
                    anchors.fill: parent
                    anchors.topMargin: anchors.margins + toolbarTopMargin
                    anchors.margins: 12 * Devices.density
                    radius: 8 * Devices.density
                    color: "#000"
                    opacity: 0.2
                }

                TextInput {
                    id: text_input
                    anchors.fill: searchbarArea
                    anchors.margins: 10 * Devices.density
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: item.layoutDirection == Qt.LeftToRight? Text.AlignLeft : Text.AlignRight
                    onTextChanged: searchTimer.restart()

                    Text {
                        id: searchPlaceholder
                        anchors.fill: parent
                        verticalAlignment: text_input.verticalAlignment
                        horizontalAlignment: text_input.horizontalAlignment
                        font: text_input.font
                        color: text_input.color
                        opacity: 0.6
                        visible: text_input.length == 0
                    }

                    Timer {
                        id: searchTimer
                        interval: 500
                        repeat: false
                        onTriggered: item.keyword = text_input.text
                    }
                }
            }
        }

        Item {
            id: toolbar
            width: parent.width
            height: 50 * Devices.density

            Item {
                width: height
                height: {
                    var s1 = parent.height
                    var s2 = searchbar.height - toolbarTopMargin
                    return item.ratio*s2 + (1-item.ratio)*s1
                }
                x: item.layoutDirection==Qt.LeftToRight? parent.width - width : 0

                Rectangle {
                    id: searchHighlight
                    anchors.fill: parent
                    anchors.margins: item.opened? 18 * Devices.density : 8 * Devices.density
                    radius: item.opened? searchbarArea.radius : 4 * Devices.density
                    opacity: searchMouseArea.pressed? 0.2 : 0
                    color: searchIcon.color
                }

                MouseArea {
                    id: searchMouseArea
                    anchors.fill: parent
                    onClicked: {
                        if(item.opened) {
                            if(text_input.length == 0)
                                opened = false
                            else
                                text_input.clear()
                        } else
                            item.opened = true
                    }
                }

                Text {
                    id: searchIcon
                    anchors.centerIn: parent
                    scale: 1 - item.ratio
                }

                Text {
                    id: clearIcon
                    anchors.centerIn: parent
                    scale: item.ratio
                }
            }
        }
    }
}
