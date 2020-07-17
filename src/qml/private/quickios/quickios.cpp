#include <QtQml>
#include <QtGui>
#include <QVariantMap>
#include <QPointer>
#include "quickios.h"
#include "qisystemdispatcher.h"
#include "qidevice.h"
#include "qiimagepicker.h"

void QuickIOS::setStatusBarStyle(QuickIOS::StatusBarStyle style)
{
    QISystemDispatcher *system = QISystemDispatcher::instance();
    QVariantMap data;
    data["style"] = style;

    system->dispatch("applicationSetStatusBarStyle",data);
}

void QuickIOS::setStatusBarHidden(bool hidden, int animation)
{
    QISystemDispatcher* dispatcher = QISystemDispatcher::instance();
    QVariantMap message;
    message["hidden"] = hidden;
    message["animation"] = animation;
    dispatcher->dispatch("applicationSetStatusBarHidden", message);
}
