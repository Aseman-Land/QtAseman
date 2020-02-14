/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.12
import QtQuick.Controls.IOSStyle 2.12
import QtQuick.Controls.IOSStyle.impl 2.12

Item {
    id: indicator
    implicitWidth: 38
    implicitHeight: 32

    property Item control
    property alias handle: handle

//    IOSStyle.elevation: 1

    Rectangle {
        width: parent.width
        height: 23
        radius: height / 2
        y: parent.height / 2 - height / 2
        border.color: control.enabled ? (control.checked ? control.IOSStyle.switchCheckedTrackColor : control.IOSStyle.switchBorderColor)
                                      : control.IOSStyle.switchDisabledTrackColor
        color: {
            if(!control.enabled)
                return control.IOSStyle.switchDisabledTrackColor

            var s0 = Qt.darker(control.IOSStyle.switchUncheckedTrackColor, 1.1)
            var s1 = control.IOSStyle.switchCheckedTrackColor
            var pos = control.visualPosition
            return Qt.rgba( s0.r*(1-pos) + s1.r*pos, s0.g*(1-pos) + s1.g*pos, s0.b*(1-pos) + s1.b*pos )
        }

        Behavior on color {
            ColorAnimation { easing.type: Easing.OutCubic; duration: 150 }
        }

        Rectangle {
            anchors.fill: parent
            anchors.margins: 1
            anchors.leftMargin: height/2
            color: control.IOSStyle.switchUncheckedTrackColor
            radius: height/2
            scale: 1 - control.visualPosition

            Behavior on scale {
                NumberAnimation { easing.type: Easing.OutCubic; duration: 300 }
            }
        }
    }

    FastDropShadow {
        anchors.fill: handle
        source: handle
        horizontalOffset: 0
        verticalOffset: 1.5
        radius: 4
        opacity: 0.5
        color: "#333"
    }

    Rectangle {
        id: handle
        x: Math.max(1.5, Math.min(parent.width - width, control.visualPosition * parent.width - (width / 2)) - 1.5)
        y: (parent.height - height) / 2
        width: 20
        height: 20
        radius: width / 2
        color: control.enabled ? control.IOSStyle.switchHandleColor
                               : control.IOSStyle.switchDisabledHandleColor

        Behavior on x {
            enabled: !control.pressed
            SmoothedAnimation {
                duration: 300
            }
        }
        layer.enabled: indicator.IOSStyle.elevation > 0
        layer.effect: ElevationEffect {
            elevation: indicator.IOSStyle.elevation
        }
    }
}
