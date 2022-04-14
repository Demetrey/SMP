/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "kernel.h"

Kernel::Kernel(QObject *parent) : QObject(parent) {
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
 * Loading plugins
 * @brief Kernel::loadPlugins
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

void Kernel::initDevice(int device, int freq) {
    initializer->initDevice(device, freq);
    if (BASS_ErrorGetCode() != BASS_ERROR_ALREADY && BASS_ErrorGetCode() != BASS_OK)
        throw "Can't initialize device";
    initializer->setDevice(device);
}

/**
 * Playing a file or stream.
 * If the stream is already being played and the passed value of the path is
 * empty or matches what is being played now, we continue playing.
 * Otherwise, if the path is new or the stream is not playing, we play a
 * new file / stream.
 * @brief Kernel::play
 * @param name File path or URL. Blank to continue playing
 * @param isFile true - file, false - URL
 */
void Kernel::play(const QString path, bool isFile) {
    if (initializer->getStream()) {
        qDebug() << "Играем что-то";
        BASS_CHANNELINFO info;
        BASS_ChannelGetInfo(initializer->getStream(), &info);
        // If there was a pause - play
        qDebug() << "1) " << !path.length();
        qDebug() << "2)" << (info.filename);
        qDebug() << "2)" << (path.toLocal8Bit());
        qDebug() << "2)" << (info.filename == path.toLocal8Bit());
        if (!path.length() || info.filename == path.toLocal8Bit()) {
            qDebug() << "Мы уже играем этот файл";
            if (BASS_ChannelIsActive(initializer->getStream()) == BASS_ACTIVE_PAUSED) {
                qDebug() << "Продолжили играть этот файл после паузы";
                if (controller->play()) // already playing
                    setState(KernelState::play);
            }
            return;
        }
        // If the new file/stream
        else {
            qDebug() << "Это новый файл. Останавливаем воспроизведение";
            initializer->freeStream();
            setState(KernelState::stop);
        }
    }
    // New file/stream
    qDebug() << "Инициализируем новый поток";
    if (isFile) {
        qDebug() << "Это файл";
        initializer->initFile(path.toLocal8Bit().data());
    }
    else {
        qDebug() << "Это URL";
        initializer->initUrl(path.toLocal8Bit().data());
        qDebug() << BASS_ErrorGetCode();
    }
    controller->setStream(initializer->getStream());
    parameters->setStream(initializer->getStream());
    if (controller->play()) {
        setState(KernelState::play);
        qDebug() << "Играем новый поток";
    }
}

void Kernel::pause() {
    if (initializer->getStream() && controller->pause())
        setState(KernelState::pause);
    qDebug() << "Поставили на паузу";

}

void Kernel::stop() {
    if (initializer->getStream() && controller->stop())
        setState(KernelState::stop);
    qDebug() << "Остановили воспроизведение";
}

void Kernel::setVolume(int value) {

}

void Kernel::setReverb(int value) {

}

void Kernel::setBalance(int value) {

}

void Kernel::setTime(int value) {

}

KernelState Kernel::state() const {
    return m_state;
}

void Kernel::setState(KernelState newState) {
    if (m_state == newState)
        return;
    m_state = newState;
    emit stateChanged();
}
