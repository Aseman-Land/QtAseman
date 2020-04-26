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
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T
import QtQuick.Controls.IOSStyle 2.12
import QtQuick.Controls.IOSStyle.impl 2.12

T.ComboBox {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding,
                             implicitIndicatorHeight + topPadding + bottomPadding)

    topInset: 6
    bottomInset: 6

    leftPadding: padding + (!control.mirrored || !indicator || !indicator.visible ? 0 : indicator.width + spacing)
    rightPadding: padding + (control.mirrored || !indicator || !indicator.visible ? 0 : indicator.width + spacing)

    IOSStyle.elevation: flat ? control.pressed || control.hovered ? 2 : 0
                             : control.pressed ? 8 : 2
    IOSStyle.background: flat ? "transparent" : undefined
    IOSStyle.foreground: flat ? undefined : IOSStyle.primaryTextColor

    delegate: MenuItem {
        width: parent.width
        text: control.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
        IOSStyle.foreground: control.currentIndex === index ? parent.IOSStyle.accent : parent.IOSStyle.foreground
        highlighted: control.highlightedIndex === index
        hoverEnabled: control.hoverEnabled
    }

    indicator: ColorImage {
        x: control.mirrored ? control.padding : control.width - width - control.padding
        y: control.topPadding + (control.availableHeight - height) / 2
        color: control.enabled ? control.IOSStyle.foreground : control.IOSStyle.hintTextColor
        source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/IOSStyle/images/drop-indicator.png"
    }

    contentItem: T.TextField {
        padding: 6
        leftPadding: control.editable ? 2 : control.mirrored ? 0 : 12
        rightPadding: control.editable ? 2 : control.mirrored ? 12 : 0

        text: control.editable ? control.editText : control.displayText

        enabled: control.editable
        autoScroll: control.editable
        readOnly: control.down
        inputMethodHints: control.inputMethodHints
        validator: control.validator

        font: control.font
        color: control.enabled ? control.IOSStyle.foreground : control.IOSStyle.hintTextColor
        selectionColor: control.IOSStyle.accentColor
        selectedTextColor: control.IOSStyle.primaryHighlightedTextColor
        verticalAlignment: Text.AlignVCenter

        cursorDelegate: CursorDelegate { }
    }

    background: Item {
        implicitWidth: 120
        implicitHeight: control.IOSStyle.buttonHeight

        Rectangle {
            anchors.fill: parent
            radius: 5
            color: control.IOSStyle.foreground
            opacity: 0.1
            visible: control.editable
        }

        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: control.down || control.visualFocus || control.hovered? control.IOSStyle.accent : control.IOSStyle.foreground
            radius: 5
            opacity: 0.1
            visible: !control.editable
        }

        Rectangle {
            width: parent.width
            height: parent.height
            visible: control.pressed || control.down || control.visualFocus || control.hovered
            opacity: control.down || control.visualFocus || control.hovered? 0.5 : 1
            color: control.IOSStyle.rippleColor
            radius: 5
        }
    }

    popup: T.Popup {
        y: control.editable ? control.height - 5 : 0
        width: control.width
        height: Math.min(contentItem.implicitHeight, control.Window.height - topMargin - bottomMargin)
        transformOrigin: Item.Top
        topMargin: 12
        bottomMargin: 12
        dim: true

        IOSStyle.theme: control.IOSStyle.theme
        IOSStyle.accent: control.IOSStyle.accent
        IOSStyle.primary: control.IOSStyle.primary

        enter: Transition {
            // grow_fade_in
            NumberAnimation { property: "scale"; from: 1.1; to: 1.0; easing.type: Easing.OutQuint; duration: 220 }
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; duration: 150 }
        }

        exit: Transition {
            // shrink_fade_out
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; duration: 150 }
        }

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.delegateModel
            currentIndex: control.highlightedIndex
            highlightMoveDuration: 0

            T.ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            radius: 10
            color: parent.IOSStyle.dialogColor
        }
    }
}
