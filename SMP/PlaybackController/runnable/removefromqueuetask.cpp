/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "removefromqueuetask.h"

RemoveFromQueueTask::RemoveFromQueueTask(int id, QObject *parent) : QObject(parent) {
    this->id = id;
}

void RemoveFromQueueTask::run() {
    QString name = "removeFromQueue";
    DBConnect dbc(name);
    dbc.connect();
    std::unique_ptr<QueueController> queueController
            (new QueueController(name));
    queueController->removeFromQueue(id);
    emit removedCompleted();
}
