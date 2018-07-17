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

Canvas {
    id: picker
    width: 100
    height: 62

    property color fillColor: "#333333"
    property color strokeColor: "#000000"

    onPaint: {
        var ctx = picker.getContext("2d");
        ctx.save();

        ctx.strokeStyle = fillColor;
        ctx.fillStyle = strokeColor
        ctx.lineWidth = 1*Devices.density
        ctx.beginPath();

        ctx.moveTo(width/2,0)
        ctx.lineTo(width,width/2)
        ctx.lineTo(width,height)
        ctx.lineTo(0,height)
        ctx.lineTo(0,width/2)
        ctx.lineTo(width/2,0)

        ctx.stroke()
        ctx.fill()
    }
}
