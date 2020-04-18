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

import QtQuick 2.14
import QtQuick.Templates 2.12 as T
import QtQuick.Controls.IOSStyle 2.12

T.BusyIndicator {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    padding: 6

    contentItem: Item {
        id: cont
        implicitWidth: 24
        implicitHeight: implicitWidth
        opacity: control.running ? 1 : 0
        Behavior on opacity { OpacityAnimator { duration: 250 } }


        Timer {
            interval: 80
            repeat: true
            running: control.running
            onTriggered: parent.rotation = (parent.rotation + 30) % 360
        }

        Repeater {
            model: 12
            Rectangle {
                property real size: parent.width

                width: 2
                height: size / 4
                radius: 16
                x: size/2 + size/2 * Math.sin(rotation * Math.PI/180).toFixed(12) - 1.28
                y: size/2 - size/2 * Math.cos(rotation * Math.PI/180).toFixed(12)
                rotation: index * 30
                antialiasing: true
                transformOrigin: Item.Top
                opacity: 1/16 * index + 4/16
                color: "grey"
            }
        }
    }
}
