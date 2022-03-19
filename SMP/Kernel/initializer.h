/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU Lesser General Public License (LGPL).
 */

#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QMap>
#include <QDebug>
#include <bass.h>

class Initializer
{
public:
    Initializer();
    ~Initializer();
    bool initDevice(int device = -1, int freq = 44100);
    void setDevice(int device);
    void initFile(const char *fileway);
    void initUrl(const char *url);
    QMap<int, QString> getDevicesInfo();
    HSTREAM* getStream();

private:
    HSTREAM stream;
};

#endif // INITIALIZER_H
