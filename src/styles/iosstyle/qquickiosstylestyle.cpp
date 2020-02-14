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

#include "qquickiosstylestyle_p.h"

#include <QtCore/qdebug.h>
#include <QtCore/qsettings.h>
#include <QtQml/qqmlinfo.h>
#include <QtQuickControls2/private/qquickstyle_p.h>

QT_BEGIN_NAMESPACE

static const QRgb colors[] = {
    0xFFFF3B30, // Red
    0xFFFF9500, // Orange
    0xFFFFCC00, // Yellow
    0xFF4CD964, // Green
    0xFF5AC8FA, // TealBlue
    0xFF007AFF, // Blue
    0xFF5856D6, // Purple
    0xFFFF2D55  // pink
};

// If no value was inherited from a parent or explicitly set, the "global" values are used.
// The initial, default values of the globals are hard-coded here, but the environment
// variables and .conf file override them if specified.
static QQuickIOSStyleStyle::Theme globalTheme = QQuickIOSStyleStyle::Light;
static uint globalPrimary = QQuickIOSStyleStyle::Blue;
static uint globalAccent = QQuickIOSStyleStyle::Blue;
static uint globalForeground = 0xDD000000; // primaryTextColorLight
static uint globalBackground = 0xFFFAFAFA; // backgroundColorLight
// These represent whether a global foreground/background was set.
// Each style's m_hasForeground/m_hasBackground are initialized to these values.
static bool hasGlobalForeground = false;
static bool hasGlobalBackground = false;
// These represent whether or not the global color value was specified as one of the
// values that QColor accepts, as opposed to one of the pre-defined colors like Red.
static bool globalPrimaryCustom = false;
static bool globalAccentCustom = false;
static bool globalForegroundCustom = true;
static bool globalBackgroundCustom = true;
// This is global because:
// 1) The theme needs access to it to determine font sizes.
// 2) There can only be one variant used for the whole application.
static QQuickIOSStyleStyle::Variant globalVariant = QQuickIOSStyleStyle::Normal;

static const QRgb backgroundColorLight = 0xFFFAFAFA;
static const QRgb backgroundColorDark = 0xFF303030;
static const QRgb dialogColorLight = 0xFFFFFFFF;
static const QRgb dialogColorDark = 0xFF424242;
static const QRgb primaryTextColorLight = 0xFF007AFF;
static const QRgb primaryTextColorDark = 0xFFFFFFFF;
static const QRgb secondaryTextColorLight = 0xFFB7B7B7;
static const QRgb secondaryTextColorDark = 0xB2FFFFFF;
static const QRgb hintTextColorLight = 0xFF8c8c93;
static const QRgb hintTextColorDark = 0x4CFFFFFF;
static const QRgb dividerColorLight = 0x1E000000;
static const QRgb dividerColorDark = 0x1EFFFFFF;
static const QRgb iconColorLight = 0x89000000;
static const QRgb iconColorDark = 0xFFFFFFFF;
static const QRgb iconDisabledColorLight = 0x42000000;
static const QRgb iconDisabledColorDark = 0x4CFFFFFF;
static const QRgb raisedButtonBorderColorLight = 0xFF007AFF;
static const QRgb raisedButtonColorLight = 0xFF007AFF;
static const QRgb raisedButtonColorDark = 0x3FCCCCCC;
static const QRgb raisedButtonDisabledColorLight = 0xFFe7e7ed;
static const QRgb raisedButtonDisabledColorDark = dividerColorDark;
static const QRgb frameColorLight = hintTextColorLight;
static const QRgb frameColorDark = hintTextColorDark;
static const QRgb sliderForegroundColorLight = 0xFFB7B7B7;
static const QRgb switchUncheckedTrackColorLight = 0xFFFFFFFF;
static const QRgb switchUncheckedTrackColorDark = 0x4CFFFFFF;
static const QRgb switchDisabledTrackColorLight = 0x1E000000;
static const QRgb switchDisabledTrackColorDark = 0x19FFFFFF;
static const QRgb switchBorderColorLight = 0xFFE5E5E5;
static const QRgb rippleColorLight = 0x10000000;
static const QRgb rippleColorDark = 0x20FFFFFF;
static const QRgb spinBoxDisabledIconColorLight = 0xFFCCCCCC;
static const QRgb spinBoxDisabledIconColorDark = 0xFF666666;

static QQuickIOSStyleStyle::Theme effectiveTheme(QQuickIOSStyleStyle::Theme theme)
{
    if (theme == QQuickIOSStyleStyle::System)
        theme = QQuickStylePrivate::isDarkSystemTheme() ? QQuickIOSStyleStyle::Dark : QQuickIOSStyleStyle::Light;
    return theme;
}

QQuickIOSStyleStyle::QQuickIOSStyleStyle(QObject *parent) : QQuickAttachedObject(parent),
    m_customPrimary(globalPrimaryCustom),
    m_customAccent(globalAccentCustom),
    m_customForeground(globalForegroundCustom),
    m_customBackground(globalBackgroundCustom),
    m_hasForeground(hasGlobalForeground),
    m_hasBackground(hasGlobalBackground),
    m_theme(globalTheme),
    m_primary(globalPrimary),
    m_accent(globalAccent),
    m_foreground(globalForeground),
    m_background(globalBackground)
{
    QQuickAttachedObject::init();
}

QQuickIOSStyleStyle *QQuickIOSStyleStyle::qmlAttachedProperties(QObject *object)
{
    return new QQuickIOSStyleStyle(object);
}

QQuickIOSStyleStyle::Theme QQuickIOSStyleStyle::theme() const
{
    return m_theme;
}

void QQuickIOSStyleStyle::setTheme(Theme theme)
{
    if (theme == System)
        theme = QQuickStylePrivate::isDarkSystemTheme() ? Dark : Light;

    m_explicitTheme = true;
    if (m_theme == theme)
        return;

    m_theme = theme;
    propagateTheme();
    emit themeChanged();
    emit paletteChanged();
    if (!m_customAccent)
        emit accentChanged();
    if (!m_hasBackground)
        emit backgroundChanged();
    if (!m_hasForeground)
        emit foregroundChanged();
}

void QQuickIOSStyleStyle::inheritTheme(Theme theme)
{
    if (m_explicitTheme || m_theme == theme)
        return;

    m_theme = theme;
    propagateTheme();
    emit themeChanged();
    emit paletteChanged();
    if (!m_customAccent)
        emit accentChanged();
    if (!m_hasBackground)
        emit backgroundChanged();
    if (!m_hasForeground)
        emit foregroundChanged();
}

void QQuickIOSStyleStyle::propagateTheme()
{
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(child);
        if (iosstyle)
            iosstyle->inheritTheme(m_theme);
    }
}

void QQuickIOSStyleStyle::resetTheme()
{
    if (!m_explicitTheme)
        return;

    m_explicitTheme = false;
    QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(attachedParent());
    inheritTheme(iosstyle ? iosstyle->theme() : globalTheme);
}

QVariant QQuickIOSStyleStyle::primary() const
{
    return primaryColor();
}

void QQuickIOSStyleStyle::setPrimary(const QVariant &var)
{
    QRgb primary = 0;
    bool custom = false;
    if (!variantToRgba(var, "primary", &primary, &custom))
        return;

    m_explicitPrimary = true;
    if (m_primary == primary)
        return;

    m_customPrimary = custom;
    m_primary = primary;
    propagatePrimary();
    emit primaryChanged();
    emit paletteChanged();
}

void QQuickIOSStyleStyle::inheritPrimary(uint primary, bool custom)
{
    if (m_explicitPrimary || m_primary == primary)
        return;

    m_customPrimary = custom;
    m_primary = primary;
    propagatePrimary();
    emit primaryChanged();
    emit paletteChanged();
}

void QQuickIOSStyleStyle::propagatePrimary()
{
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(child);
        if (iosstyle)
            iosstyle->inheritPrimary(m_primary, m_customPrimary);
    }
}

void QQuickIOSStyleStyle::resetPrimary()
{
    if (!m_explicitPrimary)
        return;

    m_customPrimary = false;
    m_explicitPrimary = false;
    QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(attachedParent());
    if (iosstyle)
        inheritPrimary(iosstyle->m_primary, iosstyle->m_customPrimary);
    else
        inheritPrimary(globalPrimary, false);
}

QVariant QQuickIOSStyleStyle::accent() const
{
    return accentColor();
}

void QQuickIOSStyleStyle::setAccent(const QVariant &var)
{
    QRgb accent = 0;
    bool custom = false;
    if (!variantToRgba(var, "accent", &accent, &custom))
        return;

    m_explicitAccent = true;
    if (m_accent == accent)
        return;

    m_customAccent = custom;
    m_accent = accent;
    propagateAccent();
    emit accentChanged();
    emit paletteChanged();
}

void QQuickIOSStyleStyle::inheritAccent(uint accent, bool custom)
{
    if (m_explicitAccent || m_accent == accent)
        return;

    m_customAccent = custom;
    m_accent = accent;
    propagateAccent();
    emit accentChanged();
    emit paletteChanged();
}

void QQuickIOSStyleStyle::propagateAccent()
{
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(child);
        if (iosstyle)
            iosstyle->inheritAccent(m_accent, m_customAccent);
    }
}

void QQuickIOSStyleStyle::resetAccent()
{
    if (!m_explicitAccent)
        return;

    m_customAccent = false;
    m_explicitAccent = false;
    QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(attachedParent());
    if (iosstyle)
        inheritAccent(iosstyle->m_accent, iosstyle->m_customAccent);
    else
        inheritAccent(globalAccent, false);
}

QVariant QQuickIOSStyleStyle::foreground() const
{
    if (!m_hasForeground)
        return QColor::fromRgba(m_theme == Light ? primaryTextColorLight : primaryTextColorDark);
    if (m_customForeground)
        return QColor::fromRgba(m_foreground);
//    if (m_foreground > BlueGrey)
//        return QColor();
    return QColor::fromRgba(colors[m_foreground]);
}

void QQuickIOSStyleStyle::setForeground(const QVariant &var)
{
    QRgb foreground = 0;
    bool custom = false;
    if (!variantToRgba(var, "foreground", &foreground, &custom))
        return;

    m_hasForeground = true;
    m_explicitForeground = true;
    if (m_foreground == foreground)
        return;

    m_customForeground = custom;
    m_foreground = foreground;
    propagateForeground();
    emit foregroundChanged();
}

void QQuickIOSStyleStyle::inheritForeground(uint foreground, bool custom, bool has)
{
    if (m_explicitForeground || m_foreground == foreground)
        return;

    m_hasForeground = has;
    m_customForeground = custom;
    m_foreground = foreground;
    propagateForeground();
    emit foregroundChanged();
}

void QQuickIOSStyleStyle::propagateForeground()
{
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(child);
        if (iosstyle)
            iosstyle->inheritForeground(m_foreground, m_customForeground, m_hasForeground);
    }
}

void QQuickIOSStyleStyle::resetForeground()
{
    if (!m_explicitForeground)
        return;

    m_hasForeground = false;
    m_customForeground = false;
    m_explicitForeground = false;
    QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(attachedParent());
    inheritForeground(iosstyle ? iosstyle->m_foreground : globalForeground, true, iosstyle ? iosstyle->m_hasForeground : false);
}

QVariant QQuickIOSStyleStyle::background() const
{
    return backgroundColor();
}

void QQuickIOSStyleStyle::setBackground(const QVariant &var)
{
    QRgb background = 0;
    bool custom = false;
    if (!variantToRgba(var, "background", &background, &custom))
        return;

    m_hasBackground = true;
    m_explicitBackground = true;
    if (m_background == background)
        return;

    m_customBackground = custom;
    m_background = background;
    propagateBackground();
    emit backgroundChanged();
    emit paletteChanged();
}

void QQuickIOSStyleStyle::inheritBackground(uint background, bool custom, bool has)
{
    if (m_explicitBackground || m_background == background)
        return;

    m_hasBackground = has;
    m_customBackground = custom;
    m_background = background;
    propagateBackground();
    emit backgroundChanged();
    emit paletteChanged();
}

void QQuickIOSStyleStyle::propagateBackground()
{
    const auto styles = attachedChildren();
    for (QQuickAttachedObject *child : styles) {
        QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(child);
        if (iosstyle)
            iosstyle->inheritBackground(m_background, m_customBackground, m_hasBackground);
    }
}

void QQuickIOSStyleStyle::resetBackground()
{
    if (!m_explicitBackground)
        return;

    m_hasBackground = false;
    m_customBackground = false;
    m_explicitBackground = false;
    QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(attachedParent());
    inheritBackground(iosstyle ? iosstyle->m_background : globalBackground, true, iosstyle ? iosstyle->m_hasBackground : false);
}

int QQuickIOSStyleStyle::elevation() const
{
    return m_elevation;
}

void QQuickIOSStyleStyle::setElevation(int elevation)
{
    if (m_elevation == elevation)
        return;

    m_elevation = elevation;
    emit elevationChanged();
}

void QQuickIOSStyleStyle::resetElevation()
{
    setElevation(0);
}

QColor QQuickIOSStyleStyle::primaryColor() const
{
    if (m_customPrimary)
        return QColor::fromRgba(m_primary);
//    if (m_primary > BlueGrey)
//        return QColor();
    return colors[m_primary];
}

QColor QQuickIOSStyleStyle::accentColor() const
{
    if (m_customAccent)
        return QColor::fromRgba(m_accent);
//    if (m_accent > BlueGrey)
//        return QColor();
    return colors[m_accent];
}

QColor QQuickIOSStyleStyle::backgroundColor() const
{
    if (!m_hasBackground)
        return QColor::fromRgba(m_theme == Light ? backgroundColorLight : backgroundColorDark);
    if (m_customBackground)
        return QColor::fromRgba(m_background);
//    if (m_background > BlueGrey)
//        return QColor();
    return colors[m_background];
}

QColor QQuickIOSStyleStyle::primaryTextColor() const
{
    return QColor::fromRgba(m_theme == Light ? primaryTextColorLight : primaryTextColorDark);
}

QColor QQuickIOSStyleStyle::primaryHighlightedTextColor() const
{
    return QColor::fromRgba(primaryTextColorDark);
}

QColor QQuickIOSStyleStyle::secondaryTextColor() const
{
    return QColor::fromRgba(m_theme == Light ? secondaryTextColorLight : secondaryTextColorDark);
}

QColor QQuickIOSStyleStyle::hintTextColor() const
{
    return QColor::fromRgba(m_theme == Light ? hintTextColorLight : hintTextColorDark);
}

QColor QQuickIOSStyleStyle::textSelectionColor() const
{
    QColor color = accentColor();
    color.setAlphaF(0.4);
    return color;
}

QColor QQuickIOSStyleStyle::dropShadowColor() const
{
    return QColor::fromRgba(0x40000000);
}

QColor QQuickIOSStyleStyle::dividerColor() const
{
    return QColor::fromRgba(m_theme == Light ? dividerColorLight : dividerColorDark);
}

QColor QQuickIOSStyleStyle::iconColor() const
{
    return QColor::fromRgba(m_theme == Light ? iconColorLight : iconColorDark);
}

QColor QQuickIOSStyleStyle::iconDisabledColor() const
{
    return QColor::fromRgba(m_theme == Light ? iconDisabledColorLight : iconDisabledColorDark);
}

QColor QQuickIOSStyleStyle::buttonColor(bool highlighted) const
{
    QColor color = Qt::transparent;

    if (m_explicitBackground) {
        color = backgroundColor();
    } else if (highlighted) {
        color = accentColor();
    }

    return color;
}

QColor QQuickIOSStyleStyle::buttonColor() const
{
    return buttonColor(false);
}

QColor QQuickIOSStyleStyle::buttonBorderColor() const
{
    QColor color = Qt::transparent;

    if (m_explicitBackground) {
        color = backgroundColor();
    } else {
        color = QColor::fromRgba(m_theme == Light ? raisedButtonBorderColorLight
                                                  : raisedButtonColorDark);
    }

    return color;
}

QColor QQuickIOSStyleStyle::buttonDisabledColor() const
{
    return QColor::fromRgba(m_theme == Light ? raisedButtonDisabledColorLight
                                                 : raisedButtonDisabledColorDark);
}

QColor QQuickIOSStyleStyle::highlightedButtonColor() const
{
    return buttonColor(true);
}

QColor QQuickIOSStyleStyle::frameColor() const
{
    return QColor::fromRgba(m_theme == Light ? frameColorLight : frameColorDark);
}

QColor QQuickIOSStyleStyle::rippleColor() const
{
    return QColor::fromRgba(m_theme == Light ? rippleColorLight : rippleColorDark);
}

QColor QQuickIOSStyleStyle::highlightedRippleColor() const
{
    QColor pressColor = accentColor();
    pressColor.setAlpha(m_theme == Light ? 30 : 50);
    return pressColor;
}

QColor QQuickIOSStyleStyle::switchUncheckedTrackColor() const
{
    return QColor::fromRgba(m_theme == Light ? switchUncheckedTrackColorLight : switchUncheckedTrackColorDark);
}

QColor QQuickIOSStyleStyle::switchCheckedTrackColor() const
{
    QColor color = accentColor();

    if (m_explicitBackground) {
        color = backgroundColor();
    }

    return color;
}

QColor QQuickIOSStyleStyle::switchBorderColor() const
{
    return QColor::fromRgba(switchBorderColorLight);
}

QColor QQuickIOSStyleStyle::switchHandleColor() const
{
    return Qt::white;
}

QColor QQuickIOSStyleStyle::switchDisabledTrackColor() const
{
    return QColor::fromRgba(m_theme == Light ? switchDisabledTrackColorLight : switchDisabledTrackColorDark);
}

QColor QQuickIOSStyleStyle::switchDisabledHandleColor() const
{
//    return m_theme == Light ? color(Grey, Shade400) : color(Grey, Shade800);
}

QColor QQuickIOSStyleStyle::scrollBarColor() const
{
    return QColor::fromRgba(m_theme == Light ? 0x40000000 : 0x40FFFFFF);
}

QColor QQuickIOSStyleStyle::scrollBarHoveredColor() const
{
    return QColor::fromRgba(m_theme == Light ? 0x60000000 : 0x60FFFFFF);
}

QColor QQuickIOSStyleStyle::scrollBarPressedColor() const
{
    return QColor::fromRgba(m_theme == Light ? 0x80000000 : 0x80FFFFFF);
}

QColor QQuickIOSStyleStyle::sliderBackgroundColor() const
{
    if (m_hasBackground)
        return backgroundColor();
    return accentColor();
}

QColor QQuickIOSStyleStyle::sliderForegroundColor() const
{
    return QColor::fromRgba(sliderForegroundColorLight);
}

QColor QQuickIOSStyleStyle::sliderHandleColor() const
{
    return Qt::white;
}

QColor QQuickIOSStyleStyle::dialogColor() const
{
    if (m_hasBackground)
        return backgroundColor();
    return QColor::fromRgba(m_theme == Light ? dialogColorLight : dialogColorDark);
}

QColor QQuickIOSStyleStyle::backgroundDimColor() const
{
    return QColor::fromRgba(m_theme == Light ? 0x99303030 : 0x99fafafa);
}

QColor QQuickIOSStyleStyle::listHighlightColor() const
{
    return QColor::fromRgba(m_theme == Light ? 0x1e000000 : 0x1effffff);
}

QColor QQuickIOSStyleStyle::tooltipColor() const
{
    if (m_explicitBackground)
        return backgroundColor();
//    return color(Grey);
}

QColor QQuickIOSStyleStyle::toolBarColor() const
{
    if (m_explicitBackground)
        return backgroundColor();
    return primaryColor();
}

// ??
QColor QQuickIOSStyleStyle::toolTextColor() const
{
    if (m_hasForeground || m_customPrimary)
        return primaryTextColor();

    switch (m_primary) {
    case Red:
    case Pink:
    case Purple:
    case Blue:
        return QColor::fromRgba(primaryTextColorDark);

    case Green:
    case Yellow:
    case Orange:
        return QColor::fromRgba(primaryTextColorLight);

    default:
        break;
    }

    return primaryTextColor();
}

QColor QQuickIOSStyleStyle::spinBoxDisabledIconColor() const
{
    return QColor::fromRgba(m_theme == Light ? spinBoxDisabledIconColorLight : spinBoxDisabledIconColorDark);
}

QColor QQuickIOSStyleStyle::color(QQuickIOSStyleStyle::Color color) const
{
    int count = sizeof(colors) / sizeof(colors[0]);
    if (color < 0 || color >= count)
        return QColor();

//    count = sizeof(colors[0]) / sizeof(colors[0][0]);
//    if (shade < 0 || shade >= count)
//        return QColor();

    return colors[color];
}

static QColor lighterShade(const QColor &color, qreal amount)
{
    QColor hsl = color.toHsl();
    hsl.setHslF(hsl.hueF(), hsl.saturationF(), qBound<qreal>(0.0, hsl.lightnessF() + amount, 1.0), color.alphaF());
    return hsl.convertTo(color.spec());
}

static QColor darkerShade(const QColor &color, qreal amount)
{
    QColor hsl = color.toHsl();
    hsl.setHslF(hsl.hueF(), hsl.saturationF(), qBound<qreal>(0.0, hsl.lightnessF() - amount, 1.0), color.alphaF());
    return hsl.convertTo(color.spec());
}

/*
 * The following lightness values originate from the IOSStyle Design Color Generator project.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 mbitson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

int QQuickIOSStyleStyle::touchTarget() const
{
    // https://iosstyle.io/guidelines/components/buttons.html#buttons-style
    return globalVariant == Dense ? 44 : 48;
}

int QQuickIOSStyleStyle::buttonHeight() const
{
    // https://iosstyle.io/guidelines/components/buttons.html#buttons-style
    return globalVariant == Dense ? 32 : 36;
}

int QQuickIOSStyleStyle::delegateHeight() const
{
    // https://iosstyle.io/guidelines/components/lists.html#lists-specs
    return globalVariant == Dense ? 40 : 48;
}

int QQuickIOSStyleStyle::dialogButtonBoxHeight() const
{
    return globalVariant == Dense ? 48 : 52;
}

int QQuickIOSStyleStyle::frameVerticalPadding() const
{
    return globalVariant == Dense ? 8 : 12;
}

int QQuickIOSStyleStyle::menuItemHeight() const
{
    // https://iosstyle.io/guidelines/components/menus.html#menus-simple-menus
    return globalVariant == Dense ? 32 : 48;
}

int QQuickIOSStyleStyle::menuItemVerticalPadding() const
{
    return globalVariant == Dense ? 8 : 12;
}

int QQuickIOSStyleStyle::switchDelegateVerticalPadding() const
{
    // SwitchDelegate's indicator is much larger than the others due to the shadow,
    // so we must reduce its padding to ensure its implicitHeight is 40 when dense.
    return globalVariant == Dense ? 4 : 8;
}

int QQuickIOSStyleStyle::tooltipHeight() const
{
    // https://iosstyle.io/guidelines/components/tooltips.html
    return globalVariant == Dense ? 22 : 32;
}

QQuickIOSStyleStyle::Variant QQuickIOSStyleStyle::variant()
{
    return globalVariant;
}

template <typename Enum>
static Enum toEnumValue(const QByteArray &value, bool *ok)
{
    QMetaEnum enumeration = QMetaEnum::fromType<Enum>();
    return static_cast<Enum>(enumeration.keyToValue(value, ok));
}

static QByteArray resolveSetting(const QByteArray &env, const QSharedPointer<QSettings> &settings, const QString &name)
{
    QByteArray value = qgetenv(env);
#if QT_CONFIG(settings)
    if (value.isNull() && !settings.isNull())
        value = settings->value(name).toByteArray();
#endif
    return value;
}

void QQuickIOSStyleStyle::initGlobals()
{
    QSharedPointer<QSettings> settings = QQuickStylePrivate::settings(QStringLiteral("IOSStyle"));

    bool ok = false;
    QByteArray themeValue = resolveSetting("QT_QUICK_CONTROLS_IOSSTYLE_THEME", settings, QStringLiteral("Theme"));
    Theme themeEnum = toEnumValue<Theme>(themeValue, &ok);
    if (ok)
        globalTheme = effectiveTheme(themeEnum);
    else if (!themeValue.isEmpty())
        qWarning().nospace().noquote() << "IOSStyle: unknown theme value: " << themeValue;

    QByteArray variantValue = resolveSetting("QT_QUICK_CONTROLS_IOSSTYLE_VARIANT", settings, QStringLiteral("Variant"));
    Variant variantEnum = toEnumValue<Variant>(variantValue, &ok);
    if (ok)
        globalVariant = variantEnum;
    else if (!variantValue.isEmpty())
        qWarning().nospace().noquote() << "IOSStyle: unknown variant value: " << variantValue;

    QByteArray primaryValue = resolveSetting("QT_QUICK_CONTROLS_IOSSTYLE_PRIMARY", settings, QStringLiteral("Primary"));
    Color primaryEnum = toEnumValue<Color>(primaryValue, &ok);
    if (ok) {
        globalPrimaryCustom = false;
        globalPrimary = primaryEnum;
    } else {
        QColor color(primaryValue.constData());
        if (color.isValid()) {
            globalPrimaryCustom = true;
            globalPrimary = color.rgba();
        } else if (!primaryValue.isEmpty()) {
            qWarning().nospace().noquote() << "IOSStyle: unknown primary value: " << primaryValue;
        }
    }

    QByteArray accentValue = resolveSetting("QT_QUICK_CONTROLS_IOSSTYLE_ACCENT", settings, QStringLiteral("Accent"));
    Color accentEnum = toEnumValue<Color>(accentValue, &ok);
    if (ok) {
        globalAccentCustom = false;
        globalAccent = accentEnum;
    } else if (!accentValue.isEmpty()) {
        QColor color(accentValue.constData());
        if (color.isValid()) {
            globalAccentCustom = true;
            globalAccent = color.rgba();
        } else {
            qWarning().nospace().noquote() << "IOSStyle: unknown accent value: " << accentValue;
        }
    }

    QByteArray foregroundValue = resolveSetting("QT_QUICK_CONTROLS_IOSSTYLE_FOREGROUND", settings, QStringLiteral("Foreground"));
    Color foregroundEnum = toEnumValue<Color>(foregroundValue, &ok);
    if (ok) {
        globalForegroundCustom = false;
        globalForeground = foregroundEnum;
        hasGlobalForeground = true;
    } else if (!foregroundValue.isEmpty()) {
        QColor color(foregroundValue.constData());
        if (color.isValid()) {
            globalForegroundCustom = true;
            globalForeground = color.rgba();
            hasGlobalForeground = true;
        } else {
            qWarning().nospace().noquote() << "IOSStyle: unknown foreground value: " << foregroundValue;
        }
    }

    QByteArray backgroundValue = resolveSetting("QT_QUICK_CONTROLS_IOSSTYLE_BACKGROUND", settings, QStringLiteral("Background"));
    Color backgroundEnum = toEnumValue<Color>(backgroundValue, &ok);
    if (ok) {
        globalBackgroundCustom = false;
        globalBackground = backgroundEnum;
        hasGlobalBackground = true;
    } else if (!backgroundValue.isEmpty()) {
        QColor color(backgroundValue.constData());
        if (color.isValid()) {
            globalBackgroundCustom = true;
            globalBackground = color.rgba();
            hasGlobalBackground = true;
        } else {
            qWarning().nospace().noquote() << "IOSStyle: unknown background value: " << backgroundValue;
        }
    }
}

void QQuickIOSStyleStyle::attachedParentChange(QQuickAttachedObject *newParent, QQuickAttachedObject *oldParent)
{
    Q_UNUSED(oldParent);
    QQuickIOSStyleStyle *iosstyle = qobject_cast<QQuickIOSStyleStyle *>(newParent);
    if (iosstyle) {
        inheritPrimary(iosstyle->m_primary, iosstyle->m_customPrimary);
        inheritAccent(iosstyle->m_accent, iosstyle->m_customAccent);
        inheritForeground(iosstyle->m_foreground, iosstyle->m_customForeground, iosstyle->m_hasForeground);
        inheritBackground(iosstyle->m_background, iosstyle->m_customBackground, iosstyle->m_hasBackground);
        inheritTheme(iosstyle->theme());
    }
}

bool QQuickIOSStyleStyle::variantToRgba(const QVariant &var, const char *name, QRgb *rgba, bool *custom) const
{
    *custom = false;
    if (var.type() == QVariant::Int) {
        int val = var.toInt();
//        if (val > BlueGrey) {
//            qmlWarning(parent()) << "unknown IOSStyle." << name << " value: " << val;
//            return false;
//        }
        *rgba = val;
    } else {
        int val = QMetaEnum::fromType<Color>().keyToValue(var.toByteArray());
        if (val != -1) {
            *rgba = val;
        } else {
            QColor color(var.toString());
            if (!color.isValid()) {
                qmlWarning(parent()) << "unknown IOSStyle." << name << " value: " << var.toString();
                return false;
            }
            *custom = true;
            *rgba = color.rgba();
        }
    }
    return true;
}

QT_END_NAMESPACE
