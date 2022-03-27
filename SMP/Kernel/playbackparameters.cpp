/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU Lesser General Public License (LGPL).
 */

#include "playbackparameters.h"

PlaybackParameters::PlaybackParameters(QObject *parent) : QObject(parent) {
    stream = 0;
    reverb = 0;
}

void PlaybackParameters::setStream(HSTREAM stream) {
    this->stream = stream;
    initReverb();
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

void PlaybackParameters::initReverb() {
    reverb = BASS_ChannelSetFX(stream, BASS_FX_DX8_REVERB, 0);
    setReverb(0);
}
