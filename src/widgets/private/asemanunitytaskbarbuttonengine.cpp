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

#include "asemanunitytaskbarbuttonengine.h"

#ifdef QT_DBUS_LIB
#include <QtDBus>
#endif
#include <QCoreApplication>

AsemanUnityTaskbarButtonEngine::AsemanUnityTaskbarButtonEngine() :
    _badge_number(0),
    _progress(0),
    _launcher("application://" + QCoreApplication::applicationName() + ".desktop")
{
}

void AsemanUnityTaskbarButtonEngine::updateBadgeNumber(int number)
{
    _badge_number = number;
    update(_launcher ,_badge_number, _progress, false);
}

void AsemanUnityTaskbarButtonEngine::updateProgress(qreal progress)
{
    _progress = progress;
    update(_launcher ,_badge_number, _progress, false);
}

void AsemanUnityTaskbarButtonEngine::updateLauncher(const QString &launcher)
{
    if(_launcher == launcher)
        return;
    if(!_launcher.isEmpty() && (_badge_number || _progress))
        update(_launcher ,0, 0, false);

    _launcher = launcher;
    update(_launcher ,_badge_number, _progress, false);
}

void AsemanUnityTaskbarButtonEngine::userAttention()
{
    update(_launcher ,_badge_number, _progress, true);
}

void AsemanUnityTaskbarButtonEngine::update(const QString &launcher, qint64 badgeNumber, qreal progress, bool userAttention)
{
#ifdef QT_DBUS_LIB
    QDBusMessage signal = QDBusMessage::createSignal(
     QStringLiteral("/"),
     QStringLiteral("com.canonical.Unity.LauncherEntry"),
     QStringLiteral("Update"));

    signal << launcher; // "application://cutegram.desktop"

    QVariantMap setProperty;
    setProperty.insert(QStringLiteral("count"), badgeNumber);
    setProperty.insert(QStringLiteral("count-visible"), badgeNumber != 0);
    setProperty.insert(QStringLiteral("progress"), progress/100);
    setProperty.insert(QStringLiteral("progress-visible"), progress != 0);
    setProperty.insert(QStringLiteral("urgent"), userAttention);

    signal << setProperty;
    QDBusConnection::sessionBus().send(signal);
#else
    Q_UNUSED(launcher)
    Q_UNUSED(badgeNumber)
    Q_UNUSED(progress)
#endif
}
