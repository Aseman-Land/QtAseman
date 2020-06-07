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

#include "asemansystemtray.h"

#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QGuiApplication>
#include <QPainterPath>

class AsemanSystemTrayPrivate
{
public:
    QSystemTrayIcon *sysTray;
    QUrl icon;
    int badgeCount;
    QColor badgeStrokeColor;
    QColor badgeFillColor;
    QColor badgeTextColor;
    QStringList menu;
    bool visible;

    QMenu *menuItem;
};

AsemanSystemTray::AsemanSystemTray(QObject *parent) :
    QObject(parent)
{
    p = new AsemanSystemTrayPrivate;
    p->visible = false;
    p->menuItem = 0;
    p->badgeFillColor = QColor("#ff0000");
    p->badgeStrokeColor = QColor("#333333");
    p->badgeTextColor = QColor("#ffffff");
    p->badgeCount = 0;

    p->sysTray = new QSystemTrayIcon(this);

    connect(p->sysTray, &QSystemTrayIcon::activated, this, &AsemanSystemTray::activated_slt);
}

void AsemanSystemTray::setVisible(bool visible)
{
    if(p->visible == visible)
        return;

    p->visible = visible;
    QGuiApplication::setQuitOnLastWindowClosed(!p->visible);
    refreshVisible();
    Q_EMIT visibleChanged();
}

bool AsemanSystemTray::visible() const
{
    return p->sysTray->isVisible();
}

void AsemanSystemTray::setIcon(const QUrl &icon)
{
    if(p->icon == icon)
        return;

    p->icon = icon;
    refreshIcon();
    refreshVisible();
    Q_EMIT iconChanged();
}

QUrl AsemanSystemTray::icon() const
{
    return p->icon;
}

void AsemanSystemTray::setBadgeCount(int badgeCount)
{
    if(p->badgeCount == badgeCount)
        return;

    p->badgeCount = badgeCount;
    refreshIcon();
    Q_EMIT badgeCountChanged();
}

int AsemanSystemTray::badgeCount() const
{
    return p->badgeCount;
}

void AsemanSystemTray::setBadgeFillColor(const QColor &badgeFillColor)
{
    if(p->badgeFillColor == badgeFillColor)
        return;

    p->badgeFillColor = badgeFillColor;
    refreshIcon();
    Q_EMIT badgeFillColorChanged();
}

QColor AsemanSystemTray::badgeFillColor() const
{
    return p->badgeTextColor;
}

void AsemanSystemTray::setBadgeStrokeColor(const QColor &badgeStrokeColor)
{
    if(p->badgeStrokeColor == badgeStrokeColor)
        return;

    p->badgeStrokeColor = badgeStrokeColor;
    refreshIcon();
    Q_EMIT badgeStrokeColorChanged();
}

QColor AsemanSystemTray::badgeStrokeColor() const
{
    return p->badgeStrokeColor;
}

void AsemanSystemTray::setBadgeTextColor(const QColor &badgeTextColor)
{
    if(p->badgeTextColor == badgeTextColor)
        return;

    p->badgeTextColor = badgeTextColor;
    refreshIcon();
    Q_EMIT badgeTextColorChanged();
}

QColor AsemanSystemTray::badgeTextColor() const
{
    return p->badgeTextColor;
}

void AsemanSystemTray::setMenu(const QStringList &menu)
{
    if(p->menu == menu)
        return;

    p->menu = menu;

    if(p->menuItem)
        delete p->menuItem;

    p->menuItem = new QMenu();
    if(p->menu.isEmpty()) {
        p->menuItem = 0;
    } else {
        for(int i=0; i<menu.count(); i++)
        {
            const QString &m = menu.at(i);
            if(m.isEmpty())
            {
                p->menuItem->addSeparator();
                continue;
            }

            QAction *act = p->menuItem->addAction(m);
            connect(act, &QAction::triggered, this, [this, i](){
                Q_EMIT menuTriggered(i);
            });
        }
    }

    p->sysTray->setContextMenu(p->menuItem);
    Q_EMIT menuChanged();
}

QStringList AsemanSystemTray::menu() const
{
    return p->menu;
}

void AsemanSystemTray::activated_slt(QSystemTrayIcon::ActivationReason reason)
{
    switch(static_cast<int>(reason))
    {
    case QSystemTrayIcon::Unknown:
        Q_EMIT activated(ActivateUnknown);
        break;
    case QSystemTrayIcon::Context:
        Q_EMIT activated(ActivateContext);
        break;
    case QSystemTrayIcon::DoubleClick:
        Q_EMIT activated(ActivateDoubleClick);
        break;
    case QSystemTrayIcon::Trigger:
        Q_EMIT activated(ActivateTrigger);
        break;
    case QSystemTrayIcon::MiddleClick:
        Q_EMIT activated(ActivateMiddleClick);
        break;
    }
}

void AsemanSystemTray::refreshIcon()
{
    QString iconPath = p->icon.toLocalFile();
    if(iconPath.isEmpty())
        iconPath = p->icon.toString();
    if(iconPath.left(4) == QStringLiteral("qrc:"))
        iconPath = iconPath.mid(3);

    const QImage & img = generateIcon( iconPath, p->badgeCount );
    p->sysTray->setIcon( QPixmap::fromImage(img) );
}

QImage AsemanSystemTray::generateIcon(const QString &filePath, int count)
{
    if(filePath.isEmpty())
        return QImage();

    QImage img(filePath);
    if( count == 0 || filePath.isEmpty() )
        return img;

    QImage res = img;

    QRect rct;
    rct.setX( img.width()/5 );
    rct.setWidth( 4*img.width()/5 );
    rct.setY( img.height()-rct.width() );
    rct.setHeight( rct.width() );

    QPainterPath path;
    path.addEllipse(rct);

    QPainter painter(&res);
    painter.setRenderHint( QPainter::Antialiasing , true );
    painter.fillPath( path, p->badgeFillColor );
    painter.setPen(p->badgeStrokeColor);
    painter.drawPath( path );
    painter.setPen(p->badgeTextColor);
    painter.drawText( rct, Qt::AlignCenter | Qt::AlignHCenter, QString::number(count) );

    return res;
}

void AsemanSystemTray::refreshVisible()
{
    if(p->visible && p->icon.isValid())
        p->sysTray->setVisible(true);
    else
        p->sysTray->setVisible(false);
}

AsemanSystemTray::~AsemanSystemTray()
{
    if(p->menuItem)
        delete p->menuItem;
    delete p;
}
