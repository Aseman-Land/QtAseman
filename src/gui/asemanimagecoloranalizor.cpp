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

#define MAX_ACTIVE_THREADS 4
#define IMAGE_WIDTH 400

#include "asemanimagecoloranalizor.h"
#include "asemandevices.h"

#include <QThread>
#include <QCoreApplication>
#include <QQueue>
#include <QSet>
#include <QImageReader>
#include <QImage>
#include <QFileInfo>
#include <QDebug>

AsemanImageColorAnalizorThread *colorizor_thread = 0;

class AsemanImageColorAnalizorPrivate
{
public:
    QUrl source;
    QColor color;
    int method;
};

AsemanImageColorAnalizor::AsemanImageColorAnalizor(QObject *parent) :
    QObject(parent)
{
    p = new AsemanImageColorAnalizorPrivate;
    p->method = Normal;

    if( !colorizor_thread )
        colorizor_thread = new AsemanImageColorAnalizorThread(QCoreApplication::instance());

    connect( colorizor_thread, &AsemanImageColorAnalizorThread::found, this, &AsemanImageColorAnalizor::found);
}

QUrl AsemanImageColorAnalizor::source() const
{
    return p->source;
}

void AsemanImageColorAnalizor::setSource(const QUrl &source)
{
    if( p->source == source )
        return;

    p->source = source;
    Q_EMIT sourceChanged();

    start();
}

QString AsemanImageColorAnalizor::sourceString() const
{
    QString res = p->source.toString();
    QString pre = p->source.toString(QUrl::RemovePath);
    if(res.left(pre.length()) == pre)
        res = QString::fromUtf8(pre==QStringLiteral("qrc:")?":":"") + res.mid(pre.length());

    return res;
}

int AsemanImageColorAnalizor::method() const
{
    return p->method;
}

void AsemanImageColorAnalizor::setMethod(int m)
{
    if( p->method == m )
        return;

    p->method = static_cast<Method>(m);
    Q_EMIT methodChanged();

    start();
}

QColor AsemanImageColorAnalizor::color() const
{
    return p->color;
}

void AsemanImageColorAnalizor::found(int method, const QString &path)
{
    if( method != p->method )
        return;
    if( path != sourceString() )
        return;

    const QHash<int, QHash<QString,QColor> > & results = colorizor_thread->results();
    if( !results.contains(p->method) || !results.value(p->method).contains(sourceString()) )
        return;

    p->color = results[p->method][sourceString()];
    Q_EMIT colorChanged();
}

void AsemanImageColorAnalizor::start()
{
    if( p->source.isEmpty() )
        return;

    colorizor_thread->analize(p->method, sourceString());
    found(p->method,sourceString());
}

AsemanImageColorAnalizor::~AsemanImageColorAnalizor()
{
    delete p;
}


class AsemanImageColorAnalizorThreadPrivate
{
public:
    QHash<int, QHash<QString,QColor> > results;

    QQueue< QPair<int,QString> > queue;
    QSet<AsemanImageColorAnalizorCore*> cores;
    QQueue<AsemanImageColorAnalizorCore*> free_cores;
};

AsemanImageColorAnalizorThread::AsemanImageColorAnalizorThread(QObject *parent) :
    QObject(parent)
{
    p = new AsemanImageColorAnalizorThreadPrivate;
}

const QHash<int, QHash<QString,QColor> > &AsemanImageColorAnalizorThread::results() const
{
    return p->results;
}

void AsemanImageColorAnalizorThread::analize(int method, const QString &path)
{
    if( p->results.contains(method) && p->results.value(method).contains(path) )
        return;

    AsemanImageColorAnalizorCore *core = getCore();
    if( !core )
    {
        QPair<int,QString> pair(method, path);
        p->queue.append(pair);
        return;
    }

    QMetaObject::invokeMethod( core, "analize", Qt::QueuedConnection, Q_ARG(int,method) , Q_ARG(QString,path) );
}

void AsemanImageColorAnalizorThread::found_slt(AsemanImageColorAnalizorCore *c, int method, const QString &source, const QColor & color)
{
    p->results[method][source] = color;
    Q_EMIT found(method, source);

    p->free_cores.append(c);
    if( p->queue.isEmpty() )
        return;

    AsemanImageColorAnalizorCore *core = getCore();
    if( !core )
        return;

    const QPair<int,QString> & pair = p->queue.takeFirst();
    QMetaObject::invokeMethod( core, "analize", Qt::QueuedConnection, Q_ARG(int,pair.first), Q_ARG(QString,pair.second) );
}

AsemanImageColorAnalizorCore *AsemanImageColorAnalizorThread::getCore()
{
    if( !p->free_cores.isEmpty() )
        return p->free_cores.takeFirst();
    if( p->cores.count() > MAX_ACTIVE_THREADS )
        return 0;

    QThread *thread = new QThread(this);

    AsemanImageColorAnalizorCore *core = new AsemanImageColorAnalizorCore();
    core->moveToThread(thread);

    connect( core, &AsemanImageColorAnalizorCore::found, this, &AsemanImageColorAnalizorThread::found_slt, Qt::QueuedConnection );

    thread->start(QThread::LowestPriority);
    p->cores.insert(core);

    return core;
}

AsemanImageColorAnalizorThread::~AsemanImageColorAnalizorThread()
{
    for(AsemanImageColorAnalizorCore *core: p->cores)
    {
        QThread *thread = core->thread();
        thread->quit();
        thread->wait();
        core->deleteLater();
    }

    delete p;
}


class AsemanImageColorAnalizorCorePrivate
{
public:
};

AsemanImageColorAnalizorCore::AsemanImageColorAnalizorCore(QObject *parent) :
    QObject(parent)
{
    p = new AsemanImageColorAnalizorCorePrivate;
}

void AsemanImageColorAnalizorCore::analize(int method, const QString &pt)
{
    QString path = pt;
    if(path.left(AsemanDevices::localFilesPrePath().size()) == AsemanDevices::localFilesPrePath())
        path = path.mid(AsemanDevices::localFilesPrePath().size());

    QImageReader image(path);

    QSize image_size = image.size();
    qreal ratio = image_size.width()/(qreal)image_size.height();
    image_size.setWidth( IMAGE_WIDTH );
    image_size.setHeight( IMAGE_WIDTH/ratio );

    image.setScaledSize( image_size );
    const QImage & img = image.read();

    QColor result;

    switch( method )
    {
    case AsemanImageColorAnalizor::Normal:
    {
        qreal sum_r = 0;
        qreal sum_g = 0;
        qreal sum_b = 0;
        int count = 0;

        for( int i=0 ; i<image_size.width(); i++ )
        {
            for( int j=0 ; j<image_size.height(); j++ )
            {
                QColor clr = img.pixel(i,j);
                qreal mid = (clr.red()+clr.green()+clr.blue())/3;
                if( mid > 180 || mid < 70 )
                    continue;

                sum_r += clr.red();
                sum_g += clr.green();
                sum_b += clr.blue();
                count++;
            }
        }

        result = QColor( sum_r/count, sum_g/count, sum_b/count );
    }
        break;

    case AsemanImageColorAnalizor::MoreSaturation:
    {
        qreal sum_r = 0;
        qreal sum_g = 0;
        qreal sum_b = 0;
        int count = 0;

        for( int i=0 ; i<image_size.width(); i++ )
        {
            for( int j=0 ; j<image_size.height(); j++ )
            {
                QColor clr = img.pixel(i,j);
                if( clr.saturation() < 150 || clr.lightness() < 50 )
                    continue;

                sum_r += clr.red();
                sum_g += clr.green();
                sum_b += clr.blue();
                count++;
            }
        }

        result = QColor( sum_r/count, sum_g/count, sum_b/count );
    }
        break;
    }

    Q_EMIT found( this, method, path, result );
}

AsemanImageColorAnalizorCore::~AsemanImageColorAnalizorCore()
{
    delete p;
}
