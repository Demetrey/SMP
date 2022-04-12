/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
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
    void initEqCenters(QString path, QList<float> *values = nullptr, float freq = 44100);
    bool setVolume(int value);
    bool setReverb(int value);
    bool setBalance(int value);
    bool setEqValue(int center, float value);

private:
    HSTREAM stream;
    HFX reverb;
    QMap<int, float> eqValues;
    QMap<int, HFX> eqHandlers;

    void initReverb();
    bool initEq();
    bool initHandlers(int center, float value);
    void correctCenters(QVector<int> &centers, int freq);
};

#endif // PLAYBACKPARAMETERS_H
