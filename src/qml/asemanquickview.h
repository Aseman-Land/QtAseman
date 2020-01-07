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

#ifndef ASEMANQUICKVIEW_H
#define ASEMANQUICKVIEW_H

#include <QQuickView>
#include <QQmlEngine>

#include "asemantools_global.h"

class AsemanBackHandler;
class AsemanDesktopTools;
class AsemanDevicesItem;
class AsemanJavaLayer;
class AsemanQtLogger;
class AsemanToolsItem;
class AsemanCalendarConverter;
class AsemanQuickViewPrivate;
class LIBQTASEMAN_QML_EXPORT AsemanQuickView : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool reverseScroll READ reverseScroll WRITE setReverseScroll NOTIFY reverseScrollChanged)

    Q_PROPERTY(qreal statusBarHeight READ statusBarHeight NOTIFY statusBarHeightChanged)
    Q_PROPERTY(qreal navigationBarHeight READ navigationBarHeight NOTIFY navigationBarHeightChanged)

    Q_PROPERTY(QObject*    root        READ root        WRITE setRoot        NOTIFY rootChanged)
    Q_PROPERTY(QQuickItem* focusedText READ focusedText WRITE setFocusedText NOTIFY focusedTextChanged)

    Q_PROPERTY(int layoutDirection READ layoutDirection WRITE setLayoutDirection NOTIFY layoutDirectionChanged)
    Q_PROPERTY(QString offlineStoragePath READ offlineStoragePath WRITE setOfflineStoragePath NOTIFY offlineStoragePathChanged)

    Q_PROPERTY(qreal flickVelocity READ flickVelocity NOTIFY fakeSignal)

public:
    AsemanQuickView(QQmlEngine *engine, QObject *parent = 0);
    virtual ~AsemanQuickView();

    AsemanDesktopTools *desktopTools() const;
    AsemanDevicesItem *devices() const;
    AsemanQtLogger *qtLogger() const;
    AsemanToolsItem *tools() const;
#ifdef Q_OS_ANDROID
    AsemanJavaLayer *javaLayer() const;
#endif
    AsemanCalendarConverter *calendar() const;
    AsemanBackHandler *backHandler() const;

    void setReverseScroll(bool stt);
    bool reverseScroll() const;

    qreal statusBarHeight() const;
    qreal navigationBarHeight() const;

    void setRoot( QObject *root );
    QObject *root() const;

    void setFocusedText( QQuickItem *item );
    QQuickItem *focusedText() const;

    int layoutDirection() const;
    void setLayoutDirection( int l );

    qreal flickVelocity() const;

    void setOfflineStoragePath(const QString &path);
    QString offlineStoragePath() const;

    Q_INVOKABLE void registerWindow(QQuickWindow *window);

public Q_SLOTS:
    void discardFocusedText();

Q_SIGNALS:
    void statusBarHeightChanged();
    void navigationBarHeightChanged();
    void rootChanged();
    void focusedTextChanged();
    void layoutDirectionChanged();
    void reverseScrollChanged();
    void fakeSignal();
    void closeRequest();
    void offlineStoragePathChanged();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    AsemanQuickViewPrivate *p;
};

typedef AsemanQuickView QAsemanQuickView;

#endif // ASEMANQUICKVIEW_H
