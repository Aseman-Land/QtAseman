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

#ifndef QQUICKIOSSTYLESTYLE_P_H
#define QQUICKIOSSTYLESTYLE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/qcolor.h>

#ifdef QT_QUICKCONTROLS2IMPL_LIB
#include <QtQuickControls2Impl/private/qquickattachedobject_p.h>
#else
#include <QtQuickControls2/private/qquickattachedobject_p.h>
#endif

QT_BEGIN_NAMESPACE

class QQuickIOSStyleStyle : public QQuickAttachedObject
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)
    Q_PROPERTY(QVariant primary READ primary WRITE setPrimary RESET resetPrimary NOTIFY primaryChanged FINAL)
    Q_PROPERTY(QVariant accent READ accent WRITE setAccent RESET resetAccent NOTIFY accentChanged FINAL)
    Q_PROPERTY(QVariant foreground READ foreground WRITE setForeground RESET resetForeground NOTIFY foregroundChanged FINAL)
    Q_PROPERTY(QVariant background READ background WRITE setBackground RESET resetBackground NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(int elevation READ elevation WRITE setElevation RESET resetElevation NOTIFY elevationChanged FINAL)

    Q_PROPERTY(QColor primaryColor READ primaryColor NOTIFY primaryChanged FINAL) // TODO: remove?
    Q_PROPERTY(QColor accentColor READ accentColor NOTIFY accentChanged FINAL) // TODO: remove?
    Q_PROPERTY(QColor backgroundColor READ backgroundColor NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(QColor primaryTextColor READ primaryTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor primaryHighlightedTextColor READ primaryHighlightedTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor hintTextColor READ hintTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor textSelectionColor READ textSelectionColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor dropShadowColor READ dropShadowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor dividerColor READ dividerColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor iconColor READ iconColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor iconDisabledColor READ iconDisabledColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor buttonColor READ buttonColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor buttonBorderColor READ buttonBorderColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor buttonDisabledColor READ buttonDisabledColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor highlightedButtonColor READ highlightedButtonColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor frameColor READ frameColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor rippleColor READ rippleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor highlightedRippleColor READ highlightedRippleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchUncheckedTrackColor READ switchUncheckedTrackColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchCheckedTrackColor READ switchCheckedTrackColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchBorderColor READ switchBorderColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchHandleColor READ switchHandleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchDisabledTrackColor READ switchDisabledTrackColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchDisabledHandleColor READ switchDisabledHandleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor scrollBarColor READ scrollBarColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor scrollBarHoveredColor READ scrollBarHoveredColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor scrollBarPressedColor READ scrollBarPressedColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor sliderBackgroundColor READ sliderBackgroundColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor sliderForegroundColor READ sliderForegroundColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor sliderHandleColor READ sliderHandleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor dialogColor READ dialogColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor backgroundDimColor READ backgroundDimColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor listHighlightColor READ listHighlightColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor tooltipColor READ tooltipColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor toolBarColor READ toolBarColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor toolTextColor READ toolTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor spinBoxDisabledIconColor READ spinBoxDisabledIconColor NOTIFY paletteChanged FINAL)

    Q_PROPERTY(int touchTarget READ touchTarget CONSTANT FINAL)
    Q_PROPERTY(int buttonHeight READ buttonHeight CONSTANT FINAL)
    Q_PROPERTY(int delegateHeight READ delegateHeight CONSTANT FINAL)
    Q_PROPERTY(int dialogButtonBoxHeight READ dialogButtonBoxHeight CONSTANT FINAL)
    Q_PROPERTY(int frameVerticalPadding READ frameVerticalPadding CONSTANT FINAL)
    Q_PROPERTY(int menuItemHeight READ menuItemHeight CONSTANT FINAL)
    Q_PROPERTY(int menuItemVerticalPadding READ menuItemVerticalPadding CONSTANT FINAL)
    Q_PROPERTY(int switchDelegateVerticalPadding READ switchDelegateVerticalPadding CONSTANT FINAL)
    Q_PROPERTY(int tooltipHeight READ tooltipHeight CONSTANT FINAL)

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QML_NAMED_ELEMENT(IOSStyle)
    QML_ATTACHED(QQuickIOSStyleStyle)
    QML_UNCREATABLE("")
    QML_ADDED_IN_VERSION(2, 0)
#endif

public:
    enum Theme {
        Light,
        Dark,
        System
    };

    enum Variant {
        Normal,
        Dense
    };

    enum Color {
        Red,
        Orange,
        Yellow,
        Green,
        TealBlue,
        Blue,
        Purple,
        Pink
    };

    Q_ENUM(Theme)
    Q_ENUM(Variant)
    Q_ENUM(Color)

    explicit QQuickIOSStyleStyle(QObject *parent = nullptr);

    static QQuickIOSStyleStyle *qmlAttachedProperties(QObject *object);

    Theme theme() const;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void propagateTheme();
    void resetTheme();

    QVariant primary() const;
    void setPrimary(const QVariant &accent);
    void inheritPrimary(uint primary, bool custom);
    void propagatePrimary();
    void resetPrimary();

    QVariant accent() const;
    void setAccent(const QVariant &accent);
    void inheritAccent(uint accent, bool custom);
    void propagateAccent();
    void resetAccent();

    QVariant foreground() const;
    void setForeground(const QVariant &foreground);
    void inheritForeground(uint foreground, bool custom, bool has);
    void propagateForeground();
    void resetForeground();

    QVariant background() const;
    void setBackground(const QVariant &background);
    void inheritBackground(uint background, bool custom, bool has);
    void propagateBackground();
    void resetBackground();

    int elevation() const;
    void setElevation(int elevation);
    void resetElevation();

    QColor primaryColor() const;
    QColor accentColor() const;
    QColor backgroundColor() const;
    QColor primaryTextColor() const;
    QColor primaryHighlightedTextColor() const;
    QColor secondaryTextColor() const;
    QColor hintTextColor() const;
    QColor textSelectionColor() const;
    QColor dropShadowColor() const;
    QColor dividerColor() const;
    QColor iconColor() const;
    QColor iconDisabledColor() const;
    QColor buttonColor() const;
    QColor buttonBorderColor() const;
    QColor buttonDisabledColor() const;
    QColor highlightedButtonColor() const;
    QColor highlightedButtonDisabledColor() const;
    QColor frameColor() const;
    QColor rippleColor() const;
    QColor highlightedRippleColor() const;
    QColor switchUncheckedTrackColor() const;
    QColor switchCheckedTrackColor() const;
    QColor switchBorderColor() const;
    QColor switchHandleColor() const;
    QColor switchDisabledTrackColor() const;
    QColor switchDisabledHandleColor() const;
    QColor scrollBarColor() const;
    QColor scrollBarHoveredColor() const;
    QColor scrollBarPressedColor() const;
    QColor sliderBackgroundColor() const;
    QColor sliderForegroundColor() const;
    QColor sliderHandleColor() const;
    QColor dialogColor() const;
    QColor backgroundDimColor() const;
    QColor listHighlightColor() const;
    QColor tooltipColor() const;
    QColor toolBarColor() const;
    QColor toolTextColor() const;
    QColor spinBoxDisabledIconColor() const;

    Q_INVOKABLE QColor color(Color color) const;

    int touchTarget() const;
    int buttonHeight() const;
    int delegateHeight() const;
    int dialogButtonBoxHeight() const;
    int frameVerticalPadding() const;
    int menuItemHeight() const;
    int menuItemVerticalPadding() const;
    int switchDelegateVerticalPadding() const;
    int tooltipHeight() const;

    static void initGlobals();

    static Variant variant();

Q_SIGNALS:
    void themeChanged();
    void primaryChanged();
    void accentChanged();
    void foregroundChanged();
    void backgroundChanged();
    void elevationChanged();

    void paletteChanged();

protected:
    void attachedParentChange(QQuickAttachedObject *newParent, QQuickAttachedObject *oldParent) override;

private:
    void init();
    bool variantToRgba(const QVariant &var, const char *name, QRgb *rgba, bool *custom) const;

    QColor buttonColor(bool highlighted) const;

    // These reflect whether a color value was explicitly set on the specific
    // item that this attached style object represents.
    bool m_explicitTheme = false;
    bool m_explicitPrimary = false;
    bool m_explicitAccent = false;
    bool m_explicitForeground = false;
    bool m_explicitBackground = false;
    // These reflect whether the color value that was either inherited or
    // explicitly set is in the form that QColor expects, rather than one of
    // our pre-defined color enum values.
    bool m_customPrimary = false;
    bool m_customAccent = false;
    bool m_customForeground = false;
    bool m_customBackground = false;
    // These will be true when this item has an explicit or inherited foreground/background
    // color, or these colors were declared globally via settings (e.g. conf or env vars).
    // Some color properties of the style will return different values depending on whether
    // or not these are set.
    bool m_hasForeground = false;
    bool m_hasBackground = false;
    // The actual values for this item, whether explicit, inherited or globally set.
    Theme m_theme = Light;
    uint m_primary = 0;
    uint m_accent = 0;
    uint m_foreground = 0;
    uint m_background = 0;
    int m_elevation = 0;
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QQuickIOSStyleStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // QQUICKIOSSTYLESTYLE_P_H
