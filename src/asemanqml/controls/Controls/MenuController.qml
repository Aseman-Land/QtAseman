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

import QtQuick 2.9
import AsemanQml.Base 2.0

Item {
    id: menuc
    width: 100
    height: 62

    property real ratio: 0
    property variant source
    property int layoutDirection: View.layoutDirection
    property alias isVisible: marea.isVisible
    property alias menuTopMargin: menu_frame.y
    property alias pressed: marea.pressed
    property alias animating: anim_timer.running
    property real handleWidth: 20*Devices.density
    property Component component
    property real menuWidth: {
        var res = Devices.isMobile? width-100*Devices.density : width/2 + 20*Devices.density
        if(res > 250*Devices.density)
            res = 250*Devices.density
        return res
    }

    onSourceChanged: refreshSource()
    onRatioChanged: refresh()
    onLayoutDirectionChanged: {
        refreshSource()
        refresh()
    }

    onPressedChanged: if(!pressed) anim_timer.restart()

    onIsVisibleChanged: {
        if(isVisible)
            BackHandler.pushHandler(menuc, menuc.close)
        else
            BackHandler.removeHandler(menuc)
    }

    onComponentChanged: {
        if(privates.item)
            privates.item.destroy()
        if(!component)
            return

        privates.item = component.createObject(menu_frame)
    }

    Timer {
        id: anim_timer
        interval: 400
    }

    Behavior on ratio {
        NumberAnimation{easing.type: Easing.OutCubic; duration: marea.animation? 400 : 0}
    }

    QtObject {
        id: privates
        property variant item
        property real sourceScale: (menuc.width-menuWidth*(ratio/2))/source.width
    }

    Scale {
        id: sourceScaleItem
        origin.x: {
            if(!source)
                return menuc.width

            switch(layoutDirection) {
            case Qt.RightToLeft:
                return -source.width
            default:
                return source.width*2
            }
        }
        origin.y: menuc.height/2
        xScale: privates.sourceScale
        yScale: xScale
    }

    Item {
        width: parent.width
        height: parent.height
        transform: Scale { origin.x: width/2; origin.y: height/2; xScale: layoutDirection==Qt.LeftToRight?1:-1}

        MouseArea {
            id: marea
            width: isVisible? parent.width : handleWidth
            height: parent.height

            property real pinX: 0
            property bool animation: true
            property bool isVisible: false
            property bool moved: false

            onPressed: {
                pinX = mouseX
                moved = false
            }

            onMouseXChanged: {
                if(!source)
                    return
                var delta = mouseX - pinX
                if(Math.abs(delta) < 5*Devices.density && !moved)
                    return

                moved = true
                if(isVisible) delta += menuWidth
                animation = false
                show(delta)
                animation = true
            }

            onReleased: {
                var delta = (mouseX - pinX)
                if(!moved) {
                    show(0)
                    isVisible = false
                    return
                }

                if(isVisible) delta += menuWidth
                if(delta > menuWidth*(isVisible?0.8:0.2)) {
                    show(menuWidth)
                    isVisible = true
                } else {
                    show(0)
                    isVisible = false
                }
            }

            function show(size) {
                if(size > menuWidth)
                    size = menuWidth
                if(size<0)
                    size = 0

                menuc.ratio = Math.abs(size/menuWidth)
            }
        }
    }

    Item {
        x: layoutDirection==Qt.RightToLeft? parent.width-width : 0
        height: parent.height
        width: menuc.ratio*menuWidth
        clip: true

        MouseArea {
            anchors.fill: parent
        }

        Item {
            id: menu_frame
            height: parent.height - y
            width: menuWidth
            x: layoutDirection==Qt.RightToLeft? parent.width-width : 0
        }
    }

    function refreshSource() {
        if(!source)
            return

        source.transform = sourceScaleItem
    }

    function refresh() {
        if(!source)
            return

        var sourceX = menuWidth*ratio/2
        if(layoutDirection == Qt.RightToLeft)
            sourceX = -sourceX

        source.x = sourceX
    }

    function close() {
        marea.show(0)
        marea.isVisible = false
    }

    function show() {
        marea.show(menuWidth)
        marea.isVisible = true
    }
}
