/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playbackparameters.h"

PlaybackParameters::PlaybackParameters(QObject *parent) : QObject(parent) {
    stream = 0;
    reverb = 0;
    currentVolume = 100;
    currentBalance = 0;
    currentReverb = -1;
}

void PlaybackParameters::setStream(HSTREAM stream) {
    this->stream = stream;
    initReverb();
    initEq();
    setVolume(currentVolume);
    setReverb(currentReverb);
    setBalance(currentBalance);
}

/**
 * @brief Initializing EQ Centers
 *
 * Initializing the Initial Values ​​of the Equalizer Parameters
 * This method must be called BEFORE setStream
 *
 * @param path - Path to the centers file
 * @param values - Initial equalizer values ​​(if not - nullptr)
 * @param freq - Sampling frequency
 */
void PlaybackParameters::initEqCenters(QString path, QList<float> *values, float freq) {
    QVector<int> centers = XmlLoader::loadCenters(path);
    correctCenters(centers, freq);
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
}

/**
 * @brief Setting the volume level
 * @param value - Volume level [0%; 100%]
 * @return true - success; false - failure
 */
bool PlaybackParameters::setVolume(int value) {
    if (value > 100 || value < 0 || value == currentVolume)
        return false;
    currentVolume = value;
    return BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, value / 100.0);
}

/**
 * @brief Setting the playback stream reverb parameter
 * @param value - Reverb parameter [0%; 100%]
 * @return true - success; false - failure
 */
bool PlaybackParameters::setReverb(int value) {
    if (value > 100 || value < 0 || value == currentReverb)
        return false;
    currentReverb = value;
    float val = 20.0 - 20.0 * value / 100.0;
    BASS_DX8_REVERB p;
    BASS_FXGetParameters(reverb, &p);
    p.fReverbMix = val < 20 ? log(1 - val / 20.0) * 20 : -96;
    return BASS_FXSetParameters(reverb, &p);
}

/**
 * @brief Setting the sound balance
 * @param value - Sound balance [Left; Right] -> [-100%; 100%]
 * @return true - success; false - failure
 */
bool PlaybackParameters::setBalance(int value) {
    if (value > 100 || value < -100 || value == currentBalance)
        return false;
    currentBalance = value;
    return BASS_ChannelSetAttribute(stream, BASS_ATTRIB_PAN, value / 100.0);
}

/**
 * @brief Setting a value for the current center
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

int PlaybackParameters::getCurrentVolume() {
    return currentVolume;
}

int PlaybackParameters::getCurretReverb() {
    return currentReverb;
}

int PlaybackParameters::getCurrentBalance() {
    return currentBalance;
}

QMap<int, float> PlaybackParameters::getEqValues() {
    return eqValues;
}

void PlaybackParameters::initReverb() {
    reverb = BASS_ChannelSetFX(stream, BASS_FX_DX8_REVERB, 0);
    setReverb(0);
}

bool PlaybackParameters::initEq() {
    QList<int> keys = eqValues.keys();
    for (auto key : qAsConst(keys)) {
        if (!initHandlers(key, eqValues.value(key))) {
            return false;
        }
    }
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
 * @brief Center correction
 *
 * Checking the correct loading of the equalizer parameters
 * On Windows, the frequencies of the centers should not go
 * beyond the range [80; freq / 3]
 * On other systems, the frequency centers should not go
 * beyond the range [0; freq / 2]
 *
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
