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
