#include "inserttopltask.h"

InsertToPlTask::InsertToPlTask(int id, QList<int> ids, QObject *parent)
    : QObject(parent) {
    this->id = id;
    this->ids = ids;
}

void InsertToPlTask::run() {
    QString name = "createQueueTask";
    DBConnect dbc(name);
    dbc.connect();

    PlaylistController pc(name);

    for (const int cid : ids) {
        pc.insertToPlaylist(id, cid);
    }

    emit insertCompleted();
}
