/*
    Copyright (C) 2018 Aseman Team
    http://aseman.co

    This file copied from AsemanServer project.
    AsemanServer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanServer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemansocketinterface.h"

#include <QBuffer>
#include <QDataStream>
#include <QEventLoop>
#include <QMetaMethod>
#include <QVariant>
#include <QHash>
#include <QDebug>
#include <QTimer>
#include <QPointer>

class AsemanSocketInterface::Private
{
public:
    enum InterfaceCallType {
        MethodResult = 0xc821ec7,
        MethodCall = 0xf40b2c9
    };

    QIODevice *device;
    QPointer<QObject> destObj;
    QByteArray socketBuffer;
    qint64 idPointer;

    QHash<qint64, std::function<void (QVariant)> > callbacks;
};

AsemanSocketInterface::AsemanSocketInterface(QIODevice *device, QObject *parent) :
    AsemanSocketInterface(this, device, parent)
{
    p = new Private;
    p->idPointer = 100000;
    p->device = device;

    connect(p->device, &QIODevice::readyRead, this, &AsemanSocketInterface::readyRead);
}

AsemanSocketInterface::AsemanSocketInterface(QObject *destObj, QIODevice *device, QObject *parent) :
    QObject(parent)
{
    p = new Private;
    p->idPointer = 100000;
    p->device = device;
    p->destObj = destObj;

    connect(p->device, &QIODevice::readyRead, this, &AsemanSocketInterface::readyRead);

}

void AsemanSocketInterface::readyRead()
{
    p->socketBuffer += p->device->readAll();

    while(!p->socketBuffer.isEmpty())
    {
        qint64 hardOperator = 0;
        QByteArray hardData;

        QBuffer buffer(&p->socketBuffer);
        buffer.open(QBuffer::ReadOnly);

        QDataStream hardStream(&buffer);
        hardStream.setVersion(QDataStream::Qt_5_6);
        hardStream >> hardOperator;
        hardStream >> hardData;

        if(hardStream.status() == QDataStream::ReadPastEnd)
            break;

        switch(hardOperator)
        {
        case AsemanSocketInterface::Private::MethodResult:
            result(hardData);
            break;

        case AsemanSocketInterface::Private::MethodCall:
            p->device->write( call(hardData) );
            break;
        }

        p->socketBuffer = p->socketBuffer.mid(buffer.pos());
    }
}

QByteArray AsemanSocketInterface::call(QByteArray data)
{
    qint64 uniqueId;
    QString method;
    QVariantList args;

    QDataStream inStream(data);
    inStream.setVersion(QDataStream::Qt_5_6);
    inStream >> uniqueId;
    inStream >> method;
    inStream >> args;

    while(args.length()<10)
        args << QVariant();

    QVariant var = call(p->destObj? p->destObj : this, method, Qt::DirectConnection, args.at(0), args.at(1), args.at(2), args.at(3), args.at(4), args.at(5), args.at(6), args.at(7), args.at(8), args.at(9));

    QByteArray hardData;
    QDataStream stream(&hardData, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_6);
    stream << uniqueId;
    stream << var;

    QByteArray res;
    QDataStream hardStream(&res, QIODevice::WriteOnly);
    hardStream.setVersion(QDataStream::Qt_5_6);
    hardStream << static_cast<qint64>(AsemanSocketInterface::Private::MethodResult);
    hardStream << hardData;

    return res;
}

void AsemanSocketInterface::result(QByteArray data)
{
    qint64 uniqueId;
    QVariant res;

    QDataStream inStream(data);
    inStream.setVersion(QDataStream::Qt_5_6);
    inStream >> uniqueId;
    inStream >> res;

    onResult(uniqueId, res);
    Q_EMIT result(uniqueId, res);
}

void AsemanSocketInterface::onResult(qint64 id, const QVariant &result)
{
    if(p->callbacks.contains(id))
        p->callbacks.take(id)(result);
}

qint64 AsemanSocketInterface::call(const QString &method, const QVariantList &args)
{
    p->idPointer++;

    QByteArray hardData;
    QDataStream stream(&hardData, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_6);
    stream << p->idPointer;
    stream << method;
    stream << args;

    QByteArray res;
    QDataStream hardStream(&res, QIODevice::WriteOnly);
    hardStream.setVersion(QDataStream::Qt_5_6);
    hardStream << static_cast<qint64>(AsemanSocketInterface::Private::MethodCall);
    hardStream << hardData;

    p->device->write(res);
    return p->idPointer;
}

void AsemanSocketInterface::call(const QString &method, const QVariantList &args, std::function<void (QVariant)> callback)
{
    qint64 id = call(method, args);
    p->callbacks[id] = callback;
}

QVariant AsemanSocketInterface::callSync(const QString &method, const QVariantList &args)
{
    QVariant result;
    if(!p->device->isOpen())
        return result;

    QPointer<QEventLoop> loop = new QEventLoop(this);
    call(method, args, [this, loop, &result](const QVariant &res){
        if(loop)
        {
            result = res;
            loop->exit();
        }
    });
    QTimer::singleShot(2000, loop, [this, loop](){
        if(!loop)
            return;

        loop->exit();
    });

    loop->exec();
    loop->deleteLater();
    return result;
}

void AsemanSocketInterface::callTimer(const QString &method, const QVariantList &args, std::function<void (QVariant)> callback)
{
    if(!p->device->isOpen())
    {
        callback( QVariant() );
        return;
    }

    QPointer<QTimer> timer = new QTimer(this);
    timer->setInterval(2000);
    timer->setSingleShot(true);
    timer->connect(timer.data(), &QTimer::timeout, this, [this, timer, callback](){
        timer->deleteLater();
        callback( QVariant() );
    });
    timer->start();

    call(method, args, [this, timer, callback](const QVariant &res){
        if(timer)
        {
            callback(res);
            delete timer;
        }
    });
}

QVariant AsemanSocketInterface::call(QObject *obj, const QString &member, Qt::ConnectionType ctype, const QVariant &v0, const QVariant &v1, const QVariant &v2, const QVariant &v3, const QVariant &v4, const QVariant &v5, const QVariant &v6, const QVariant &v7, const QVariant &v8, const QVariant &v9, bool *isVoid)
{
    const QMetaObject *meta_obj = obj->metaObject();
    QMetaMethod meta_method;
    for( int i=0; i<meta_obj->methodCount(); i++ )
    {
        QMetaMethod mtd = meta_obj->method(i);
        if( mtd.name() == member )
            meta_method = mtd;
    }
    if( !meta_method.isValid() )
        return QVariant();

    QList<QByteArray> param_types = meta_method.parameterTypes();
    QList<QByteArray> param_names = meta_method.parameterNames();

    QString ret_type = meta_method.typeName();
    QList< QPair<QString,QString> > m_args;
    for( int i=0 ; i<param_types.count() ; i++ )
        m_args << QPair<QString,QString>( param_types.at(i) , param_names.at(i) );

    QVariantList vals;
        vals << v0 << v1 << v2 << v3 << v4 << v5 << v6 << v7 << v8 << v9;

    QVariantList tr_vals;

    QList< QPair<QString,const void*> > args;
    for( int i=0 ; i<vals.count() ; i++ )
    {
        if( i<m_args.count() )
        {
            QString type = m_args.at(i).first;

            if( type != vals.at(i).typeName() )
            {
                if( vals[i].canConvert( QVariant::nameToType(type.toLatin1()) ) )
                    vals[i].convert( QVariant::nameToType(type.toLatin1()) );
            }

            args << QPair<QString,const void*>( type.toLatin1() , vals.at(i).data() );
            tr_vals << vals[i];
        }
        else
        {
            args << QPair<QString,const void*>( vals.at(i).typeName() , vals.at(i).data() );
        }
    }

    int type = QMetaType::type(ret_type.toLatin1());
    if(isVoid) *isVoid = (type == QMetaType::Void);
    void *res = QMetaType::create(type);
    bool is_pointer = ret_type.contains('*');

    bool done;
    switch( static_cast<int>(ctype) )
    {
    case Qt::QueuedConnection:
        done = QMetaObject::invokeMethod( obj , member.toLatin1() , Qt::QueuedConnection ,
                                  QGenericArgument( args.at(0).first.toLatin1() , args.at(0).second ) ,
                                  QGenericArgument( args.at(1).first.toLatin1() , args.at(1).second ) ,
                                  QGenericArgument( args.at(2).first.toLatin1() , args.at(2).second ) ,
                                  QGenericArgument( args.at(3).first.toLatin1() , args.at(3).second ) ,
                                  QGenericArgument( args.at(4).first.toLatin1() , args.at(4).second ) ,
                                  QGenericArgument( args.at(5).first.toLatin1() , args.at(5).second ) ,
                                  QGenericArgument( args.at(6).first.toLatin1() , args.at(6).second ) ,
                                  QGenericArgument( args.at(7).first.toLatin1() , args.at(7).second ) ,
                                  QGenericArgument( args.at(8).first.toLatin1() , args.at(8).second ) ,
                                  QGenericArgument( args.at(9).first.toLatin1() , args.at(9).second ) );
        return QVariant();
        break;

    default:
        done = QMetaObject::invokeMethod( obj , member.toLatin1() , ctype, QGenericReturnArgument( ret_type.toLatin1() , (is_pointer)? &res : res ) ,
                                  QGenericArgument( args.at(0).first.toLatin1() , args.at(0).second ) ,
                                  QGenericArgument( args.at(1).first.toLatin1() , args.at(1).second ) ,
                                  QGenericArgument( args.at(2).first.toLatin1() , args.at(2).second ) ,
                                  QGenericArgument( args.at(3).first.toLatin1() , args.at(3).second ) ,
                                  QGenericArgument( args.at(4).first.toLatin1() , args.at(4).second ) ,
                                  QGenericArgument( args.at(5).first.toLatin1() , args.at(5).second ) ,
                                  QGenericArgument( args.at(6).first.toLatin1() , args.at(6).second ) ,
                                  QGenericArgument( args.at(7).first.toLatin1() , args.at(7).second ) ,
                                  QGenericArgument( args.at(8).first.toLatin1() , args.at(8).second ) ,
                                  QGenericArgument( args.at(9).first.toLatin1() , args.at(9).second ) );
        break;
    }

    QVariant result;
    if( !done )
    {
        QMetaType::destroy(type, res);
        return result;
    }

    if( type == QMetaType::Void )
        result = QVariant();
    else
    if( is_pointer )
        result = QVariant( type , &res );
    else
        result = QVariant( type , res );

    QMetaType::destroy(type, res);
    if( type == QMetaType::type("QVariant") )
        return result.value<QVariant>();
    else
        return result;
}

AsemanSocketInterface::~AsemanSocketInterface()
{
    delete p;
}
