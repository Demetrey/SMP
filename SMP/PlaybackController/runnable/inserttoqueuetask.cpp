/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "inserttoqueuetask.h"

InsertToQueueTask::InsertToQueueTask(int id, QObject *parent)
    : QObject(parent) {
    this->id = id;
}

void InsertToQueueTask::run() {
    QString name = "insertToQueue";
    DBConnect dbc(name);
    dbc.connect();
    std::unique_ptr<QueueController> queueController
            (new QueueController(name));
    queueController->insertToQueue(id);
    emit insertCompleted();
}
