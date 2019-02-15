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

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import AsemanQml.Base 2.0

Item {
    clip: true

    SwipeView {
        id: swipeView
        width: parent.width
        anchors.top: tabBar.bottom
        anchors.bottom: parent.bottom
        onCurrentIndexChanged: {
            BackHandler.removeHandler(swipeView)
            if(currentIndex > 0)
                BackHandler.pushHandler(swipeView, function(){currentIndex = 0})
        }

        QmlControls {}
        Item {}
    }

    TabBar {
        id: tabBar
        width: parent.width
        currentIndex: swipeView.currentIndex
        onCurrentIndexChanged: swipeView.currentIndex = currentIndex

        TabButton { text: qsTr("Home") }
        TabButton { text: qsTr("Page") }
    }
}
