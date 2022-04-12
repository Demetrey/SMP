/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playbackparameters.h"

PlaybackParameters::PlaybackParameters(QObject *parent) : QObject(parent) {
    stream = 0;
    reverb = 0;
}

void PlaybackParameters::setStream(HSTREAM stream) {
    this->stream = stream;
    initReverb();
    initEq();
}

/**
 * Initializing the Initial Values ​​of the Equalizer Parameters
 * This method must be called BEFORE setStream
 * @brief PlaybackParameters::initEqCenters
 * @param path - Path to the centers file
 * @param values - Initial equalizer values ​​(if not - nullptr)
 * @param freq - Sampling frequency
 */
void PlaybackParameters::initEqCenters(QString path, QList<float> *values, float freq) {
    QVector<int> centers = XmlLoader::loadCenters(path);
    correctCenters(centers, freq);
    qDebug() << centers;
    // Validation of values
    bool checkVal = true;
    if (!values)
        checkVal = false;
    else if ((*values).size() != centers.size())
        checkVal = false;

    if (centers.size() > 0) {
        for (int i = 0; i < centers.size(); i++) {
            eqValues.insert(centers.at(i), checkVal ? (*values).at(i) : 0.0);
        }
    }
    qDebug() << "values" << eqValues;
}

/**
 * Setting the volume level
 * @brief PlaybackParameters::setVolume
 * @param value - Volume level [0%; 100%]
 * @return true - success; false - failure
 */
bool PlaybackParameters::setVolume(int value) {
    if (value > 100 || value < 0)
        return false;
    return BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, value / 100.0);
}

/**
 * Setting the playback stream reverb parameter
 * @brief PlaybackParameters::setReverb
 * @param value - Reverb parameter [0%; 100%]
 * @return true - success; false - failure
 */
bool PlaybackParameters::setReverb(int value) {
    if (value > 100 || value < 0)
        return false;
    float val = 20.0 - 20.0 * value / 100.0;
    BASS_DX8_REVERB p;
    BASS_FXGetParameters(reverb, &p);
    p.fReverbMix = val < 20 ? log(1 - val / 20.0) * 20 : -96;
    return BASS_FXSetParameters(reverb, &p);
}

/**
 * Setting the sound balance
 * @brief PlaybackParameters::setBalance
 * @param value - Sound balance [Left; Right] -> [-100%; 100%]
 * @return true - success; false - failure
 */
bool PlaybackParameters::setBalance(int value) {
    if (value > 100 || value < -100)
        return false;
    return BASS_ChannelSetAttribute(stream, BASS_ATTRIB_PAN, value / 100.0);
}

/**
 * Setting a value for the current center
 * @brief PlaybackParameters::setEqValue
 * @param center - Current frequency center
 * @param value - New value
 * @return true - success; false - failure
 */
bool PlaybackParameters::setEqValue(int center, float value) {
    if (eqHandlers.contains(center) && eqValues.contains(center)) {
        BASS_DX8_PARAMEQ p;
        BASS_FXGetParameters(eqHandlers.value(center), &p);
        p.fGain = value;
        if (BASS_FXSetParameters(eqHandlers.value(center), &p)) {
            eqValues[center] = value;
            return true;
        }
    }
    return false;
}

void PlaybackParameters::initReverb() {
    reverb = BASS_ChannelSetFX(stream, BASS_FX_DX8_REVERB, 0);
    setReverb(0);
}

bool PlaybackParameters::initEq() {
    QList<int> keys = eqValues.keys();
    for (auto key : qAsConst(keys)) {
        if (!initHandlers(key, eqValues.value(key))) {
            qDebug() << "Error init handlers" << key;
            qDebug() << "Error" << BASS_ErrorGetCode();
            return false;
        }
    }
    qDebug() << eqHandlers;
    return true;
}

bool PlaybackParameters::initHandlers(int center, float value) {
    BASS_DX8_PARAMEQ p;
    p.fGain = value;
    p.fBandwidth = 1.0;
    p.fCenter = center;
    eqHandlers.insert(center, BASS_ChannelSetFX(stream, BASS_FX_DX8_PARAMEQ, 1));
    return BASS_FXSetParameters(eqHandlers.value(center), &p);
}

/**
 * Checking the correct loading of the equalizer parameters
 * On Windows, the frequencies of the centers should not go
 * beyond the range [80; freq / 3]
 * On other systems, the frequency centers should not go
 * beyond the range [0; freq / 2]
 * @brief PlaybackParameters::correctCenters
 * @param centers - frequency centers
 * @param freq - sampling frequency
 */
void PlaybackParameters::correctCenters(QVector<int> &centers, int freq) {
#ifdef Q_OS_WINDOWS
    for (int i = 0; i < centers.size(); i++) {
        if (centers.at(i) < 80 || centers.at(i) > freq / 3) {
            centers.removeAt(i);
            i--;
        }
    }
#else
    for (int i = 0; i < centers.size(); i++) {
        if (centers.at(i) < 0 || centers.at(i) > freq / 2) {
            centers.removeAt(i);
            i--;
        }
    }
#endif
}
