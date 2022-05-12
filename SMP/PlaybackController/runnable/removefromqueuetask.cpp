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
