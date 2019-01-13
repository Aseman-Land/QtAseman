import QtQuick 2.0
import AsemanQml.Base 2.0

Item {
    id: navigBar
    data: [back, bar]

    property alias color: back.color
    default property alias contents: back.data

    property int currentIndex
    readonly property int count: repeater.model.length

    property alias barHeight: bar.height
    readonly property FancyPage currentPage: back.currentIndex>=0 && back.currentIndex<repeater.model.length? repeater.model[back.currentIndex] : null

    onCurrentIndexChanged: {
        back.lastCurrentIndex = back.currentIndex
        back.currentIndex = currentIndex
    }

    Rectangle {
        id: back
        anchors.fill: parent

        property int currentIndex
        property int lastCurrentIndex
        property int animDuration

        Timer {
            interval: 50
            running: true
            repeat: false
            onTriggered: back.animDuration = 300
        }
    }

    Item {
        id: bar
        width: navigBar.width
        height: 50 * Devices.density
        anchors.bottom: navigBar.bottom

        property real normalWidth: back.currentIndex>=0? bar.height*1.2 : bar.width / navigBar.count
        property real selectedWidth: bar.width - normalWidth*(navigBar.count-1)

        Rectangle {
            id: highlighter
            width: bar.normalWidth * 2
            height: 4 * Devices.density
            anchors.bottom: parent.bottom
            color: currentPage? currentPage.textColor : "#333"
            x: back.currentIndex * bar.normalWidth + (bar.selectedWidth - width)/2

            Behavior on x {
                NumberAnimation { easing.type: Easing.OutBack; duration: back.animDuration }
            }
            Behavior on color {
                ColorAnimation { easing.type: Easing.OutCubic; duration: back.animDuration }
            }
        }

        Repeater {
            id: repeater
            model: back.children
            Item {
                id: btn
                x: {
                    var res = bar.normalWidth * index
                    if(back.currentIndex >= 0 && index > back.currentIndex)
                        res = res - bar.normalWidth + bar.selectedWidth
                    return res
                }
                width: selected? bar.selectedWidth : bar.normalWidth
                height: bar.height

                property FancyPage page: repeater.model[index]
                readonly property bool selected: index == back.currentIndex
                onSelectedChanged: {
                    if(selected) {
                        if(back.lastCurrentIndex < index)
                            page.openFromRight()
                        else
                            page.openFromLeft()
                    } else {
                        if(back.currentIndex < index)
                            page.closeToRight()
                        else
                            page.closeToLeft()
                    }
                }

                Behavior on x {
                    NumberAnimation { easing.type: Easing.OutBack; duration: back.animDuration }
                }
                Behavior on width {
                    NumberAnimation { easing.type: Easing.OutBack; duration: back.animDuration }
                }


                Text {
                    anchors.centerIn: parent
                    font: btn.page.font
                    color: currentPage.textColor
                    text: btn.page.title
                    scale: btn.selected? 1.0 : 0.6

                    Behavior on scale {
                        NumberAnimation { easing.type: Easing.OutBack; duration: back.animDuration }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: navigBar.currentIndex = index
                }

                Timer {
                    interval: 50
                    running: true
                    repeat: false
                    onTriggered: page.init(btn.selected)
                }
            }
        }
    }
}
