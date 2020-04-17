/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemanquickview.h"
#include "asemandevicesitem.h"
#include "asemanqttools.h"
#include "asemantoolsitem.h"
#include "aseman_macros.h"
#ifdef Q_OS_ANDROID
#include "asemanjavalayer.h"
#endif

#include <QPointer>
#include <QSharedPointer>
#include <QtQml>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QScreen>
#include <QSet>
#include <QDebug>

class AsemanQuickViewPrivate
{
public:
    QPointer<QObject> root;
    QPointer<QQuickItem> focused_text;

    bool reverseScroll;

    QQmlEngine *engine;
};

AsemanQuickView::AsemanQuickView(QQmlEngine *engine, QObject *parent ) :
    QObject(parent)
{
    p = new AsemanQuickViewPrivate;
    p->engine = engine;
    p->reverseScroll = false;

    connect(devices(), &AsemanDevices::statusBarHeightChanged, this, &AsemanQuickView::statusBarHeightChanged);
    connect(devices(), &AsemanDevices::navigationBarHeightChanged, this, &AsemanQuickView::navigationBarHeightChanged);
}

AsemanDesktopTools *AsemanQuickView::desktopTools() const
{
    return AsemanQtTools::desktopTools();
}

AsemanDevicesItem *AsemanQuickView::devices() const
{
    return AsemanQtTools::devices();
}

AsemanQtLogger *AsemanQuickView::qtLogger() const
{
    return AsemanQtTools::qtLogger();
}

AsemanToolsItem *AsemanQuickView::tools() const
{
    return AsemanQtTools::tools();
}

#ifdef Q_OS_ANDROID
AsemanJavaLayer *AsemanQuickView::javaLayer() const
{
    return AsemanJavaLayer::instance();
}
#endif

AsemanCalendarConverter *AsemanQuickView::calendar() const
{
    return AsemanQtTools::calendar(p->engine);
}

AsemanBackHandler *AsemanQuickView::backHandler() const
{
    return AsemanQtTools::backHandler(p->engine);
}

void AsemanQuickView::setReverseScroll(bool stt)
{
    if(p->reverseScroll == stt)
        return;

    p->reverseScroll = stt;
    Q_EMIT reverseScrollChanged();
}

bool AsemanQuickView::reverseScroll() const
{
    return p->reverseScroll;
}

qreal AsemanQuickView::statusBarHeight() const
{
    return devices()->statusBarHeight();
}

qreal AsemanQuickView::navigationBarHeight() const
{
    return devices()->navigationBarHeight();
}

void AsemanQuickView::setRoot(QObject *root)
{
    if( p->root == root )
        return;

    p->root = root;
    Q_EMIT rootChanged();
}

QObject *AsemanQuickView::root() const
{
    if( p->root )
        return p->root;

    return p->root;
}

void AsemanQuickView::setFocusedText(QQuickItem *item)
{
    if( p->focused_text == item )
        return;
    if( p->focused_text )
        disconnect(p->focused_text, &QQuickItem::destroyed, this, &AsemanQuickView::focusedTextChanged);

    p->focused_text = item;
    if( item )
    {
        connect(p->focused_text, &QQuickItem::destroyed, this, &AsemanQuickView::focusedTextChanged);
        devices()->showKeyboard();
    }
    else
    {
        devices()->hideKeyboard();
    }

    Q_EMIT focusedTextChanged();
}

QQuickItem *AsemanQuickView::focusedText() const
{
    return p->focused_text;
}

qreal AsemanQuickView::flickVelocity() const
{
#ifdef DESKTOP_DEVICE
    return 2500;
#else
    return 25000;
#endif
}

void AsemanQuickView::setOfflineStoragePath(const QString &path)
{
    if(path == offlineStoragePath())
        return;

    p->engine->setOfflineStoragePath(path);
    Q_EMIT offlineStoragePathChanged();
}

QString AsemanQuickView::offlineStoragePath() const
{
    return p->engine->offlineStoragePath();
}

void AsemanQuickView::registerWindow(QQuickWindow *window)
{
#ifdef Q_OS_IOS
    window->setFlag(Qt::MaximizeUsingFullscreenGeometryHint, true);
#endif
    window->installEventFilter(this);
}

void AsemanQuickView::discardFocusedText()
{
    setFocusedText(0);
}

bool AsemanQuickView::eventFilter(QObject *o, QEvent *e)
{
    QQuickWindow *win = qobject_cast<QQuickWindow*>(o);
    if(win)
    {
        switch( static_cast<int>(e->type()) )
        {
        case QEvent::Close:
            if(o->property("backController").toBool())
            {
                QCloseEvent *ce = static_cast<QCloseEvent*>(e);
                if( o->property("try_close").toBool() || AsemanDevices::isDesktop() )
                    ce->accept();
                else
                {
                    ce->ignore();
                    QMetaObject::invokeMethod(o, "closeRequest");
                }
            }
            break;
        case QEvent::KeyPress:
        {
            QKeyEvent *ke = static_cast<QKeyEvent*>(e);
            switch(ke->key())
            {
            case Qt::Key_Escape:
            case Qt::Key_Back:
                QMetaObject::invokeMethod(o, "closeRequest");
                break;
            }
        }
            break;
        }
    }

    return QObject::eventFilter(o,e);
}

AsemanQuickView::~AsemanQuickView()
{
    delete p;
}
