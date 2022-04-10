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

#include "asemandesktoptools.h"

#include <QProcess>
#include <QStringList>
#include <QPalette>
#include <QEventLoop>
#include <QFontDatabase>
#include <QDebug>

#if defined(QT_WIDGETS_LIB)
#include <QFileDialog>
#endif

#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
#include <QInputDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QToolTip>
#endif

class AsemanDesktopToolsPrivate
{
public:
    QFontDatabase *font_db;
    QString style;
    QString tooltip;
#ifdef DESKTOP_DEVICE
    QList<QMenu*> currentMenuObjects;
#endif
};

AsemanDesktopTools::AsemanDesktopTools(QObject *parent) :
    QObject(parent)
{
    p = new AsemanDesktopToolsPrivate;
    p->font_db = 0;
}

int AsemanDesktopTools::desktopSession()
{
    static int result = -1;
    if( result != -1 )
        return result;

#ifdef Q_OS_MAC
    result = AsemanDesktopTools::Mac;
#else
#ifdef Q_OS_WIN
    result = AsemanDesktopTools::Windows;
#else
    static QString *desktop_session = 0;
    if( !desktop_session )
        desktop_session = new QString( QString::fromUtf8(qgetenv("DESKTOP_SESSION")) );

    if( desktop_session->contains(QStringLiteral("kde"),Qt::CaseInsensitive) )
        result = AsemanDesktopTools::Kde;
    else
    if( desktop_session->contains(QStringLiteral("plasma"),Qt::CaseInsensitive) )
        result = AsemanDesktopTools::Plasma;
    else
    if( desktop_session->contains(QStringLiteral("ubuntu"),Qt::CaseInsensitive) )
        result = AsemanDesktopTools::Unity;
    else
    if( desktop_session->contains(QStringLiteral("gnome-fallback"),Qt::CaseInsensitive) )
        result = AsemanDesktopTools::GnomeFallBack;
    else
    if( desktop_session->contains(QStringLiteral("gnome"),Qt::CaseInsensitive) )
        result = AsemanDesktopTools::Gnome;
#endif
#endif

    if( result == -1 )
        result = AsemanDesktopTools::Unknown;

    return result;
}

QColor AsemanDesktopTools::titleBarColor() const
{
#ifdef DESKTOP_DEVICE
    const int dsession = desktopSession();
    switch( dsession )
    {
    case AsemanDesktopTools::Mac:
        return QColor("#C8C8C8");
        break;

    case AsemanDesktopTools::Windows:
        return QColor("#E5E5E5");
        break;

    case AsemanDesktopTools::Kde:
    case AsemanDesktopTools::Plasma:
        return QPalette().window().color();
        break;

    case AsemanDesktopTools::Unity:
    case AsemanDesktopTools::GnomeFallBack:
    case AsemanDesktopTools::Gnome:
    {
        static QColor *res = 0;
        if( !res )
        {
            QProcess prc;
            prc.start(QStringLiteral("dconf"), QStringList()<< QStringLiteral("read")<< QStringLiteral("/org/gnome/desktop/interface/gtk-theme"));
            prc.waitForStarted();
            prc.waitForFinished();
            QString sres = QString::fromUtf8(prc.readAll());
            sres.remove(QStringLiteral("\n")).remove(QStringLiteral("'"));
            sres = sres.toLower();

            if( sres == QStringLiteral("ambiance") )
                res = new QColor("#403F3A");
            else
            if( sres == QStringLiteral("radiance") )
                res = new QColor("#DFD7CF");
            else
            if( sres == QStringLiteral("adwaita") )
                res = new QColor("#EDEDED");
            else
            if( dsession == AsemanDesktopTools::Unity )
                res = new QColor("#403F3A");
            else
                res = new QColor("#EDEDED");
        }

        return *res;
    }
        break;
    }

    return QColor("#EDEDED");
#else
    return QColor("#111111");
#endif
}

QColor AsemanDesktopTools::titleBarTransparentColor() const
{
    QColor color = titleBarColor();
    color.setAlpha(160);
    return color;
}

QColor AsemanDesktopTools::titleBarTextColor() const
{
#ifdef DESKTOP_DEVICE
    const int dsession = desktopSession();
    switch( dsession )
    {
    case AsemanDesktopTools::Mac:
        return QColor("#333333");
        break;

    case AsemanDesktopTools::Windows:
        return QColor("#333333");
        break;

    case AsemanDesktopTools::Kde:
    case AsemanDesktopTools::Plasma:
        return QPalette().windowText().color();
        break;

    case AsemanDesktopTools::Unity:
    case AsemanDesktopTools::GnomeFallBack:
    case AsemanDesktopTools::Gnome:
    {
        static QColor *res = 0;
        if( !res )
        {
            QProcess prc;
            prc.start( QStringLiteral("dconf"), QStringList()<< QStringLiteral("read")<< QStringLiteral("/org/gnome/desktop/interface/gtk-theme") );
            prc.waitForStarted();
            prc.waitForFinished();
            QString sres = QString::fromUtf8(prc.readAll());
            sres.remove(QStringLiteral("\n")).remove(QStringLiteral("'"));
            sres = sres.toLower();

            if( sres == QStringLiteral("ambiance") )
                res = new QColor("#eeeeee");
            else
            if( sres == QStringLiteral("radiance") )
                res = new QColor("#333333");
            else
            if( sres == QStringLiteral("adwaita") )
                res = new QColor("#333333");
            else
            if( dsession == AsemanDesktopTools::Unity )
                res = new QColor("#eeeeee");
            else
                res = new QColor("#333333");
        }

        return *res;
    }
        break;
    }

    return QColor("#333333");
#else
    return QColor("#ffffff");
#endif
}

bool AsemanDesktopTools::titleBarIsDark() const
{
    const QColor & clr = titleBarColor();
    qreal middle = (clr.green()+clr.red()+clr.blue())/3.0;
    if( middle>128 )
        return false;
    else
        return true;
}

QStringList AsemanDesktopTools::fontFamilies() const
{
    if(!p->font_db)
        p->font_db = new QFontDatabase();

    return p->font_db->families();
}

void AsemanDesktopTools::setMenuStyle(const QString &style)
{
    if(p->style == style)
        return;

    p->style = style;
    Q_EMIT menuStyleChanged();
}

QString AsemanDesktopTools::menuStyle() const
{
    return p->style;
}

void AsemanDesktopTools::setTooltip(const QString &txt)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    QToolTip::hideText();
    if(!txt.isEmpty())
        QToolTip::showText(QCursor::pos(), txt);
#endif

    if(p->tooltip == txt)
        return;

    p->tooltip = txt;
    Q_EMIT tooltipChanged();
}

QString AsemanDesktopTools::tooltip() const
{
    return p->tooltip;
}

QObject *AsemanDesktopTools::currentMenuObject() const
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    if(p->currentMenuObjects.isEmpty())
        return 0;

    return p->currentMenuObjects.last();
#else
    return 0;
#endif
}

QString AsemanDesktopTools::getOpenFileName(QWindow *window, const QString & title, const QString &filter, const QString &startPath)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    const int dsession = desktopSession();
    switch( dsession )
    {
    case AsemanDesktopTools::Kde:
    case AsemanDesktopTools::Plasma:
        if( QFileInfo::exists(QStringLiteral("/usr/bin/kdialog")) )
        {
            QStringList args = QStringList()<< QStringLiteral("--title") << title << QStringLiteral("--getopenfilename")
                                            << startPath << filter;
            if( window )
                args << QStringLiteral("--attach") << QString::number(window->winId());

            QProcess process;
            QEventLoop loop;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            connect(&process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::quit, Qt::QueuedConnection );
#else
            connect(&process, &QProcess::finished, &loop, &QEventLoop::quit, Qt::QueuedConnection );
#endif

            process.start(QStringLiteral("/usr/bin/kdialog"), args );
            loop.exec(QEventLoop::ExcludeUserInputEvents);

            if( process.exitStatus() == QProcess::NormalExit )
                return QString::fromUtf8(process.readAll()).remove(QStringLiteral("\n"));
            else
                return QFileDialog::getOpenFileName(0, title, startPath, filter);
        }
        else
            return QFileDialog::getOpenFileName(0, title, startPath, filter);
        break;

    case AsemanDesktopTools::Unity:
    case AsemanDesktopTools::GnomeFallBack:
    case AsemanDesktopTools::Gnome:
        if( QFileInfo::exists(QStringLiteral("/usr/bin/zenity")) )
        {
            QStringList args = QStringList()<< QStringLiteral("--title=") << QStringLiteral("--file-selection") <<
                                               QStringLiteral("--class=Cutegram") << QStringLiteral("--name=Cutegram");
            if(!filter.isEmpty())
                args << QStringLiteral("--file-filter=") + filter;

            QProcess process;
            QEventLoop loop;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            connect(&process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::quit, Qt::QueuedConnection );
#else
            connect(&process, &QProcess::finished, &loop, &QEventLoop::quit, Qt::QueuedConnection );
#endif

            process.start(QStringLiteral("/usr/bin/zenity"), args );
            loop.exec(QEventLoop::ExcludeUserInputEvents);

            if( process.exitStatus() == QProcess::NormalExit )
                return QString::fromUtf8(process.readAll()).remove(QStringLiteral("\n"));
            else
                return QFileDialog::getOpenFileName(0, title, startPath, filter);
        }
        else
            return QFileDialog::getOpenFileName(0, title, startPath, filter);
        break;

    case AsemanDesktopTools::Mac:
    case AsemanDesktopTools::Windows:
        return QFileDialog::getOpenFileName(0, title, startPath, filter);
        break;
    }

    return QString();
#else
#if defined(QT_WIDGETS_LIB)
    return QFileDialog::getOpenFileName(0, title, startPath, filter);
#else
    Q_UNUSED(window)
    Q_UNUSED(title)
    Q_UNUSED(filter)
    Q_UNUSED(startPath)
    return QString();
#endif
#endif
}

QStringList AsemanDesktopTools::getOpenFileNames(QWindow *window, const QString &title, const QString &filter, const QString &startPath)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    const int dsession = desktopSession();
    switch( dsession )
    {
    case AsemanDesktopTools::Kde:
    case AsemanDesktopTools::Plasma:
        if( QFileInfo::exists(QStringLiteral("/usr/bin/kdialog")) )
        {
            QStringList args = QStringList()<< QStringLiteral("--title") << title << QStringLiteral("--getopenfilename")
                                            << startPath << filter;
            if( window )
                args << QStringLiteral("--attach") << QString::number(window->winId());

            QProcess process;
            QEventLoop loop;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            connect(&process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::quit, Qt::QueuedConnection );
#else
            connect(&process, &QProcess::finished, &loop, &QEventLoop::quit, Qt::QueuedConnection );
#endif

            process.start(QStringLiteral("/usr/bin/kdialog"), args );
            loop.exec(QEventLoop::ExcludeUserInputEvents);

            if( process.exitStatus() == QProcess::NormalExit )
                return QStringList() << QString::fromUtf8(process.readAll()).remove(QStringLiteral("\n"));
            else
                return QFileDialog::getOpenFileNames(0, title, startPath, filter);
        }
        else
            return QFileDialog::getOpenFileNames(0, title, startPath, filter);
        break;

    case AsemanDesktopTools::Unity:
    case AsemanDesktopTools::GnomeFallBack:
    case AsemanDesktopTools::Gnome:
        if( QFileInfo::exists(QStringLiteral("/usr/bin/zenity")) )
        {
            QStringList args = QStringList()<< QStringLiteral("--title=") << QStringLiteral("--file-selection") <<
                                               QStringLiteral("--class=Cutegram") << QStringLiteral("--name=Cutegram");
            if(!filter.isEmpty())
                args << QStringLiteral("--file-filter=") + filter;

            QProcess process;
            QEventLoop loop;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            connect(&process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::quit, Qt::QueuedConnection );
#else
            connect(&process, &QProcess::finished, &loop, &QEventLoop::quit, Qt::QueuedConnection );
#endif

            process.start(QStringLiteral("/usr/bin/zenity"), args );
            loop.exec(QEventLoop::ExcludeUserInputEvents);

            if( process.exitStatus() == QProcess::NormalExit )
                return QStringList() << QString::fromUtf8(process.readAll()).remove(QStringLiteral("\n"));
            else
                return QFileDialog::getOpenFileNames(0, title, startPath, filter);
        }
        else
            return QFileDialog::getOpenFileNames(0, title, startPath, filter);
        break;

    case AsemanDesktopTools::Mac:
    case AsemanDesktopTools::Windows:
        return QFileDialog::getOpenFileNames(0, title, startPath, filter);
        break;
    }

    return QStringList();
#else
#if defined(QT_WIDGETS_LIB)
    return QFileDialog::getOpenFileNames(0, title, startPath, filter);
#else
#endif
    Q_UNUSED(window)
    Q_UNUSED(title)
    Q_UNUSED(filter)
    Q_UNUSED(startPath)
    return QStringList();
#endif
}

QString AsemanDesktopTools::getSaveFileName(QWindow *window, const QString &title, const QString &filter, const QString &startPath)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    const int dsession = desktopSession();
    switch( dsession )
    {
    case AsemanDesktopTools::Kde:
    case AsemanDesktopTools::Plasma:
        if( QFileInfo::exists(QStringLiteral("/usr/bin/kdialog")) )
        {
            QStringList args = QStringList()<< QStringLiteral("--title") << title << QStringLiteral("--getsavefilename")
                                            << startPath << filter;
            if( window )
                args << QStringLiteral("--attach") << QString::number(window->winId());

            QProcess process;
            QEventLoop loop;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            connect(&process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::quit, Qt::QueuedConnection );
#else
            connect(&process, &QProcess::finished, &loop, &QEventLoop::quit, Qt::QueuedConnection );
#endif

            process.start(QStringLiteral("/usr/bin/kdialog"), args );
            loop.exec(QEventLoop::ExcludeUserInputEvents);

            if( process.exitStatus() == QProcess::NormalExit )
                return QString::fromUtf8(process.readAll()).remove(QStringLiteral("\n"));
            else
                return QFileDialog::getSaveFileName(0, title, startPath, filter);
        }
        else
        {
            return QFileDialog::getSaveFileName(0, title, startPath, filter);
        }
        break;

    case AsemanDesktopTools::Unity:
    case AsemanDesktopTools::GnomeFallBack:
    case AsemanDesktopTools::Gnome:
        if( QFileInfo::exists(QStringLiteral("/usr/bin/zenity")) )
        {
            QStringList args = QStringList()<< QStringLiteral("--title=") << QStringLiteral("--file-selection") << QStringLiteral("--save") <<
                                               QStringLiteral("--class=Cutegram") << QStringLiteral("--name=Cutegram");
            if(!filter.isEmpty())
                args << QStringLiteral("--file-filter=") + filter;

            QProcess process;
            QEventLoop loop;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            connect(&process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::quit, Qt::QueuedConnection );
#else
            connect(&process, &QProcess::finished, &loop, &QEventLoop::quit, Qt::QueuedConnection );
#endif

            process.start(QStringLiteral("/usr/bin/zenity"), args );
            loop.exec(QEventLoop::ExcludeUserInputEvents);

            if( process.exitStatus() == QProcess::NormalExit )
                return QString::fromUtf8(process.readAll()).remove(QStringLiteral("\n"));
            else
                return QFileDialog::getSaveFileName(0, title, startPath, filter);
        }
        else
            return QFileDialog::getSaveFileName(0, title, startPath, filter);
        break;

    case AsemanDesktopTools::Mac:
    case AsemanDesktopTools::Windows:
        return QFileDialog::getSaveFileName(0, title, startPath, filter);
        break;
    }

    return QString();
#else
#if defined(QT_WIDGETS_LIB)
    return QFileDialog::getSaveFileName(0, title, startPath, filter);
#else
    Q_UNUSED(window)
    Q_UNUSED(title)
    Q_UNUSED(filter)
    Q_UNUSED(startPath)
    return QString();
#endif
#endif
}

QString AsemanDesktopTools::getExistingDirectory(QWindow *window, const QString &title, const QString &startPath)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    const int dsession = desktopSession();
    switch( dsession )
    {
    case AsemanDesktopTools::Kde:
    case AsemanDesktopTools::Plasma:
        if( QFileInfo::exists(QStringLiteral("/usr/bin/kdialog")) )
        {
            QStringList args = QStringList()<< QStringLiteral("--title") << title << QStringLiteral("--getexistingdirectory")
                                            << startPath;
            if( window )
                args << QStringLiteral("--attach") << QString::number(window->winId());

            QProcess process;
            QEventLoop loop;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            connect(&process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::quit, Qt::QueuedConnection );
#else
            connect(&process, &QProcess::finished, &loop, &QEventLoop::quit, Qt::QueuedConnection );
#endif

            process.start(QStringLiteral("/usr/bin/kdialog"), args );
            loop.exec(QEventLoop::ExcludeUserInputEvents);

            if( process.exitStatus() == QProcess::NormalExit )
                return QString::fromUtf8(process.readAll()).remove(QStringLiteral("\n"));
            else
                return QFileDialog::getExistingDirectory(0, title, startPath);
        }
        else
        {
            return QFileDialog::getExistingDirectory(0, title, startPath);
        }
        break;

    case AsemanDesktopTools::Unity:
    case AsemanDesktopTools::GnomeFallBack:
    case AsemanDesktopTools::Gnome:
        if( QFileInfo::exists(QStringLiteral("/usr/bin/zenity")) )
        {
            QStringList args = QStringList()<< QStringLiteral("--title=") << QStringLiteral("--file-selection") << QStringLiteral("--directory") <<
                                               QStringLiteral("--class=Cutegram") << QStringLiteral("--name=Cutegram");

            QProcess process;
            QEventLoop loop;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
            connect(&process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::quit, Qt::QueuedConnection );
#else
            connect(&process, &QProcess::finished, &loop, &QEventLoop::quit, Qt::QueuedConnection );
#endif

            process.start(QStringLiteral("/usr/bin/zenity"), args );
            loop.exec(QEventLoop::ExcludeUserInputEvents);

            if( process.exitStatus() == QProcess::NormalExit )
                return QString::fromUtf8(process.readAll()).remove(QStringLiteral("\n"));
            else
                return QFileDialog::getExistingDirectory(0, title, startPath);
        }
        else
            return QFileDialog::getExistingDirectory(0, title, startPath);
        break;

    case AsemanDesktopTools::Mac:
    case AsemanDesktopTools::Windows:
        return QFileDialog::getExistingDirectory(0, title, startPath);
        break;
    }

    return QString();
#else
#if defined(QT_WIDGETS_LIB)
    return QFileDialog::getExistingDirectory(0, title, startPath);
#else
    Q_UNUSED(window)
    Q_UNUSED(title)
    Q_UNUSED(startPath)
    return QString();
#endif
#endif
}

QFont AsemanDesktopTools::getFont(QWindow *window, const QString &title, const QFont &font)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    Q_UNUSED(window)
    bool ok = false;
    return QFontDialog::getFont(&ok, font, 0, title);
#else
    Q_UNUSED(window)
    Q_UNUSED(title)
    Q_UNUSED(font)
    return font;
#endif
}

QColor AsemanDesktopTools::getColor(const QColor &color)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    return QColorDialog::getColor(color);
#else
    return color;
#endif
}

QString AsemanDesktopTools::getText(QWindow *window, const QString &title, const QString &text, const QString &defaultText)
{
    Q_UNUSED(window)
    Q_UNUSED(title)
    Q_UNUSED(text)
    Q_UNUSED(defaultText)

#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    bool ok = false;
    const QString &result = QInputDialog::getText(0, title, text, QLineEdit::Normal, defaultText, &ok);
    if(!ok)
        return QString();

    return result;
#else
    return QString();
#endif
}

int AsemanDesktopTools::showMenu(const QVariantList &actions, QPoint point)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    if( point.isNull() )
        point = QCursor::pos();

    QList<QAction*> pointers;
    QMenu *menu = menuOf(actions, &pointers);
    menu->setStyleSheet(p->style);

    p->currentMenuObjects.append(menu);
    Q_EMIT currentMenuObjectChanged();

    QAction *res = menu->exec(point);

    p->currentMenuObjects.removeAll(menu);
    Q_EMIT currentMenuObjectChanged();

    menu->deleteLater();

    return pointers.indexOf(res);
#else
    Q_UNUSED(actions)
    Q_UNUSED(point)
    return -1;
#endif
}

QMenu *AsemanDesktopTools::menuOf(const QVariantList &list, QList<QAction *> *actions, QMenu *parent)
{
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    QMenu *result = new QMenu(parent);
    for(const QVariant &var: list)
    {
        QString txt;
        bool checkable = false;
        bool checked = false;
        QVariantList list;

        switch(static_cast<int>(var.type()))
        {
        case QVariant::Map:
        {
            const QVariantMap &map = var.toMap();
            checkable = map[QStringLiteral("checkable")].toBool();
            checked = map[QStringLiteral("checked")].toBool();
            txt = map[QStringLiteral("text")].toString();
            list = map[QStringLiteral("list")].toList();
        }
            break;

        default:
            txt = var.toString();
            break;
        }

        QAction *act;
        if(list.isEmpty())
        {
            act = (txt.isEmpty()? result->addSeparator() : result->addAction(txt));
            act->setCheckable(checkable);
            if(checkable)
                act->setChecked(checked);
        }
        else
        {
            QMenu *menu = menuOf(list, actions, result);
            menu->setTitle(txt);

            act = result->addMenu(menu);
        }

        (*actions) << act;
    }

    return result;
#else
    Q_UNUSED(list)
    Q_UNUSED(actions)
    Q_UNUSED(parent)
    return 0;
#endif
}

bool AsemanDesktopTools::yesOrNo(QWindow *window, const QString &title, const QString &text, int type)
{
    Q_UNUSED(window)
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    switch(type)
    {
    case Warning:
        return QMessageBox::warning(0, title, text, QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes;
        break;

    case Information:
        return QMessageBox::information(0, title, text, QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes;
        break;

    case Question:
        return QMessageBox::question(0, title, text, QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes;
        break;

    case Critical:
        return QMessageBox::critical(0, title, text, QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes;
        break;
    }

    return false;
#else
    Q_UNUSED(title)
    Q_UNUSED(text)
    Q_UNUSED(type)
    return false;
#endif
}

void AsemanDesktopTools::showMessage(QWindow *window, const QString &title, const QString &text, int type)
{
    Q_UNUSED(window)
#if defined(DESKTOP_DEVICE) && defined(QT_WIDGETS_LIB)
    switch(type)
    {
    case Warning:
        QMessageBox::warning(0, title, text, QMessageBox::Ok);
        break;

    case Information:
        QMessageBox::information(0, title, text, QMessageBox::Ok);
        break;

    case Question:
        QMessageBox::question(0, title, text, QMessageBox::Ok);
        break;

    case Critical:
        QMessageBox::critical(0, title, text, QMessageBox::Ok);
        break;
    }
#else
    Q_UNUSED(title)
    Q_UNUSED(text)
    Q_UNUSED(type)
    return;
#endif
}

AsemanDesktopTools::~AsemanDesktopTools()
{
    if(p->font_db)
        delete p->font_db;

    delete p;
}
