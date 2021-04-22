#include "asemankeyhandler.h"

#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QPointer>

class AsemanKeyHandler::Private
{
public:
    QPointer<QObject> window;
    qint32 key;
    qint32 scanCode;
    qint32 modifiers;
};

AsemanKeyHandler::AsemanKeyHandler(QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->key = 0;
    p->scanCode = 0;
    p->modifiers = static_cast<qint32>(Qt::NoModifier);
}

void AsemanKeyHandler::setWindow(QObject *window)
{
    if(p->window == window)
        return;

    if(p->window)
        p->window->removeEventFilter(this);
    p->window = window;
    if(p->window)
        p->window->installEventFilter(this);

    Q_EMIT windowChanged();
}

QObject *AsemanKeyHandler::window() const
{
    return p->window;
}

qint32 AsemanKeyHandler::key() const
{
    return p->key;
}

void AsemanKeyHandler::setKey(qint32 key)
{
    if(p->key == key)
        return;

    p->key = key;
    Q_EMIT keyChanged();
}

qint32 AsemanKeyHandler::modifiers() const
{
    return p->modifiers;
}

qint32 AsemanKeyHandler::scanCode() const
{
    return p->scanCode;
}

void AsemanKeyHandler::setScanCode(qint32 scanCode)
{
    if(p->scanCode == scanCode)
        return;

    p->scanCode = scanCode;
    Q_EMIT scanCodeChanged();
}

void AsemanKeyHandler::setModifiers(qint32 modifiers)
{
    if(p->modifiers == modifiers)
        return;

    p->modifiers = modifiers;
    Q_EMIT modifiersChanged();
}

bool AsemanKeyHandler::eventFilter(QObject *watched, QEvent *ev)
{
    if(watched != p->window)
        return QObject::eventFilter(watched, ev);

    switch(static_cast<int>(ev->type()))
    {
    case QEvent::ActivationChange:
    {
        setModifiers(0);
        setKey(0);
        setScanCode(0);
    }
        break;

    case QEvent::KeyPress:
    {
        QKeyEvent *e = static_cast<QKeyEvent*>(ev);
        if(e->isAutoRepeat())
            return QObject::eventFilter(watched, ev);

        qint32 key = e->key();
        quint32 scanCode = e->nativeScanCode();
        switch (key) {
        case Qt::Key_Shift:
        case Qt::Key_Control:
        case Qt::Key_Meta:
            key = 0;
            scanCode = 0;
            break;
        }

        setKey(key);
        setScanCode(static_cast<qint32>(scanCode));
        setModifiers(static_cast<int>(e->modifiers()));
        Q_EMIT pressed(static_cast<int>(e->modifiers()), key, static_cast<qint32>(scanCode));
    }
        break;

    case QEvent::KeyRelease: {
        QKeyEvent *e = static_cast<QKeyEvent*>(ev);
        if(e->isAutoRepeat())
            return QObject::eventFilter(watched, ev);

        qint32 key = e->key();
        quint32 scanCode = e->nativeScanCode();
        switch (key) {
        case Qt::Key_Shift:
        case Qt::Key_Control:
        case Qt::Key_Meta:
            key = 0;
            scanCode = 0;
            break;
        }
        if(key == p->key) {
            setKey(0);
            setScanCode(0);
        }

        setModifiers(static_cast<int>(e->modifiers()));
        Q_EMIT released(static_cast<int>(e->modifiers()), key, static_cast<qint32>(scanCode));
    }
        break;
    }

    return QObject::eventFilter(watched, ev);
}

AsemanKeyHandler::~AsemanKeyHandler()
{
    delete p;
}
