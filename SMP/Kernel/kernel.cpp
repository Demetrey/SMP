/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "kernel.h"

Kernel::Kernel(QObject *parent) : QObject(parent) {

}

Kernel::~Kernel() {
    BASS_PluginFree(0); // Free all plugins
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
        HPLUGIN pluginHandler = BASS_PluginLoad((path + file + ext).toLocal8Bit().data(), 0);
        if (!BASS_PluginEnable(pluginHandler, 1)) {
            errorLoad.append(file);
        }
    }
    return errorLoad;
}
