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

#include "asemanaudioencodersettings.h"

#include <QAudioEncoderSettings>

class AsemanAudioEncoderSettingsPrivate
{
public:
    QAudioEncoderSettings settings;
};

AsemanAudioEncoderSettings::AsemanAudioEncoderSettings(QObject *parent) :
    QObject(parent)
{
    p = new AsemanAudioEncoderSettingsPrivate;
}

int AsemanAudioEncoderSettings::bitRate() const
{
    return p->settings.bitRate();
}

void AsemanAudioEncoderSettings::setBitRate(int rate)
{
    if(p->settings.bitRate() == rate)
        return;

    p->settings.setBitRate(rate);
    Q_EMIT bitRateChanged();
}

int AsemanAudioEncoderSettings::channelCount() const
{
    return p->settings.channelCount();
}

void AsemanAudioEncoderSettings::setChannelCount(int channels)
{
    if(p->settings.channelCount() == channels)
        return;

    p->settings.setChannelCount(channels);
    Q_EMIT channelCountChanged();
}

QString AsemanAudioEncoderSettings::codec() const
{
    return p->settings.codec();
}

void AsemanAudioEncoderSettings::setCodec(const QString &cdc)
{
    if(p->settings.codec() == cdc)
        return;

    p->settings.setCodec(cdc);
    Q_EMIT codecChanged();
}

int AsemanAudioEncoderSettings::encodingMode() const
{
    return p->settings.encodingMode();
}

void AsemanAudioEncoderSettings::setEncodingMode(int mode)
{
    if(p->settings.encodingMode() == mode)
        return;

    p->settings.setEncodingMode(static_cast<QMultimedia::EncodingMode>(mode));
    Q_EMIT encodingModeChanged();
}

QVariantMap AsemanAudioEncoderSettings::encodingOptions() const
{
    return p->settings.encodingOptions();
}

void AsemanAudioEncoderSettings::setEncodingOptions(const QVariantMap &options)
{
    if(p->settings.encodingOptions() == options)
        return;

    p->settings.setEncodingOptions(options);
    Q_EMIT encodingOptionsChanged();
}

int AsemanAudioEncoderSettings::quality() const
{
    return p->settings.quality();
}

void AsemanAudioEncoderSettings::setQuality(int quality)
{
    if(p->settings.quality() == quality)
        return;

    p->settings.setQuality(static_cast<QMultimedia::EncodingQuality>(quality));
    Q_EMIT qualityChanged();
}

int AsemanAudioEncoderSettings::sampleRate() const
{
    return p->settings.sampleRate();
}

void AsemanAudioEncoderSettings::setSampleRate(int rate)
{
    if(p->settings.sampleRate() == rate)
        return;

    p->settings.setSampleRate(rate);
    Q_EMIT sampleRateChanged();
}

QAudioEncoderSettings AsemanAudioEncoderSettings::exportSettings() const
{
    return p->settings;
}

AsemanAudioEncoderSettings::~AsemanAudioEncoderSettings()
{
    delete p;
}
