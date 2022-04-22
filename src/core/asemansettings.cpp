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

#define PROPERTY_KEY(PROPERTY) QString(p->caregory.isEmpty()? QString(PROPERTY) : p->caregory + QStringLiteral("/") + QString(PROPERTY))

#include "asemansettings.h"

#include <QMetaObject>
#include <QMetaProperty>
#include <QDir>
#include <QSettings>
#include <QFileInfo>
#include <QDebug>

class AsemanSettingsPrivate
{
public:
    QHash<QByteArray, QByteArray> signalsProperties;
    QSettings *settings;
    QString caregory;
    QString source;
};

AsemanSettings::AsemanSettings(QObject *parent) : QObject(parent)
{
    p = new AsemanSettingsPrivate;
    p->settings = 0;

    initProperties();
}

void AsemanSettings::setCategory(const QString &category)
{
    if(p->caregory == category)
        return;

    p->caregory = category;
    initProperties();
    Q_EMIT categoryChanged();
}

QString AsemanSettings::category() const
{
    return p->caregory;
}

void AsemanSettings::setSource(const QString &source)
{
    if(p->source == source)
        return;

    p->source = source;
    if(p->settings)
        delete p->settings;

    p->settings = 0;
    if(!p->source.isEmpty())
    {
        QDir().mkpath(QFileInfo(p->source).dir().path());
        p->settings = new QSettings(p->source, QSettings::IniFormat, this);
        initProperties();
    }

    Q_EMIT sourceChanged();
}

QString AsemanSettings::source() const
{
    return p->source;
}

void AsemanSettings::setValue(const QString &key, const QVariant &value)
{
    if(!p->settings)
        return;

    p->settings->setValue(PROPERTY_KEY(key), value);
    Q_EMIT valueChanged();
}

QVariant AsemanSettings::value(const QString &key, const QVariant &defaultValue)
{
    if(!p->settings)
        return QVariant();

    return p->settings->value(PROPERTY_KEY(key), defaultValue);
}

void AsemanSettings::remove(const QString &key)
{
    if(!p->settings)
        return;
    p->settings->remove(PROPERTY_KEY(key));
}

QStringList AsemanSettings::keys() const
{
    QStringList result;
    if(!p->settings)
        return result;

    p->settings->beginGroup(p->caregory);
    result = p->settings->childKeys();
    p->settings->endGroup();
    return result;
}

void AsemanSettings::sync()
{
    if(!p->settings)
        return;

    p->settings->sync();
    initProperties();
}

void AsemanSettings::propertyChanged()
{
    if(sender() != this)
        return;

    const int signalIndex = senderSignalIndex();
    if(signalIndex == -1)
        return;

    QMetaMethod signalObj = metaObject()->method(signalIndex);
    const QByteArray &propertyName = p->signalsProperties.value(signalObj.methodSignature());
    const QVariant &value = property(propertyName);
    if(p->settings)
        p->settings->setValue( PROPERTY_KEY(QString::fromUtf8(propertyName)), value);

    Q_EMIT valueChanged();
}

void AsemanSettings::initProperties()
{
    if(!p->settings || p->caregory.isEmpty())
        return;

    for (const auto &signalSign: p->signalsProperties.keys())
        disconnect(this, QByteArray(QByteArray::number(QSIGNAL_CODE)+signalSign),
                   this, SLOT(propertyChanged()));

    p->signalsProperties.clear();

    const QMetaObject *meta = metaObject();
    for(int i=0; i<meta->propertyCount(); i++)
    {
        QMetaProperty property = meta->property(i);
        const QByteArray &propertyName = property.name();
        const QByteArray &signalSign = property.notifySignal().methodSignature();
        if(propertyName == "source" || propertyName == "category" || propertyName == "objectName")
            continue;

        p->signalsProperties[signalSign] = propertyName;
        if(p->settings)
        {
            QVariant value = p->settings->value(PROPERTY_KEY( QString::fromUtf8(propertyName) ));
            if(value != QObject::property(propertyName) && value.isValid())
                setProperty(propertyName, value);
        }

        connect(this, QByteArray(QByteArray::number(QSIGNAL_CODE)+signalSign),
                this, SLOT(propertyChanged()));
    }
}

AsemanSettings::~AsemanSettings()
{
    delete p;
}
