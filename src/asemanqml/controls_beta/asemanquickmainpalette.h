#ifndef ASEMANQUICKMAINPALETTE_H
#define ASEMANQUICKMAINPALETTE_H

#include <QObject>
#include <QColor>

class AsemanQuickMainPalette : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QColor highlight MEMBER mHighlight NOTIFY themeChanged)
    Q_PROPERTY(QColor highlightText MEMBER mHighlightText NOTIFY themeChanged)
    Q_PROPERTY(QColor foreground MEMBER mForeground NOTIFY themeChanged)
    Q_PROPERTY(QColor background MEMBER mBackground NOTIFY themeChanged)
    Q_PROPERTY(QColor base MEMBER mBase NOTIFY themeChanged)
    Q_PROPERTY(QColor baseText MEMBER mBaseText NOTIFY themeChanged)

public:
    enum Theme {
        Auto,
        Light,
        Dark,
    };
    Q_ENUM(Theme)

    AsemanQuickMainPalette(QObject *parent = nullptr);
    virtual ~AsemanQuickMainPalette();

    int theme() const;
    void setTheme(int newTheme);

Q_SIGNALS:
    void themeChanged();

private:
    int mTheme = Auto;

    QColor mForeground;
    QColor mBackground;
    QColor mHighlight;
    QColor mHighlightText;
    QColor mBase;
    QColor mBaseText;
};

#endif // ASEMANQUICKMAINPALETTE_H
