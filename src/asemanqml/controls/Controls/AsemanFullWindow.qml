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
import QtQuick.Controls 2.0
import AsemanQml.Base 2.0
import QtQuick.Controls 2.0

AsemanWindow {
    visible: true

    property alias backgroundColor: backFrame.color
    property alias pageManager: spManager
    property alias sidebar: _sidebar
    property alias headerButton: haderBtn
    property alias backVisible: haderBtn.visible
    property alias main: spManager.mainComponent
    property alias drawer: _sidebar.delegate
    property alias forceActiveBackButton: haderBtn.forceActive

    BackAction {
        id: searchAction
    }

    Rectangle {
        id: backFrame
        anchors.fill: parent
    }

    SlidePageManager {
        id: spManager
        anchors.fill: parent
    }

    SideMenu {
        id: _sidebar
        anchors.fill: parent
        source: spManager
    }

    HeaderMenuButton {
        id: haderBtn
        ratio: {
            if(spManager.count || forceActive)
                return fakeRatio
            else
            if(sidebar.percent == 0)
                return fakeRatio
            return sidebar.percent
        }

        property bool forceActive
        property real fakeRatio: {
            if(spManager.count || forceActive)
                return 1
            else
                return 0
        }

        Behavior on fakeRatio {
            NumberAnimation{easing.type: Easing.OutCubic; duration: 300}
        }
    }
}
