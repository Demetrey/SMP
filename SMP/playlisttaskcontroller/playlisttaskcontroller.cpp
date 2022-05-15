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
