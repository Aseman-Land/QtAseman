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

#ifndef ASEMANIMAGECOLORANALIZOR_H
#define ASEMANIMAGECOLORANALIZOR_H

#include <QObject>
#include <QColor>
#include <QHash>
#include <QUrl>

#include "asemangui_global.h"

class AsemanImageColorAnalizorPrivate;
class LIBQTASEMAN_GUI_EXPORT AsemanImageColorAnalizor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(int method READ method WRITE setMethod NOTIFY methodChanged)
    Q_ENUMS(Method)

public:
    enum Method {
        Normal,
        MoreSaturation
    };

    AsemanImageColorAnalizor(QObject *parent = Q_NULLPTR);
    virtual ~AsemanImageColorAnalizor();

    QUrl source() const;
    void setSource( const QUrl & source );

    int method() const;
    void setMethod( int m );

    QColor color() const;

Q_SIGNALS:
    void sourceChanged();
    void colorChanged();
    void methodChanged();

private Q_SLOTS:
    void found(int method, const QString & path );
    void start();

private:
    QString sourceString() const;

private:
    AsemanImageColorAnalizorPrivate *p;
};


class AsemanImageColorAnalizorThreadPrivate;
class AsemanImageColorAnalizorThread : public QObject
{
    Q_OBJECT
public:
    AsemanImageColorAnalizorThread(QObject *parent = Q_NULLPTR);
    virtual ~AsemanImageColorAnalizorThread();

    const QHash<int, QHash<QString, QColor> > &results() const;

public Q_SLOTS:
    void analize(int method, const QString & path );

Q_SIGNALS:
    void found( int method, const QString & path );

private Q_SLOTS:
    void found_slt(class AsemanImageColorAnalizorCore *core, int method, const QString & path , const QColor &color);

private:
    AsemanImageColorAnalizorCore *getCore();

private:
    AsemanImageColorAnalizorThreadPrivate *p;
};

typedef AsemanImageColorAnalizor QAsemanImageColorAnalizor;


class AsemanImageColorAnalizorCorePrivate;
class AsemanImageColorAnalizorCore : public QObject
{
    Q_OBJECT
public:
    AsemanImageColorAnalizorCore(QObject *parent = Q_NULLPTR);
    virtual ~AsemanImageColorAnalizorCore();

public Q_SLOTS:
    void analize( int method, const QString & path );

Q_SIGNALS:
    void found(AsemanImageColorAnalizorCore *core, int method, const QString & path , const QColor &color);

private:
    AsemanImageColorAnalizorCorePrivate *p;
};

#endif // ASEMANIMAGECOLORANALIZOR_H
