/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "getarttask.h"

GetArtTask::GetArtTask(QString path, QObject *parent) : QObject(parent) {
    this->path = path;
}

void GetArtTask::run() {
    TagReader tagReader;
    QImage result = tagReader.getCoverArt(path);
    emit completed(result);
}
