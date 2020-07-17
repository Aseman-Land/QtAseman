#ifndef QUICKIOS_H
#define QUICKIOS_H

#include <QtPlugin>
#include <QQuickWindow>
#include <QObject>

class QuickIOS: public QObject
{
    Q_OBJECT
    Q_ENUMS(StatusBarStyle)
public:
    QuickIOS(QObject *parent = Q_NULLPTR) : QObject(parent) {}
    virtual ~QuickIOS() {}

    enum StatusBarStyle {
        StatusBarStyleDefault,
        StatusBarStyleLightContent,
        StatusBarStyleBlackTranslucent,
        StatusBarStyleBlackOpaque
    };

    static void registerTypes();

public Q_SLOTS:
    static void setStatusBarStyle(StatusBarStyle style);
    static void setStatusBarHidden(bool hidden, int animation);
};

#endif // QUICKIOS_H
