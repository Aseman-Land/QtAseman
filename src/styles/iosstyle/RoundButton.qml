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
import QtQuick.Templates 2.12 as T
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Controls.IOSStyle 2.12
import QtQuick.Controls.IOSStyle.impl 2.12

T.RoundButton {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    topInset: 6
    leftInset: 6
    rightInset: 6
    bottomInset: 6
    padding: 12
    spacing: 6

    icon.width: 24
    icon.height: 24
    icon.color: !enabled ? IOSStyle.hintTextColor :
        flat && highlighted ? IOSStyle.accentColor :
        highlighted ? IOSStyle.primaryHighlightedTextColor : IOSStyle.foreground

    IOSStyle.elevation: flat ? control.down || control.hovered ? 2 : 0
                             : control.down ? 12 : 6
    IOSStyle.background: flat ? "transparent" : undefined

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font
        color: !control.enabled ? control.IOSStyle.hintTextColor :
            control.flat && control.highlighted ? control.IOSStyle.accentColor :
            control.highlighted ? control.IOSStyle.primaryHighlightedTextColor : control.IOSStyle.foreground
    }

    // TODO: Add a proper ripple/ink effect for mouse/touch input and focus state
    background: Rectangle {
        implicitWidth: control.IOSStyle.buttonHeight
        implicitHeight: control.IOSStyle.buttonHeight

        radius: control.radius
        color: !control.enabled ? control.IOSStyle.buttonDisabledColor
            : control.checked || control.highlighted ? control.IOSStyle.highlightedButtonColor : control.IOSStyle.buttonColor

        Rectangle {
            width: parent.width
            height: parent.height
            radius: control.radius
            visible: control.hovered || control.visualFocus
            color: control.IOSStyle.rippleColor
        }

        Rectangle {
            width: parent.width
            height: parent.height
            radius: control.radius
            visible: control.down
            color: control.IOSStyle.rippleColor
        }

        // The layer is disabled when the button color is transparent so that you can do
        // IOSStyle.background: "transparent" and get a proper flat button without needing
        // to set IOSStyle.elevation as well
        layer.enabled: control.enabled && control.IOSStyle.buttonColor.a > 0
        layer.effect: ElevationEffect {
            elevation: control.IOSStyle.elevation
        }
    }
}
