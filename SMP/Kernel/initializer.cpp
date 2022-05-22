/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "initializer.h"

Initializer::Initializer(QObject *parent) : QObject(parent) {
    stream = 0;
}

Initializer::~Initializer() {
    freeDevices();
}

/**
 * @brief Device initialization
 * Инициализация устройств воспроизведения
 * Initializes an output device
 *
 * @param device - output device number (-1 - default)
 * @param freq - output sample rate, Hz (44100 - default)
 * @return true - successful application; false - error
 */
bool Initializer::initDevice(int device, int freq) {
    bool res = false;
    if (!(res = BASS_Init(device, freq, BASS_DEVICE_FREQ, 0, NULL)) &&
            BASS_ErrorGetCode() == BASS_ERROR_ALREADY && device != -1) {
        // reinitializing a non-default playback device
        res = BASS_Init(device, freq, BASS_DEVICE_FREQ | BASS_DEVICE_REINIT, 0, NULL);
    }
    return res;
}

/**
 * @brief Device activation
 * Смена устройства воспроизведения
 * Specifying an output device
 *
 * @param device - output device number
 */
void Initializer::setDevice(int device) {
    BASS_SetDevice(device);
    if (BASS_ChannelIsActive(stream) != BASS_ACTIVE_STOPPED)
        BASS_ChannelSetDevice(stream, device);
}

/**
 * @brief File initialization
 * Установка воспроизведения файла
 * File playback initialization
 *
 * @param fileWay - path to file
 */
void Initializer::initFile(const char *fileWay) {
    stream = BASS_StreamCreateFile(false, fileWay, 0, 0, 0);
}

/**
 * @brief URL initialization
 * Установка воспроизведения URL
 * Initiating playback by URL
 *
 * @param url - url for playback (HTTP, HTTPS, FTP protocols)
 */
void Initializer::initUrl(const char *url) {
    stream = BASS_StreamCreateURL(url, 0, BASS_STREAM_STATUS, 0, 0);
}

/**
 * @brief Initializer::freeStream
 * Освобождение потока воспроизведения
 * Force release of a playback stream
 */
void Initializer::freeStream() {
    if (BASS_ChannelIsActive(stream) != BASS_ACTIVE_STOPPED)
        BASS_ChannelStop(stream);
    BASS_StreamFree(stream);
    stream = 0;
}

/**
 * @brief Device information
 * Получение списка доступных устройств воспроизведения
 * Search for connected output devices for further use
 *
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

/**
 * @brief Channel sampling rate
 * @return Sampling frequency (Hz)
 */
float Initializer::getChannelFreq() {
    BASS_CHANNELINFO info;
    BASS_ChannelGetInfo(stream, &info);
    return info.freq;
}

/**
 * @brief Releasing resources
 * Освободление ресурсов активных устройств воспроизведения
 * Releasing resources for active playback devices
 */
void Initializer::freeDevices() {
    QList<int> devices = getDevicesInfo().keys();
    for (int device : qAsConst(devices)) {
        if (BASS_SetDevice(device)) {
            BASS_Free();
        }
    }
}
