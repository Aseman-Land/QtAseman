/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import AsemanQml.Base 2.0

Item {
    id: pmanager
    clip: true

    property Component mainComponent
    property alias mainItem: scene.itemObject
    readonly property variant currentItem: {
        if(list.count == 0)
            return scene.itemObject
        else
            return list.last().itemObject
    }

    property int animationDuration: 400
    property int easingType: Easing.OutCubic
    property alias count: list.count

    property int layoutDirection: View.layoutDirection
    property int direction: Qt.Horizontal

    onMainComponentChanged: {
        if(mainItem)
            mainItem.destroy()

        mainItem = mainComponent.createObject(scene)
    }

    ListObject {
        id: list

        function lastItem() {
            if(count == 0)
                return scene
            else
                return last()
        }
    }

    Item {
        id: scene
        width: parent.width
        height: parent.height

        property real xPadding: 0

        x: {
            if(pmanager.direction != Qt.Horizontal)
                return 0

            switch(pmanager.layoutDirection) {
            case Qt.LeftToRight:
                return (closed? -width/3 + scene.xPadding/3 : 0)
                break

            case Qt.RightToLeft:
                return (closed? width/3 + scene.xPadding/3 : 0)
                break
            }
        }
        scale: {
            if(pmanager.direction == Qt.Horizontal)
                return 1
            else
                return closed? 0.9 : 1
        }
        transformOrigin: Item.Bottom

        clip: true

        Behavior on x {
            NumberAnimation{easing.type: easingType; duration: animationDuration}
        }
        Behavior on scale {
            NumberAnimation{easing.type: easingType; duration: animationDuration}
        }

        property variant itemObject
        property bool closed
    }

    function append(component, properties) {
        var last = list.lastItem()
        var iscene = item_component.createObject(pmanager)

        last.closed = true
        list.append(iscene)

        iscene.itemObject = properties? component.createObject(iscene.itemScene, properties) : component.createObject(iscene.itemScene)
        return iscene.itemObject
    }

    Component {
        id: item_component
        Item {
            id: item
            width: parent.width
            height: parent.height
            clip: true

            property real xPadding: 0
            property alias itemScene: item_scene
            property variant itemObject
            property bool opened: false
            property bool closed: false

            MouseArea {
                anchors.fill: parent
            }

            Rectangle {
                anchors.fill: parent
                color: "#000000"
                opacity: opened? 0.5 * (1-itemBackable.closeRatio) : 0

                Behavior on opacity {
                    NumberAnimation{easing.type: easingType; duration: animationDuration}
                }
            }

            ItemBackable {
                id: itemBackable
                width: parent.width
                height: parent.height
                active: pmanager.direction == Qt.Horizontal
                animationDuration: pmanager.animationDuration
                onOpenedChanged: {
                    if(opened)
                        return

                    item.back()
                }
                onXChanged: {
                    if(list.count > 1)
                        list.at(list.count-2).xPadding = x
                    else
                        scene.xPadding = x
                }

                Rectangle {
                    id: item_scene
                    width: parent.width
                    height: parent.height
                    x: {
                        if(item.opened && !item.closed)
                            return 0
                        if(pmanager.direction != Qt.Horizontal)
                            return 0

                        switch(pmanager.layoutDirection) {
                        case Qt.LeftToRight:
                            return (item.closed? -item.width/3 + scene.xPadding/3 : item.width)
                            break

                        case Qt.RightToLeft:
                            return (item.closed? item.width/3 + scene.xPadding/3 : -item.width)
                            break
                        }
                    }
                    y: {
                        if(item.opened && !item.closed)
                            return 0
                        if(pmanager.direction == Qt.Horizontal)
                            return 0
                        else
                            return item.closed? 0 : item.height
                    }
                    scale: {
                        if(item.opened && !item.closed)
                            return 1
                        if(pmanager.direction == Qt.Horizontal)
                            return 1
                        else
                            return closed? 0.9 : 1
                    }

                    Behavior on x {
                        NumberAnimation{easing.type: easingType; duration: animationDuration}
                    }
                    Behavior on y {
                        NumberAnimation{easing.type: easingType; duration: animationDuration}
                    }
                    Behavior on scale {
                        NumberAnimation{easing.type: easingType; duration: animationDuration}
                    }
                }
            }

            Timer {
                id: destroy_timer
                interval: animationDuration
                onTriggered: {
                    if(item.itemObject)
                        item.itemObject.destroy()
                    item.destroy()
                }
            }

            function back() {
                list.removeAll(item)
                list.lastItem().xPadding = 0
                list.lastItem().closed = false
                opened = false
                destroy_timer.restart()
            }

            Component.onCompleted: {
                opened = true
                BackHandler.pushHandler(item, item.back)
            }
        }
    }

    function closeLast() {
        if(list.count == 0)
            return false

        list.last().back()
        return true
    }
}
