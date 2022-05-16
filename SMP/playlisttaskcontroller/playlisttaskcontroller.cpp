/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playlisttaskcontroller.h"

PlaylistTaskController::PlaylistTaskController(QObject *parent) : QObject(parent) {
}

void PlaylistTaskController::insertToPlaylist(QList<int> ids, int id) {
    emit startInPlaylistAdding();
    InsertToPlTask *task = new InsertToPlTask(id, ids);
    connect(task, SIGNAL(insertCompleted()), this, SLOT(onInsertFinished()));
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);
}

void PlaylistTaskController::onInsertFinished() {
    emit endInPlaylistAdding();
}
