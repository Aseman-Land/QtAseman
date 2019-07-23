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
import QtGraphicalEffects 1.0

Item {
    width: sourceSize.width
    height: sourceSize.height

    property alias radius: mask.radius
    property alias asynchronous: img.asynchronous
    property alias cache: img.cache
    property alias fillMode: img.fillMode
    property alias horizontalAlignment: img.horizontalAlignment
    property alias mirror: img.mirror
    property alias paintedHeight: img.paintedHeight
    property alias paintedWidth: img.paintedWidth
    property alias progress: img.progress
    property alias smooth: img.smooth
    property alias source: img.source
    property alias sourceSize: img.sourceSize
    property alias status: img.status
    property alias verticalAlignment: img.verticalAlignment

    Rectangle {
        id: mask
        anchors.fill: parent
        visible: false
    }

    Image {
        id: img
        anchors.fill: parent
        visible: false
    }

    OpacityMask {
        anchors.fill: parent
        source: img
        maskSource: mask
    }
}
