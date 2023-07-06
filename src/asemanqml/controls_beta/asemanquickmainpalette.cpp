#include "asemanquickmainpalette.h"

#include <QPalette>
#include <QGuiApplication>

AsemanQuickMainPalette::AsemanQuickMainPalette(QObject *parent)
    : QObject(parent)
{
    auto palette = qApp->palette();
    mBackground = palette.window().color();
    mForeground = palette.windowText().color();
    mHighlight = palette.highlight().color();
    mHighlightText = palette.highlightedText().color();
    mBase = palette.base().color();
    mBaseText = palette.text().color();
}

AsemanQuickMainPalette::~AsemanQuickMainPalette()
{
}

int AsemanQuickMainPalette::theme() const
{
    return mTheme;
}

void AsemanQuickMainPalette::setTheme(int newTheme)
{
    if (mTheme == newTheme)
        return;
    mTheme = newTheme;
    Q_EMIT themeChanged();
}
