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

Item {

    ColumnLayout {
        anchors.centerIn: parent

        Switch {
            text: qsTr("Switch")
        }

        SpinBox {
        }

        Slider {
            value: 0.5
        }

        CheckBox {
            text: qsTr("Check Box")
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                text: qsTr("Press Me 1")
            }

            Button {
                text: qsTr("Press Me 2")
            }
        }
    }
}
