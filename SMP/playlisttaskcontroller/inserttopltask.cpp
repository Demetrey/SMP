/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

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
