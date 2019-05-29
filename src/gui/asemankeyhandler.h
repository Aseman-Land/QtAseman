#ifndef ASEMANKEYHANDLER_H
#define ASEMANKEYHANDLER_H

#include <QObject>
#include <QWindow>

#include "asemangui_global.h"

class LIBQTASEMAN_GUI_EXPORT AsemanKeyHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ window WRITE setWindow NOTIFY windowChanged)
    Q_PROPERTY(qint32 modifiers READ modifiers NOTIFY modifiersChanged)
    Q_PROPERTY(qint32 scanCode READ scanCode WRITE setScanCode NOTIFY scanCodeChanged)
    Q_PROPERTY(qint32 key READ key WRITE setKey NOTIFY keyChanged)

    class Private;

public:
    AsemanKeyHandler(QObject *parent = Q_NULLPTR);
    virtual ~AsemanKeyHandler();

    void setWindow(QWindow *window);
    QWindow *window() const;

    qint32 key() const;
    qint32 modifiers() const;

    qint32 scanCode() const;
    void setScanCode(qint32 scanCode);

Q_SIGNALS:
    void windowChanged();
    void keyChanged();
    void modifiersChanged();
    void scanCodeChanged();

    void pressed(qint32 modifiers, qint32 key, qint32 scanCode);
    void released(qint32 modifiers, qint32 key, qint32 scanCode);

public Q_SLOTS:

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void setKey(qint32 key);
    void setModifiers(qint32 modifiers);

private:
    Private *p;
};

#endif // ASEMANKEYHANDLER_H
