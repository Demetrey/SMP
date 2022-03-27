/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU Lesser General Public License (LGPL).
 */

#ifndef PLAYBACKPARAMETERS_H
#define PLAYBACKPARAMETERS_H

#include <QObject>
#include <QList>
#include <QMap>
#include <cmath>
#include <bass.h>
#include "readers/xmlloader.h"

class PlaybackParameters : public QObject
{
    Q_OBJECT
public:
    explicit PlaybackParameters(QObject *parent = nullptr);
    void setStream(HSTREAM stream);
    bool setVolume(int value);
    bool setReverb(int value);
    bool setBalance(int value);

private:
    HSTREAM stream;
    HFX reverb;

    void initReverb();
};

#endif // PLAYBACKPARAMETERS_H
