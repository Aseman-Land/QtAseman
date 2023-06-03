#ifndef MACMANAGER_H
#define MACMANAGER_H

#include <QGuiApplication>
#include <QWindow>

class AsemanMacManager: public QObject
{
    Q_OBJECT
public:
    class Private;

    AsemanMacManager(QObject *parent = nullptr);
    virtual ~AsemanMacManager();

    static void removeTitlebarFromWindow(double r, double g, double b);

    static bool hasBiometric();
    static bool biometricCheck();

Q_SIGNALS:
    void deepLinkReceived(const QString &link);

private:
    Private *p;
};
#endif // MACMANAGER_H
