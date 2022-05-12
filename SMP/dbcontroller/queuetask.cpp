#include "queuetask.h"

QueueTask::QueueTask(int id, QObject *parent) : QObject(parent)
{
    this->_id = id;
}

void QueueTask::run()
{
    ConnectionController connectionContorller("queueCreator");
    connectionContorller.dbconnect();
    connectionContorller.createPlayQueue(_id);
    emit completed();
}
