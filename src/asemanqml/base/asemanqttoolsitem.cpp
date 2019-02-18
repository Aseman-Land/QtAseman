/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtToolsItem is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtToolsItem is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemanqttoolsitem.h"

#include "asemanquickview.h"
#include "asemanqtlogger.h"
#include "asemandevicesitem.h"
#include "asemantoolsitem.h"
#include "asemanapplicationitem.h"
#include "asemanhashobject.h"
#include "asemandownloader.h"
#include "asemanlistobject.h"
#include "asemancalendarconverter.h"
#include "asemanimagecoloranalizor.h"
#include "asemandesktoptools.h"
#include "asemansettings.h"
#include "asemanmimedata.h"
#include "asemannetworkrequest.h"
#include "asemanfileresourcemanager.h"
#include "asemanmapobject.h"
#include "asemandragobject.h"
#include "asemanbackhandler.h"
#include "aseman_macros.h"
#include "asemancountriesmodel.h"
#include "asemanwindowdetails.h"
#include "asemanautostartmanager.h"
#include "asemanfilesystemmodel.h"
#include "asemanhostchecker.h"
#include "asemannetworkmanager.h"
#include "asemannetworkmanageritem.h"
#include "asemannetworksleepmanager.h"
#include "asemannetworkproxy.h"
#include "asemanquickobject.h"
#include "asemankeyhandler.h"
#include "asemantexttools.h"
#include "asemanlistmodel.h"
#include "asemanfiledownloaderqueueitem.h"
#include "asemanquickitemimagegrabber.h"
#include "asemantitlebarcolorgrabber.h"
#include "asemanproxycomponent.h"
#include "asemanfiledownloaderqueue.h"
#include "asemandragarea.h"
#include "asemanapplicationitem.h"
#include "asemancalendarmodel.h"
#include "asemanmixedlistmodel.h"
#include "asemanencrypter.h"
#include "asemanquickviewwrapper.h"
#include "asemanqmlsmartcomponent.h"
#include "asemanmouseeventlistener.h"
#include "asemanqmlimage.h"
#include "asemantranslationmanager.h"
#include "asemansysteminfo.h"
#include "asemanitemgrabber.h"
#ifndef Q_OS_IOS
#include "asemanprocess.h"
#endif
#ifdef QT_WIDGETS_LIB
#include "asemansystemtray.h"
#endif
#ifdef Q_OS_ANDROID
#include "asemanjavalayer.h"
#endif
#ifdef DESKTOP_LINUX
#include "asemanmimeapps.h"
#endif
#ifdef ASEMAN_SENSORS
#include "asemansensors.h"
#endif
#ifdef QZXING_SUPPORTED
#include "QZXing.h"
#ifdef QZXING_MULTIMEDIA
#include "QZXingFilter.h"
#endif
#endif
#ifdef ASEMAN_NOTIFICATION
#include "asemannotification.h"
#endif
#if defined(Q_OS_LINUX) && defined(QT_DBUS_LIB)
#include "asemankdewallet.h"
#endif

#include <qqml.h>
#include <QHash>
#include <QPointer>

#define SINGLETON_PROVIDER(TYPE, FNC_NAME, NEW_CREATOR) \
    static QObject *FNC_NAME(QQmlEngine *engine, QJSEngine *scriptEngine) { \
        Q_UNUSED(engine) \
        Q_UNUSED(scriptEngine) \
        static TYPE *singleton = NEW_CREATOR; \
        return singleton; \
    }

SINGLETON_PROVIDER(AsemanDevicesItem        , aseman_devices_singleton         , AsemanQtToolsItem::devices())
SINGLETON_PROVIDER(AsemanToolsItem          , aseman_tools_singleton           , AsemanQtToolsItem::tools())
SINGLETON_PROVIDER(AsemanTextTools          , aseman_text_tools_singleton      , AsemanQtToolsItem::textTools())
SINGLETON_PROVIDER(AsemanDesktopTools       , aseman_desktoptools_singleton    , AsemanQtToolsItem::desktopTools())
SINGLETON_PROVIDER(AsemanCalendarConverter  , aseman_calendarconv_singleton    , AsemanQtToolsItem::calendar(engine))
SINGLETON_PROVIDER(AsemanBackHandler        , aseman_backhandler_singleton     , AsemanQtToolsItem::backHandler(engine))
SINGLETON_PROVIDER(AsemanApplicationItem    , aseman_app_singleton             , AsemanQtToolsItem::application(engine))
SINGLETON_PROVIDER(AsemanQuickViewWrapper   , aseman_qview_singleton           , AsemanQtToolsItem::quickView(engine))
SINGLETON_PROVIDER(AsemanQtLogger           , aseman_logger_singleton          , AsemanQtToolsItem::qtLogger())
SINGLETON_PROVIDER(AsemanSystemInfo         , aseman_sysinfo_singleton         , AsemanQtToolsItem::systemInfo())
SINGLETON_PROVIDER(AsemanFileDownloaderQueue, aseman_downloader_queue_singleton, AsemanQtToolsItem::getDownloaderQueue(engine))
#ifdef Q_OS_ANDROID
SINGLETON_PROVIDER(AsemanJavaLayer          , aseman_javalayer_singleton       , AsemanQtToolsItem::javaLayer())
#endif

QStringList aseman_qt_tools_indexCache;
QString aseman_qt_tools_destination;

void AsemanQtToolsItem::registerTypes(const char *uri, bool exportMode)
{
    static QSet<QByteArray> register_list;
    if(register_list.contains(uri) && !exportMode)
        return;
    qRegisterMetaType<AsemanMimeData*>("AsemanMimeData*");

    registerType<AsemanMimeData>(uri, 2, 0, "MimeData", exportMode);
    registerType<AsemanDragObject>(uri, 2, 0, "DragObject", exportMode);
    registerType<AsemanHashObject>(uri, 2, 0, "HashObject", exportMode);
    registerType<AsemanMapObject>(uri, 2, 0, "MapObject", exportMode);
    registerType<AsemanListObject>(uri, 2, 0, "ListObject", exportMode);
    registerType<AsemanDownloader>(uri, 2, 0, "Downloader", exportMode);
    registerType<AsemanEncrypter>(uri, 2, 0, "Encrypter", exportMode);
#ifdef QT_WIDGETS_LIB
    registerType<AsemanSystemTray>(uri, 2, 0, "SystemTray", exportMode);
#endif
    registerType<AsemanWindowDetails>(uri, 2, 0, "WindowDetails", exportMode);
    registerType<AsemanQuickObject>(uri, 2, 0, "AsemanObject", exportMode);
    registerType<AsemanImageColorAnalizor>(uri, 2, 0, "ImageColorAnalizor", exportMode);
    registerType<AsemanAutoStartManager>(uri, 2, 0, "AutoStartManager", exportMode);
    registerType<AsemanSettings>(uri, 2, 0, "Settings", exportMode);
    registerType<AsemanQuickItemImageGrabber>(uri, 2, 0, "ItemImageGrabber", exportMode);
    registerType<AsemanFileDownloaderQueueItem>(uri, 2, 0, "FileDownloaderQueueItem", exportMode);
    registerType<AsemanFileDownloaderQueue>(uri, 2, 0, "FileDownloaderQueue", exportMode);
    registerType<AsemanMouseEventListener>(uri, 2, 0, "MouseEventListener", exportMode);
    registerType<AsemanNetworkRequest>(uri, 2, 0, "NetworkRequest", exportMode);
    registerType<AsemanItemGrabber>(uri, 2, 0, "ItemGrabber", exportMode);
    registerType<AsemanApplicationItem>(uri, 2,0, "AsemanApplicationBase", exportMode);
    registerType<AsemanKeyHandler>(uri, 2, 0, "KeyHandler", exportMode);
    registerType<AsemanQmlImage>(uri, 2, 0, "AsemanImage", exportMode);
#ifndef Q_OS_IOS
    registerType<AsemanProcess>(uri, 2, 0, "Process", exportMode);
#endif
    registerType<AsemanTranslationManager>(uri, 2, 0, "TranslationManager", exportMode);
    registerType<AsemanQmlSmartComponent>(uri, 2, 0, "SmartComponentCore", exportMode);
#ifdef DESKTOP_LINUX
    registerType<AsemanMimeApps>(uri, 2, 0, "MimeApps", exportMode);
#endif
    registerType<AsemanHostChecker>(uri, 2, 0, "HostChecker", exportMode);
    registerType<AsemanNetworkManager>(uri, 2, 0, "NetworkManager", exportMode);
    registerType<AsemanNetworkSleepManager>(uri, 2, 0, "NetworkSleepManager", exportMode);
    registerType<AsemanNetworkProxy>(uri, 2, 0, "NetworkProxy", exportMode);
    registerType<AsemanTitleBarColorGrabber>(uri, 2, 0, "TitleBarColorGrabber", exportMode);
    registerType<AsemanDragArea>(uri, 2, 0, "MouseDragArea", exportMode);
    registerType<AsemanCalendarModel>(uri, 2, 0, "CalendarModel", exportMode);
    registerType<AsemanListModel>(uri, 2, 0, "AsemanListModel", exportMode);
    registerType<AsemanFileResourceManager>(uri, 2, 0, "FileResourceManager", exportMode);
    registerType<AsemanProxyComponent>(uri, 2, 0, "ProxyComponent", exportMode);

    registerModel<AsemanMixedListModel>(uri, 2, 0, "MixedListModel", exportMode);
    registerModel<AsemanCountriesModel>(uri, 2, 0, "CountriesModel", exportMode);
    registerModel<AsemanFileSystemModel>(uri, 2, 0, "FileSystemModel", exportMode);

    registerSingletonType<AsemanDevicesItem>(uri, 2, 0, "Devices", aseman_devices_singleton, exportMode);
    registerSingletonType<AsemanTextTools>(uri, 2, 0, "TextTools", aseman_text_tools_singleton, exportMode);
    registerSingletonType<AsemanToolsItem>(uri, 2, 0, "Tools", aseman_tools_singleton, exportMode);
    registerSingletonType<AsemanDesktopTools>(uri, 2, 0, "Desktop", aseman_desktoptools_singleton, exportMode);
    registerSingletonType<AsemanCalendarConverter>(uri, 2, 0, "CalendarConv", aseman_calendarconv_singleton, exportMode);
    registerSingletonType<AsemanBackHandler>(uri, 2, 0, "BackHandler", aseman_backhandler_singleton, exportMode);
    registerSingletonType<AsemanApplicationItem>(uri, 2, 0, "AsemanApp", aseman_app_singleton, exportMode);
    registerSingletonType<AsemanQtLogger>(uri, 2, 0, "Logger", aseman_logger_singleton, exportMode);
    registerSingletonType<AsemanQuickViewWrapper>(uri, 2, 0, "View", aseman_qview_singleton, exportMode);
    registerSingletonType<AsemanSystemInfo>(uri, 2, 0, "SystemInfo", aseman_sysinfo_singleton, exportMode);
    registerSingletonType<AsemanFileDownloaderQueue>(uri, 2, 0, "DownloaderQueue", aseman_downloader_queue_singleton, exportMode);
#ifdef Q_OS_ANDROID
    registerSingletonType<AsemanJavaLayer>(uri, 2, 0, "JavaLayer", aseman_javalayer_singleton, exportMode);
#endif

    registerUncreatableType<QScreen>(uri, 2, 0, "Screen", QStringLiteral(""), exportMode);
    registerUncreatableType<AsemanDesktopTools>(uri, 2, 0, "AsemanDesktopTools", QStringLiteral("It's a singleton class"), exportMode);
    registerUncreatableType<AsemanNetworkManagerItem>(uri, 2, 0, "NetworkManagerItem", QStringLiteral("It must create using NetworkManager component."), exportMode);

#ifdef QZXING_SUPPORTED
    registerType<QZXing>(uri, 2, 0, "QZXing", exportMode);
#ifdef QZXING_MULTIMEDIA
    registerType<QZXingFilter>(uri, 2, 0, "QZXingFilter", exportMode);
#endif //QZXING_MULTIMEDIA
#endif

    register_list.insert(uri);
}

void AsemanQtToolsItem::registerFiles(const QString &filesLocation, const char *uri)
{
    QFile file(filesLocation + QStringLiteral("/qmldir"));
    if(file.open(QFile::ReadOnly))
    {
        QStringList lines = QString::fromUtf8(file.readAll()).split(QStringLiteral("\n"), QString::SkipEmptyParts);
        file.close();

        for(const QString &l: lines)
        {
            QStringList parts = l.trimmed().split(QStringLiteral(" "), QString::SkipEmptyParts);
            bool singleton = false;
            if(parts.count() && parts.first() == "singleton")
                singleton = parts.takeFirst().count();
            if(parts.length() != 3)
                continue;

            QStringList version = parts.at(1).split(QStringLiteral("."), QString::SkipEmptyParts);
            if(version.count() != 2)
                continue;

            if(singleton)
                qmlRegisterSingletonType(QUrl(QStringLiteral("qrc") + filesLocation + QStringLiteral("/") + parts.at(2)),
                                         uri, version.at(0).toInt(), version.at(1).toInt(), parts.at(0).toUtf8());
            else
                qmlRegisterType(QUrl(QStringLiteral("qrc") + filesLocation + QStringLiteral("/") + parts.at(2)),
                                uri, version.at(0).toInt(), version.at(1).toInt(), parts.at(0).toUtf8());
        }
    }
}

template<typename T>
int AsemanQtToolsItem::registerType(const char *uri, int versionMajor, int versionMinor, const char *typeName, bool exportMode)
{
    if(exportMode)
        exportItem<T>(QString::fromUtf8(uri), versionMajor, versionMinor, QString::fromUtf8(typeName));
    else
        return qmlRegisterType<T>(uri, versionMajor, versionMinor, typeName);
    return 0;
}

template<typename T>
int AsemanQtToolsItem::registerModel(const char *uri, int versionMajor, int versionMinor, const char *typeName, bool exportMode)
{
    if(exportMode)
        exportModel<T>(QString::fromUtf8(uri), versionMajor, versionMinor, QString::fromUtf8(typeName));
    else
        return qmlRegisterType<T>(uri, versionMajor, versionMinor, typeName);
    return 0;
}

template<typename T>
int AsemanQtToolsItem::registerSingletonType(const char *uri, int versionMajor, int versionMinor, const char *typeName, QObject *(*callback)(QQmlEngine *, QJSEngine *), bool exportMode)
{
    if(exportMode)
        exportItem<T>(QString::fromUtf8(uri), versionMajor, versionMinor, QString::fromUtf8(typeName));
    else
        return qmlRegisterSingletonType<T>(uri, versionMajor, versionMinor, typeName, callback);
    return 0;
}

template<typename T>
int AsemanQtToolsItem::registerUncreatableType(const char *uri, int versionMajor, int versionMinor, const char *qmlName, const QString &reason, bool exportMode)
{
    if(exportMode)
        exportItem<T>(QString::fromUtf8(uri), versionMajor, versionMinor, QString::fromUtf8(qmlName));
    else
        return qmlRegisterUncreatableType<T>(uri, versionMajor, versionMinor, qmlName, reason);
    return 0;
}


void AsemanQtToolsItem::exportDocuments(const QString &destination)
{
    aseman_qt_tools_destination = destination;

    QDir().mkpath(aseman_qt_tools_destination);
    aseman_qt_tools_indexCache.clear();

    AsemanQtToolsItem::registerTypes("AsemanToolsItem", true);

    QString index = QStringLiteral("# AsemanToolsItem Documents\n\n");
    index += QStringLiteral("### [Getting Started](gettingstarted.md)\n\n");
    index += QStringLiteral("### How to import:\n\n");
    index += QStringLiteral("```c++\nimport AsemanQml.Base 2.0\n```\n\nor\n\n"
             "```c++\nimport AsemanQml.Base 2.0 as Aseman\n```\n\n");
    index += QStringLiteral("### Types\n\nHere are all components of the AsemanToolsItem:\n\n");
    for(const QString cmpnt: aseman_qt_tools_indexCache)
    {
        if(cmpnt == QStringLiteral("MimeData"))
            index += QStringLiteral("\n##### Normal types\n\n");
        if(cmpnt == QStringLiteral("MixedListModel"))
            index += QStringLiteral("\n##### Models\n\n");
        if(cmpnt == QStringLiteral("Devices"))
            index += QStringLiteral("\n##### Singletons\n\n");
        if(cmpnt == QStringLiteral("Screen"))
            index += QStringLiteral("\n##### Uncreatable types\n\n");
        index += QStringLiteral(" * [%1](%2.md)\n").arg(cmpnt).arg(cmpnt.toLower());
    }

    QString path = aseman_qt_tools_destination + "/start.md";
    aseman_qt_tools_destination.clear();
    QFile file(path);
    if(!file.open(QFile::WriteOnly))
        return;

    file.write(index.toUtf8());
    file.close();
}

QString AsemanQtToolsItem::fixType(const QString &type)
{
    if(type == QStringLiteral("QSizeF") || type == QStringLiteral("QSize"))
        return QStringLiteral("size");
    if(type == QStringLiteral("QPoint") || type == QStringLiteral("QPointF"))
        return QStringLiteral("point");
    if(type == QStringLiteral("QUrl"))
        return QStringLiteral("url");
    if(type == QStringLiteral("QString"))
        return QStringLiteral("string");
    if(type == QStringLiteral("QByteArray"))
        return QStringLiteral("byte");
    if(type == QStringLiteral("bool"))
        return QStringLiteral("boolean");
    if(type == QStringLiteral("double") || type == QStringLiteral("qreal"))
        return QStringLiteral("real");
    if(type == QStringLiteral("QVariant"))
        return QStringLiteral("variant");
    if(type == QStringLiteral("QJSValue"))
        return QStringLiteral("function(){[code]}");
    if(type == QStringLiteral("QVariantMap"))
        return QStringLiteral("map");
    if(type == QStringLiteral("QVariantList"))
        return QStringLiteral("list&lt;variant&gt;");
    if(type == QStringLiteral("QStringList"))
        return QStringLiteral("list&lt;string&gt;");
    if(type == QStringLiteral("QList<qint32>"))
        return QStringLiteral("list&lt;int&gt;");
    if(type.contains(QStringLiteral("*")))
    {
        if(type == QStringLiteral("QObject*"))
            return QStringLiteral("object");
        if(type.contains(QStringLiteral("Telegram")))
        {
            QString name = QString(type).remove(QStringLiteral("*")).remove(QStringLiteral("Telegram"));
            return QStringLiteral("[%1](%2.md)").arg(name).arg(name.toLower());
        }
        if(type.contains(QStringLiteral("Object")))
        {
            QString name = QString(type).remove(QStringLiteral("*")).remove(QStringLiteral("Object"));
            return QStringLiteral("[%1](https://github.com/Aseman-Land/libqtelegram-aseman-edition/blob/API51/telegram/documents/types/%2.md)")
                    .arg(name).arg(name.toLower());
        }
        if(type == QStringLiteral("QQmlComponent*"))
            return QStringLiteral("Component");
        if(type == QStringLiteral("QQuickItem"))
            return QStringLiteral("Item");
    }
    if(type.contains(QStringLiteral("Telegram")))
    {
        QString name = QString(type).remove(QStringLiteral("Telegram"));
        return QStringLiteral("[%1](%2.md)").arg(name).arg(name.toLower());
    }
    if(type == QStringLiteral("QQuickItem"))
        return QStringLiteral("Item");
    if(type == QStringLiteral("QObject"))
        return QStringLiteral("object");
    if(type.contains(QStringLiteral("Object")))
    {
        QString name = QString(type).remove(QStringLiteral("Object"));
        return QStringLiteral("[%1](https://github.com/Aseman-Land/libqtelegram-aseman-edition/blob/API51/telegram/documents/types/%2.md)")
                .arg(name).arg(name.toLower());
    }
    return type;
}

template<typename T>
QString AsemanQtToolsItem::exportItem(const QString &module, int major, int minor, const QString &component, bool store)
{
    QString result;
    aseman_qt_tools_indexCache << component;

    QMetaObject meta = T::staticMetaObject;
    QString inherits = fixType(QString::fromUtf8(meta.superClass()? meta.superClass()->className() : ""));
    bool isModel = component.toLower().contains(QStringLiteral("model"));

    result += QStringLiteral("# %1\n\n").arg(component);

    QString headers;
    headers += QStringLiteral(" * [Component details](#component-details)\n");

    QString details = QStringLiteral("\n### Component details:\n\n");
    details += QStringLiteral("|Detail|Value|\n"
                       "|------|-----|\n");
    details += QStringLiteral("|%1|%2 %3.%4|\n").arg(QStringLiteral("Import")).arg(module).arg(major).arg(minor);
    details += QStringLiteral("|%1|<font color='#074885'>%2</font>|\n").arg(QStringLiteral("Component")).arg(component);
    details += QStringLiteral("|%1|<font color='#074885'>%2</font>|\n").arg(QStringLiteral("C++ class")).arg(QString::fromUtf8(meta.className()));
    details += QStringLiteral("|%1|<font color='#074885'>%2</font>|\n").arg(QStringLiteral("Inherits")).arg(inherits);
    details += QStringLiteral("|%1|<font color='#074885'>%2</font>|\n").arg(QStringLiteral("Model")).arg(QString::fromUtf8(isModel?"Yes":"No"));

    QString resultProperties;
    QStringList propertiesSignals;
    for(int i=0; i<meta.propertyCount(); i++)
    {
        QMetaProperty property = meta.property(i);
        const QString &propertyName = QString::fromUtf8(property.name());
        const QString &propertyType = fixType(QString::fromUtf8(property.typeName()));
        propertiesSignals << QString::fromUtf8(property.notifySignal().name());

        QString text = QStringLiteral("* <font color='#074885'><b>%1</b></font>: %2").arg(propertyName).arg(propertyType);
        if(!property.isWritable())
            text += QStringLiteral(" (readOnly)");

        text += QStringLiteral("\n");
        if(meta.propertyOffset()<=i)
            resultProperties += text;
    }

    QString enumResults;
    for(int i=meta.enumeratorOffset(); i<meta.enumeratorCount(); i++)
    {
        QMetaEnum enumerator = meta.enumerator(i);
        const QString &enumName = QString::fromUtf8(enumerator.name());

        enumResults += QStringLiteral("\n##### %1\n\n").arg(enumName);
        enumResults += QStringLiteral("|Key|Value|\n"
                               "|---|-----|\n");

        for(int j=0; j<enumerator.keyCount(); j++)
            enumResults += QStringLiteral("|%1|%2|\n").arg(QString::fromUtf8(enumerator.key(j))).arg(enumerator.value(j));
    }

    QString resultSlots;
    QString resultSignals;
    for(int i=meta.methodOffset(); i<meta.methodCount(); i++)
    {
        QMetaMethod method = meta.method(i);
        if(method.access() != QMetaMethod::Public)
            continue;

        const QString &methodName = QString::fromUtf8(method.name());
        if(propertiesSignals.contains(methodName))
            continue;

        const QString &methodType = fixType(QString::fromUtf8(method.typeName()));

        QString args;
        const QList<QByteArray> &paramNames = method.parameterNames();
        const QList<QByteArray> &paramTypes = method.parameterTypes();
        for(int j=0; j<paramNames.count(); j++)
        {
            if(j != 0)
                args += QStringLiteral(", ");

            args += fixType(QString::fromUtf8(paramTypes[j])) + QStringLiteral(" ") + paramNames[j];
        }

        QString text = QStringLiteral(" * %1 <font color='#074885'><b>%2</b></font>(%3)\n").arg(methodType).arg(methodName).arg(args);
        switch(static_cast<int>(method.methodType()))
        {
        case QMetaMethod::Slot:
            resultSlots += text;
            break;
        case QMetaMethod::Signal:
            resultSignals += text;
            break;
        }
    }

    if(!resultProperties.isEmpty())
    {
        headers += QStringLiteral(" * [Normal Properties](#normal-properties)\n");
        resultProperties = QStringLiteral("\n### Normal Properties\n\n") + resultProperties;
    }
    if(!enumResults.isEmpty())
    {
        headers += QStringLiteral(" * [Enumerator](#enumerator)\n");
        enumResults = QStringLiteral("\n### Enumerator\n\n") + enumResults;
    }
    if(!resultSlots.isEmpty())
    {
        headers += QStringLiteral(" * [Methods](#methods)\n");
        resultSlots = QStringLiteral("\n### Methods\n\n") + resultSlots;
    }
    if(!resultSignals.isEmpty())
    {
        headers += QStringLiteral(" * [Signals](#Q_SIGNALS)\n");
        resultSignals = QStringLiteral("\n### Signals\n\n") + resultSignals;
    }
    if(isModel)
        headers += QStringLiteral(" * [Roles](#roles)\n");

    result += headers + QStringLiteral("\n");
    result += details + QStringLiteral("\n");
    result += resultProperties + QStringLiteral("\n");
    result += resultSlots + QStringLiteral("\n");
    result += resultSignals + QStringLiteral("\n");
    result += enumResults + QStringLiteral("\n");

    if(!store)
        return result;

    QString path = aseman_qt_tools_destination + QStringLiteral("/") + component.toLower() + QStringLiteral(".md");
    QFile file(path);
    if(!file.open(QFile::WriteOnly))
        return result;

    file.write(result.toUtf8());
    file.close();
    return result;
}

template<typename T>
QString AsemanQtToolsItem::exportModel(const QString &module, int major, int minor, const QString &component)
{
    QString result = exportItem<T>(module, major, minor, component, false);
    T *model = new T();

    QHash<qint32,QByteArray> roleNames = model->roleNames();
    QMap<qint32,QByteArray> rolesMap;
    QHashIterator<qint32,QByteArray> i(roleNames);
    while(i.hasNext())
    {
        i.next();
        rolesMap[i.key()] = i.value();
    }

    result += QStringLiteral("\n### Roles\n\n");
    Q_FOREACH(const QByteArray &name, rolesMap)
        result += QStringLiteral(" * model.<font color='#074885'>%1</font>\n").arg(QString::fromUtf8(name));

    delete model;

    QString path = aseman_qt_tools_destination + "/" + component.toLower() + ".md";
    QFile file(path);
    if(!file.open(QFile::WriteOnly))
        return result;

    file.write(result.toUtf8());
    file.close();
    return result;
}
