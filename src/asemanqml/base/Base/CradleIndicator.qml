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
    width: 300*Devices.density
    height: 10*Devices.density

    property real count: 6

    CradleBits{
        id: bit_0
        index: 0
    }
    CradleBits{
        id: bit_1
        index: 1
    }
    CradleBits{
        id: bit_2
        index: 2
    }
    CradleBits{
        id: bit_3
        index: 3
    }
    CradleBits{
        id: bit_4
        index: 4
    }
    CradleBits{
        id: bit_5
        index: 5
    }

    Timer{
        id: poke_timer_1
        interval: 1000
        repeat: true
        onTriggered: {
            bit_0.poke()
            bit_1.poke()
            poke_timer_2.start()
        }
    }

    Timer{
        id: poke_timer_2
        interval: 500
        repeat: false
        onTriggered: {
            bit_4.poke()
            bit_5.poke()
        }
    }

    Component.onCompleted: {
        bit_0.poke()
        bit_1.poke()
        poke_timer_2.start()
        poke_timer_1.start()
    }
}
