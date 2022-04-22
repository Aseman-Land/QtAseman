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

#include <QtQuickControls2/private/qquickstyleplugin_p.h>

#include "qquickiosstylestyle_p.h"
#include "qquickiosstyletheme_p.h"
#include "qquickiosstyleripple_p.h"

#include <QDir>
#include <QQmlContext>

#ifdef QT_QUICKCONTROLS2IMPL_LIB
#include <QtQuickControls2/private/qquickstyleplugin_p.h>
#include <QtQuickControls2Impl/private/qquickpaddedrectangle_p.h>
#include <QtQuickTemplates2/private/qquicktheme_p.h>
#else
#include <QtQuickControls2/private/qquickstyleselector_p.h>
#include <QtQuickControls2/private/qquickpaddedrectangle_p.h>
#endif

QT_BEGIN_NAMESPACE

class QtQuickControls2IOSStyleStylePlugin : public QQuickStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtQuickControls2IOSStyleStylePlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;

    QString name() const override;
    void initializeTheme(QQuickTheme *theme) override;
};

QtQuickControls2IOSStyleStylePlugin::QtQuickControls2IOSStyleStylePlugin(QObject *parent) : QQuickStylePlugin(parent)
{
    QQuickIOSStyleStyle::initGlobals();
}

void QtQuickControls2IOSStyleStylePlugin::registerTypes(const char *uri)
{
    qmlRegisterModule(uri, 2, QT_VERSION_MINOR); // Qt 5.12->2.12, 5.13->2.13...
    qmlRegisterUncreatableType<QQuickIOSStyleStyle>(uri, 2, 0, "IOSStyle", tr("IOSStyle is an attached property"));

    QByteArray import = QByteArray(uri) + ".impl";
    qmlRegisterModule(import, 2, QT_VERSION_MINOR); // Qt 5.12->2.12, 5.13->2.13...

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    auto resolvedUrl = [](const QString &path) -> QUrl {
        return QUrl(QStringLiteral("qrc:/qt-project.org/imports/QtQuick/Controls/IOSStyle/") + path);
    };

    auto list = QDir(QStringLiteral(":/qt-project.org/imports/QtQuick/Controls/IOSStyle/")).entryList({QStringLiteral("*.qml")});
    for (const auto &l: list)
        qmlRegisterType(resolvedUrl(l), uri, 2, 12, QString(l).remove(QStringLiteral(".qml")).toUtf8());
#endif

    qmlRegisterType<QQuickIOSStyleRipple>(import, 2, 0, "Ripple");
    qmlRegisterType(resolvedUrl(QStringLiteral("BoxShadow.qml")), import, 2, 0, "BoxShadow");
    qmlRegisterType(resolvedUrl(QStringLiteral("FastDropShadow.qml")), import, 2, 0, "FastDropShadow");
    qmlRegisterType(resolvedUrl(QStringLiteral("CheckIndicator.qml")), import, 2, 0, "CheckIndicator");
    qmlRegisterType(resolvedUrl(QStringLiteral("CursorDelegate.qml")), import, 2, 0, "CursorDelegate");
    qmlRegisterType(resolvedUrl(QStringLiteral("ElevationEffect.qml")), import, 2, 0, "ElevationEffect");
    qmlRegisterType(resolvedUrl(QStringLiteral("RadioIndicator.qml")), import, 2, 0, "RadioIndicator");
    qmlRegisterType(resolvedUrl(QStringLiteral("RectangularGlow.qml")), import, 2, 0, "RectangularGlow");
    qmlRegisterType(resolvedUrl(QStringLiteral("SliderHandle.qml")), import, 2, 0, "SliderHandle");
    qmlRegisterType(resolvedUrl(QStringLiteral("SwitchIndicator.qml")), import, 2, 0, "SwitchIndicator");
}

QString QtQuickControls2IOSStyleStylePlugin::name() const
{
    return QStringLiteral("IOSStyle");
}

void QtQuickControls2IOSStyleStylePlugin::initializeTheme(QQuickTheme *theme)
{
    QQuickIOSStyleTheme::initialize(theme);
}

QT_END_NAMESPACE

#include "qtquickcontrols2iosstylestyleplugin.moc"
