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

#ifndef ASEMANAUDIOENCODERSETTINGS_H
#define ASEMANAUDIOENCODERSETTINGS_H

#include <QObject>
#include <QVariant>
#include <QMultimedia>

#include "asemanmultimedia_global.h"

class QAudioEncoderSettings;
class AsemanAudioEncoderSettingsPrivate;
class LIBQTASEMAN_MULTIMEDIA_EXPORT AsemanAudioEncoderSettings : public QObject
{
    Q_OBJECT
    Q_ENUMS(EncodingQuality)
    Q_ENUMS(EncodingMode)

    Q_PROPERTY(int bitRate READ bitRate WRITE setBitRate NOTIFY bitRateChanged)
    Q_PROPERTY(int channelCount READ channelCount WRITE setChannelCount NOTIFY channelCountChanged)
    Q_PROPERTY(QString codec READ codec WRITE setCodec NOTIFY codecChanged)
    Q_PROPERTY(int encodingMode READ encodingMode WRITE setEncodingMode NOTIFY encodingModeChanged)
    Q_PROPERTY(QVariantMap encodingOptions READ encodingOptions WRITE setEncodingOptions NOTIFY encodingOptionsChanged)
    Q_PROPERTY(int quality READ quality WRITE setQuality NOTIFY qualityChanged)
    Q_PROPERTY(int sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)

public:
    enum EncodingQuality
    {
        VeryLowQuality = QMultimedia::VeryLowQuality,
        LowQuality = QMultimedia::LowQuality,
        NormalQuality = QMultimedia::NormalQuality,
        HighQuality = QMultimedia::HighQuality,
        VeryHighQuality = QMultimedia::VeryHighQuality
    };

    enum EncodingMode
    {
        ConstantQualityEncoding = QMultimedia::ConstantQualityEncoding,
        ConstantBitRateEncoding = QMultimedia::ConstantBitRateEncoding,
        AverageBitRateEncoding = QMultimedia::AverageBitRateEncoding,
        TwoPassEncoding = QMultimedia::TwoPassEncoding
    };

    AsemanAudioEncoderSettings(QObject *parent = 0);
    virtual ~AsemanAudioEncoderSettings();

    int bitRate() const;
    void setBitRate(int rate);

    int channelCount() const;
    void setChannelCount(int channels);

    QString codec() const;
    void setCodec(const QString & codec);

    int encodingMode() const;
    void setEncodingMode(int mode);

    QVariantMap encodingOptions() const;
    void setEncodingOptions(const QVariantMap & options);

    int quality() const;
    void setQuality(int quality);

    int sampleRate() const;
    void setSampleRate(int rate);

    QAudioEncoderSettings exportSettings() const;

Q_SIGNALS:
    void bitRateChanged();
    void channelCountChanged();
    void codecChanged();
    void encodingModeChanged();
    void encodingOptionsChanged();
    void qualityChanged();
    void sampleRateChanged();

private:
    AsemanAudioEncoderSettingsPrivate *p;
};

#endif // ASEMANAUDIOENCODERSETTINGS_H
