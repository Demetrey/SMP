/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playbackcontroller.h"

PlaybackController *PlaybackController::playbackController = nullptr;

PlaybackController::PlaybackController(QObject *parent) : QObject(parent) {
    stream = 0;
    playbackController = this;

    connect(this, &PlaybackController::endOfFile, [this]() {
        onEndOfFile();
    });
}

void PlaybackController::setStream(HSTREAM stream) {
    this->stream = stream;
}

bool PlaybackController::play() {
    if (BASS_ChannelIsActive(stream) == BASS_ACTIVE_STOPPED)
        BASS_ChannelSetSync(stream, BASS_SYNC_END, 0, syncEnd, 0);
    return BASS_ChannelPlay(stream, false);
}

bool PlaybackController::pause() {
    if (BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING)
        return BASS_ChannelPause(stream);
    return false;
}

bool PlaybackController::stop() {
    return BASS_ChannelStop(stream);
}

/**
 * @brief Looping
 *
 * Setting or clearing the loop flag
 */
void PlaybackController::looping() {
    if (BASS_ChannelFlags(stream, 0, 0)&BASS_SAMPLE_LOOP)
        BASS_ChannelFlags(stream, 0, BASS_SAMPLE_LOOP);
    else
        BASS_ChannelFlags(stream, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
}
/**
 * @brief Set Position
 *
 * Set the playback position (rewind) to the specified value in ms
 *
 * @param position Position in ms
 * @return true is success, false is failure
 */
bool PlaybackController::setPosition(int position) {
    if (position < 0 || position > getCompositionTime())
        return false;
    return BASS_ChannelSetPosition(stream,
                                   BASS_ChannelSeconds2Bytes(stream,
                                         static_cast<double>(position / 1000.)),
                                   BASS_POS_BYTE);
}

/**
 * @brief Current composition time
 * @return Time in milliseconds
 */
int PlaybackController::getCompositionTime() {
    return static_cast<int>(1000 *
                            BASS_ChannelBytes2Seconds(stream,
                                                      BASS_ChannelGetLength(stream,
                                                                            BASS_POS_BYTE)));
}

/**
 * @brief Current playback position in time
 * @return Time in milliseconds
 */
int PlaybackController::getCurrentTime() {
    return static_cast<int>(1000 *
                            BASS_ChannelBytes2Seconds(stream,
                                                      BASS_ChannelGetPosition(stream,
                                                                              BASS_POS_BYTE)));
}

void PlaybackController::onEndOfFile() {
    qDebug() << "End Of File";
    emit eof();
}

/**
 * End-of-file playback signal handler (for BASS AL)
 * (BASS_ChannelSetSync proc)
 */
void PlaybackController::syncEnd(HSYNC handle, DWORD channel,
                                 DWORD data, void *user) {
    emit playbackController->endOfFile();
}
