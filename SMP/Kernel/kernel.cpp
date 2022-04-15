/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "kernel.h"

Kernel::Kernel(QObject *parent) : QObject(parent) {
    m_kernelState = KernelState::State::Stop;
    initializer = new Initializer(this);
    controller = new PlaybackController(this);
    parameters = new PlaybackParameters(this);
}

Kernel::~Kernel() {
    BASS_PluginFree(0); // Free all plugins
    delete parameters;
    delete controller;
    delete initializer;
}

/**
 * @brief Loading plugins
 *
 * Loading plugins specified in XML
 *
 * @return List of unloaded plugins
 */
QList<QString> Kernel::loadPlugins() {
    QList<QString> errorLoad;
    QString path;
    QString ext;
    QStringList pluginNames = XmlLoader::loadPlugFiles(":/XML/pluginFiles.xml");

#ifdef Q_OS_ANDROID
    path = "./";
#else
    path = "./plugins/";
#endif
#ifdef Q_OS_WINDOWS
        ext = ".dll";
#else
        ext = ".so";
        for (int i = 0; i < pluginNames.size(); i++) {
            pluginNames[i] = "lib" + pluginNames[i];
        }
#endif

    for (const auto &file : qAsConst(pluginNames)) {
        HPLUGIN pluginHandler = BASS_PluginLoad((path + file + ext)
                                                .toLocal8Bit().data(), 0);
        if (!BASS_PluginEnable(pluginHandler, 1)) {
            errorLoad.append(file);
        }
    }
    return errorLoad;
}

/**
 * @brief Initializing the playback device
 *
 * Search for a device in the list of available devices
 * and initialization if found
 *
 * @param device - Playback device index
 * @param freq - Sample rate of playback device
 */
void Kernel::initDevice(int device, int freq) {
    QMap<int, QString> devices = initializer->getDevicesInfo();
    if (devices.contains(device) || device == -1) {
        initializer->initDevice(device, freq);
        if (BASS_ErrorGetCode() == BASS_ERROR_ALREADY
                || BASS_ErrorGetCode() == BASS_OK) {
            initializer->setDevice(device);
            return;
        }
    }
    throw "Can't initialize device";
}

/**
 * @brief Playing a file or stream
 *
 * If the stream is already being played and the passed value of the path is
 * empty or matches what is being played now, we continue playing.
 * Otherwise, if the path is new or the stream is not playing, we play a
 * new file / stream.
 *
 * @param name File path or URL. Blank to continue playing
 * @param isFile true - file, false - URL
 */
void Kernel::play(const QString path, bool isFile) {
    if (initializer->getStream()) {
        BASS_CHANNELINFO info;
        BASS_ChannelGetInfo(initializer->getStream(), &info);
        // If there was a pause - play
        if (!path.length() || info.filename == path.toLocal8Bit()) {
            if (BASS_ChannelIsActive(initializer->getStream()) == BASS_ACTIVE_PAUSED) {
                if (controller->play()) // already playing
                    setKernelState(KernelState::State::Play);
            }
            return;
        }
        // If the new file/stream
        else {
            initializer->freeStream();
            setKernelState(KernelState::State::Stop);
        }
    }
    // New file/stream
    if (isFile) {
        initializer->initFile(path.toLocal8Bit().data());
    }
    else {
        initializer->initUrl(path.toLocal8Bit().data());
    }
    controller->setStream(initializer->getStream());
    parameters->setStream(initializer->getStream());
    if (controller->play()) {
        setKernelState(KernelState::State::Play);
    }
}

/**
 * @brief Pause
 *
 * If the playback stream is initialized, pause
 */
void Kernel::pause() {
    if (initializer->getStream() && controller->pause())
        setKernelState(KernelState::State::Pause);

}

/**
 * @brief Stop
 *
 * If the playback stream is initialized, stop
 */
void Kernel::stop() {
    if (initializer->getStream() && controller->stop())
        setKernelState(KernelState::State::Stop);
}

void Kernel::setVolume(int value) {

}

void Kernel::setReverb(int value) {

}

void Kernel::setBalance(int value) {

}

void Kernel::setTime(int value) {

}

const KernelState::State &Kernel::kernelState() const
{
    return m_kernelState;
}

void Kernel::setKernelState(const KernelState::State &newKernelState)
{
    if (m_kernelState == newKernelState)
        return;
    m_kernelState = newKernelState;
    emit kernelStateChanged();
}
