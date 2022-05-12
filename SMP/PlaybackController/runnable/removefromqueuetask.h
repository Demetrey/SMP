#ifndef REMOVEFROMQUEUETASK_H
#define REMOVEFROMQUEUETASK_H

#include <QObject>
#include <QRunnable>

#include "dbcontroller/queuecontroller.h"

class RemoveFromQueueTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit RemoveFromQueueTask(int id, QObject *parent = nullptr);
    void run() override;

signals:
    void removedCompleted();

private:
    int id;

};

#endif // REMOVEFROMQUEUETASK_H
