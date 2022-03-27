/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU Lesser General Public License (LGPL).
 */

#include "initializer.h"

Initializer::Initializer(QObject *parent) : QObject(parent) {
    stream = 0;
}

Initializer::~Initializer() {
    BASS_Free();
}

/**
 * Initializes an output device
 * @brief Initializer::initDevice
 * @param device - output device number (-1 - default)
 * @param freq - output sample rate, Hz (44100 - default)
 * @return true - successful application; false - error
 */
bool Initializer::initDevice(int device, int freq) {
    return BASS_Init(device, freq, BASS_DEVICE_FREQ, 0, NULL);
}

/**
 * Specifying an output device
 * @brief Initializer::setDevice
 * @param device - output device number
 */
void Initializer::setDevice(int device) {
    BASS_SetDevice(device);
    if (BASS_ChannelIsActive(stream) != BASS_ACTIVE_STOPPED)
        BASS_ChannelSetDevice(stream, device);
}

/**
 * File playback initialization
 * @brief Initializer::initFile
 * @param fileWay - path to file
 */
void Initializer::initFile(const char *fileWay) {
    stream = BASS_StreamCreateFile(false, fileWay, 0, 0, 0);
}

/**
 * Initiating playback by URL
 * @brief Initializer::initUrl
 * @param url - url for playback (HTTP, HTTPS, FTP protocols)
 */
void Initializer::initUrl(const char *url)
{
    stream = BASS_StreamCreateURL(url, 0, BASS_STREAM_STATUS, 0, 0);
}

/**
 * Force release of a playback stream
 * @brief Initializer::freeStream
 */
void Initializer::freeStream() {
    if (BASS_ChannelIsActive(stream) != BASS_ACTIVE_STOPPED)
        BASS_ChannelStop(stream);
    BASS_StreamFree(stream);
    stream = 0;
}

/**
 * Search for connected output devices for further use
 * @brief Initializer::getDeviceInfo
 * @return QMap of connected devices with name and number
 */
QMap<int, QString> Initializer::getDevicesInfo() {
    BASS_DEVICEINFO info;
    QMap<int, QString> devices;
    for (int device = 1; BASS_GetDeviceInfo(device, &info); device++) {
        if (info.flags & BASS_DEVICE_ENABLED) {
            devices.insert(device, QString::fromLocal8Bit(info.name));
            qDebug() << device << " ... " << QString::fromLocal8Bit(info.name);
        }
    }
    return devices;
}

HSTREAM Initializer::getStream() {
    return stream;
}
