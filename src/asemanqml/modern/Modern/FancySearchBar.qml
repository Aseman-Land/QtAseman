import QtQuick 2.9
import AsemanQml.Base 2.0
import AsemanQml.Controls 2.0
import AsemanQml.Awesome 2.0
import QtGraphicalEffects 1.0

Item {
    id: item

    property int layoutDirection: View.layoutDirection
    property alias toolbarHeight: toolbar.height
    property alias toolbarTopMargin: toolbar.y
    property alias searchBarButton: searchIcon
    property alias clearButton: clearIcon

    property alias panelColor: panelRect.color
    property alias searchBarColor: searchbarArea.color
    property alias background: _background.color

    property Item mainList

    property alias opened: openedAction.active

    readonly property real ratio: searchbar.ratio
    property alias textInput: text_input
    property alias placeholder: searchPlaceholder.text

    property string keyword

    BackAction { id: openedAction }

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

        Rectangle {
            id: _background
            anchors.fill: parent
            color: "#99000000"
            opacity: searchbar.ratio
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
            height: toolbarTopMargin + Devices.standardTitleBarHeight
            clip: true
            y: -height * (1-ratio)

            property real ratio: opened? 1 : 0

            Behavior on ratio {
                NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
            }

            MouseArea {
                anchors.fill: parent
            }

            Rectangle {
                id: panelRect
                anchors.fill: parent
                opacity: 1
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
                    anchors.margins: (Devices.isDesktop? 10 : 7) * Devices.density
                    radius: 8 * Devices.density
                    color: "#000"
                    opacity: 0.2
                }

                TextInput {
                    id: text_input
                    anchors.fill: searchbarArea
                    leftPadding: Devices.isIOS || layoutDirection==Qt.RightToLeft? 0 : height
                    rightPadding: Devices.isIOS || layoutDirection==Qt.LeftToRight? 0 : height
                    selectedTextColor: "#fff"
                    selectionColor: "#18f"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: item.layoutDirection == Qt.LeftToRight? Text.AlignLeft : Text.AlignRight
                    inputMethodHints: Qt.ImhNoPredictiveText
                    font.family: AsemanApp.globalFont.family
                    font.pixelSize: 10*Devices.fontDensity
                    onTextChanged: searchTimer.restart()

                    Text {
                        id: searchPlaceholder
                        anchors.fill: parent
                        leftPadding: text_input.leftPadding
                        rightPadding: text_input.rightPadding
                        verticalAlignment: text_input.verticalAlignment
                        horizontalAlignment: text_input.horizontalAlignment
                        font: text_input.font
                        color: text_input.color
                        opacity: 0.6
                        visible: text_input.length == 0
                    }

                    TextCursorArea { id: cursor; active: true; cursorParent: item}

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
            y: Devices.statusBarHeight
            width: parent.width
            height: Devices.standardTitleBarHeight

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
                    font.family: Awesome.family
                    font.pixelSize: 12*Devices.fontDensity
                    text: Awesome.fa_search
                    color: "#666"
                }

                Text {
                    id: clearIcon
                    anchors.centerIn: parent
                    scale: item.ratio
                    font.family: Awesome.family
                    font.pixelSize: 12*Devices.fontDensity
                    text: Awesome.fa_times
                    color: "#666"
                }
            }
        }
    }
}
