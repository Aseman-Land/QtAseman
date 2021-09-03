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
#include "asemanapplicationsingleton.h"
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
    AsemanQuickView *view = new AsemanQuickView(engine, Q_NULLPTR);
    return new AsemanQuickViewWrapper(view, engine);
}

AsemanApplicationSingleton *AsemanQtTools::application(QQmlEngine *engine)
{
    return new AsemanApplicationSingleton(engine);
}

AsemanDesktopTools *AsemanQtTools::desktopTools()
{
    return new AsemanDesktopTools();
}

AsemanDevicesItem *AsemanQtTools::devices()
{
    return new AsemanDevicesItem();
}

AsemanQtLogger *AsemanQtTools::qtLogger()
{
    QString path = QString::fromUtf8(qgetenv("ASEMAN_LOG_PATH"));
    if(path.isEmpty())
        path = AsemanApplicationItem::logPath() + "/log";

    return new AsemanQtLogger(path);
}

#ifdef Q_OS_ANDROID
AsemanJavaLayer *AsemanQtTools::javaLayer()
{
    return new AsemanJavaLayer();
}
#endif

AsemanToolsItem *AsemanQtTools::tools()
{
    return new AsemanToolsItem();
}

AsemanTextTools *AsemanQtTools::textTools()
{
    return new AsemanTextTools();
}

AsemanCalendarConverter *AsemanQtTools::calendar(QQmlEngine *)
{
    return new AsemanCalendarConverter();
}

AsemanBackHandler *AsemanQtTools::backHandler(QQmlEngine *)
{
    return new AsemanBackHandler();
}

AsemanGlobalTranslations *AsemanQtTools::globalTranslations(QQmlEngine *)
{
    return new AsemanGlobalTranslations();
}
