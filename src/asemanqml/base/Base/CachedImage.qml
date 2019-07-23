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
import QtGraphicalEffects 1.0

Item {
    id: cimage
    width: image.width
    height: image.height

    onWidthChanged: image.width = width
    onHeightChanged: image.height = height

    property alias radius: mask.radius
    property alias source: queueItem.source
    property alias percent: queueItem.percent
    readonly property string cachedSource: image.source

    property alias fillMode: image.fillMode
    property alias asynchronous: image.asynchronous
    property alias cache: image.cache
    property alias horizontalAlignment: image.horizontalAlignment
    property alias mirror: image.mirror
    property alias paintedHeight: image.paintedHeight
    property alias paintedWidth: image.paintedWidth
    property alias progress: image.progress
    property alias smooth: image.smooth
    property alias sourceSize: image.sourceSize
    property alias status: image.status
    property alias verticalAlignment: image.verticalAlignment

    property string fileName: Tools.md5(source) + "." + Tools.fileSuffix(source)


    Rectangle {
        id: mask
        anchors.fill: parent
        visible: false
    }

    Image {
        id: image
        source: queueItem.result
        visible: radius == 0
    }

    OpacityMask {
        anchors.fill: parent
        source: radius != 0? image : null
        maskSource: mask
        cached: true
        visible: radius != 0
    }

    FileDownloaderQueueItem {
        id: queueItem
        downloaderQueue: DownloaderQueue
        fileName: {
            if(source.length == 0)
                return ""

            return cimage.fileName
        }
    }
}
