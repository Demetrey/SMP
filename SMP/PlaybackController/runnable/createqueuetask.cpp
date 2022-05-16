/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "createqueuetask.h"

CreateQueueTask::CreateQueueTask(int id, QObject *parent)
    : QObject(parent) {
    this->id = id;
}

void CreateQueueTask::run() {
    QString name = "createQueueTask";
    DBConnect dbc(name);
    dbc.connect();
    std::unique_ptr<QueueController> queueController
            (new QueueController(name));
    queueController->clearQueue();

    if (id) {
        std::unique_ptr<PlaylistController> playlistCntroller
                (new PlaylistController(name));
        std::unique_ptr<PlaylistDataModel> playlistDataModel
                (new PlaylistDataModel(dbc.getDB()));
        playlistDataModel->updateModel(this->id);

        for (int i = 0; i < playlistDataModel->rowCount(); i++) {
            queueController->insertToQueue(
                        playlistDataModel->data(playlistDataModel->index(i, 0),
                                                playlistDataModel->idRole).toInt());
        }
    }
    else {
        std::unique_ptr<CompositionController> playlistCntroller
                (new CompositionController(name));
        std::unique_ptr<MediaModel> playlistDataModel
                (new MediaModel(dbc.getDB()));

        for (int i = 0; i < playlistDataModel->rowCount(); i++) {
            queueController->insertToQueue(
                        playlistDataModel->data(playlistDataModel->index(i, 0),
                                                playlistDataModel->idRole).toInt());
        }
    }
    emit createdQueue();
}
