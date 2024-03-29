/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef PLAYBACKCONTROLLER_H
#define PLAYBACKCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <bass.h>

/**
 * @brief The PlaybackController class
 * Класс управления воспроизведением.
 * Предоставляет методы для управления воспроизведением.
 * Playback control class.
 * Provides methods to control playback.
 */
class PlaybackController : public QObject
{
    Q_OBJECT
public:
    explicit PlaybackController(QObject *parent = nullptr);
    void setStream(HSTREAM stream);
    bool play();
    bool pause();
    bool stop();
    void looping();
    bool setPosition(int position);
    int getCompositionTime();
    int getCurrentTime();

signals:
    void eof();         // Sends a signal to an external slot
    void endOfFile();   // Sends a signal to an internal slot

private slots:
    void onEndOfFile();    // Responds to internal signals

private:
    HSTREAM stream;
    // Memory specificity to send a signal from a static method
    static PlaybackController *playbackController;

    static void CALLBACK syncEnd(HSYNC handle, DWORD channel,
                                 DWORD data, void *user);  // Generate signal
};

#endif // PLAYBACKCONTROLLER_H
