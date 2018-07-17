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

/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import AsemanQml.Base 2.0

Item {
    id: container

    property Flickable scrollArea
    property int orientation: Qt.Vertical
    property alias color: bilbilak.color
    property alias pressed: marea.pressed
    property bool reverse

    opacity: 1

    function position()
    {
        var ny = 0;
        if (container.orientation == Qt.Vertical)
            ny = scrollArea.visibleArea.yPosition * container.height;
        else
            ny = scrollArea.visibleArea.xPosition * container.width;
        if (ny > 2) return ny; else return 2;
    }

    function size()
    {
        var nh, ny;

        if (container.orientation == Qt.Vertical)
            nh = scrollArea.visibleArea.heightRatio * container.height;
        else
            nh = scrollArea.visibleArea.widthRatio * container.width;

        if (container.orientation == Qt.Vertical)
            ny = scrollArea.visibleArea.yPosition * container.height;
        else
            ny = scrollArea.visibleArea.xPosition * container.width;

        if (ny > 3) {
            var t;
            if (container.orientation == Qt.Vertical)
                t = Math.ceil(container.height - 3 - ny);
            else
                t = Math.ceil(container.width - 3 - ny);
            if (nh > t) return t; else return nh;
        } else return nh + ny;
    }

    Rectangle {
        id: bilbilak
        color: "#000000"
        smooth: true
        radius: 2*Devices.density
        x: container.orientation == Qt.Vertical ? 2 : position()
        width: container.orientation == Qt.Vertical ? (marea.containsMouse||marea.pressed? 1.5*(container.width-3) : container.width - 4) : diagonal
        y: container.orientation == Qt.Vertical ? position() : 2
        height: container.orientation == Qt.Vertical ? diagonal : container.height - 4
        opacity: marea.containsMouse? 1 : 0.5
        visible: scrollArea.visibleArea.heightRatio != 1

        property real diagonal: size()<20*Devices.density? 20*Devices.density : size()

        Behavior on width {
            NumberAnimation{easing.type: Easing.OutCubic; duration: 300}
        }

        MouseArea {
            id: marea
            anchors.fill: parent
            anchors.leftMargin: container.orientation == Qt.Vertical? -4 : 0
            anchors.rightMargin: anchors.leftMargin
            anchors.topMargin: container.orientation == Qt.Vertical? 0 : -4
            anchors.bottomMargin: anchors.topMargin
            hoverEnabled: true
            onPressed: pinY = mouseY
            onMouseYChanged: {
                if( !pressed )
                    return

                var cy = scrollArea.contentY + (mouseY-pinY)/scrollArea.visibleArea.heightRatio
                var pad
                if(reverse) {
                    pad = scrollArea.originY+scrollArea.contentHeight
                    if( cy > -scrollArea.height+pad )
                        cy = -scrollArea.height+pad
                    else
                    if( cy < -scrollArea.contentHeight+pad )
                        cy = -scrollArea.contentHeight+pad
                } else {
                    pad = scrollArea.originY
                    if( cy < -pad )
                        cy = -pad
                    else
                    if( cy > scrollArea.contentHeight - scrollArea.height + pad )
                        cy = scrollArea.contentHeight - scrollArea.height + pad
                }

                scrollArea.contentY  = cy
            }

            property real pinY
        }
    }
}
