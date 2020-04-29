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

#include "asemanbackhandler.h"
#include "asemanqttools.h"
#include "asemanquickview.h"
#include "asemanqtlogger.h"
#include "asemandevicesitem.h"
#include "asemantoolsitem.h"
#include "asemanapplicationitem.h"
#include "asemanquickviewwrapper.h"
#include "asemandesktoptools.h"
#include <asemantexttools.h>
#include <asemancalendarconverter.h>

#ifdef Q_OS_ANDROID
#include "asemanjavalayer.h"
#endif

#include <qqml.h>
#include <QHash>
#include <QPointer>
#include <asemanglobaltranslations.h>

void AsemanQtTools::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    Q_UNUSED(engine)
}

AsemanQuickViewWrapper *AsemanQtTools::quickView(QQmlEngine *engine)
{
    static QHash<QQmlEngine*, QPointer<AsemanQuickViewWrapper> > views;
    AsemanQuickViewWrapper *res = views.value(engine);
    if(res)
        return res;

    AsemanQuickView *view = new AsemanQuickView(engine, Q_NULLPTR);
    if(view)
    {
        res = new AsemanQuickViewWrapper(view, engine);
        views[engine] = res;
        return res;
    }

    return res;
}

AsemanApplicationItem *AsemanQtTools::application(QQmlEngine *engine)
{
    static QPointer<AsemanApplicationItem> res;
    if(!res)
        res = new AsemanApplicationItem(engine);

    return res;
}

AsemanDesktopTools *AsemanQtTools::desktopTools()
{
    static QPointer<AsemanDesktopTools> res = 0;
    if(!res)
        res = new AsemanDesktopTools();

    return res;
}

AsemanDevicesItem *AsemanQtTools::devices()
{
    static QPointer<AsemanDevicesItem> res = 0;
    if(!res)
        res = new AsemanDevicesItem();

    return res;
}

AsemanQtLogger *AsemanQtTools::qtLogger()
{
    static QPointer<AsemanQtLogger> res = 0;
    if(!res)
    {
        QString path = QString::fromUtf8(qgetenv("ASEMAN_LOG_PATH"));
        if(path.isEmpty())
            path = AsemanApplicationItem::logPath() + "/log";

        res = new AsemanQtLogger(path);
    }

    return res;
}

#ifdef Q_OS_ANDROID
AsemanJavaLayer *AsemanQtTools::javaLayer()
{
    static QPointer<AsemanJavaLayer> res = 0;
    if(!res)
        res = new AsemanJavaLayer();

    return res;
}
#endif

AsemanToolsItem *AsemanQtTools::tools()
{
    static QPointer<AsemanToolsItem> res = 0;
    if(!res)
        res = new AsemanToolsItem();

    return res;
}

AsemanTextTools *AsemanQtTools::textTools()
{
    static QPointer<AsemanTextTools> res = 0;
    if(!res)
        res = new AsemanTextTools();

    return res;
}

AsemanCalendarConverter *AsemanQtTools::calendar(QQmlEngine *engine)
{
    static QHash<QQmlEngine*, QPointer<AsemanCalendarConverter> > views;
    AsemanCalendarConverter *res = views.value(engine);
    if(res)
        return res;

    res = new AsemanCalendarConverter();
    views[engine] = res;
    return res;
}

AsemanBackHandler *AsemanQtTools::backHandler(QQmlEngine *engine)
{
    static QHash<QQmlEngine*, QPointer<AsemanBackHandler> > views;
    AsemanBackHandler *res = views.value(engine);
    if(res)
        return res;

    res = new AsemanBackHandler();
    views[engine] = res;
    return res;
}

AsemanGlobalTranslations *AsemanQtTools::globalTranslations(QQmlEngine *engine)
{
    static QHash<QQmlEngine*, QPointer<AsemanGlobalTranslations> > translations;
    AsemanGlobalTranslations *res = translations.value(engine);
    if(res)
        return res;

    res = new AsemanGlobalTranslations();
    translations[engine] = res;
    return res;
}
