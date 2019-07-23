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
    id: animation_item
    property bool anim: false
    property int anim_time: 250
    property alias easing: anim_item.easing

    signal animationFinished()

    Behavior on x {
        NumberAnimation { id: anim_item; easing.type: Easing.OutCubic; duration: anim? anim_time : 0 }
    }

    Timer{
        id: anim_disabler
        interval: anim_time
        repeat: false
        onTriggered: {
            anim = false
            animation_item.animationFinished()
        }
    }

    function startAnimation(){
        anim = true
        anim_disabler.start()
    }
}
