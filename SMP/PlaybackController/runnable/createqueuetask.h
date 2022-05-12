#ifndef CREATEQUEUETASK_H
#define CREATEQUEUETASK_H

#include <QObject>
#include <QRunnable>
#include <QString>

#include "dbcontroller/queuecontroller.h"
#include "dbcontroller/playlistcontroller.h"
#include "dbcontroller/compositioncontroller.h"
#include "dbcontroller/Models/playqueuemodel.h"
#include "dbcontroller/Models/playlistdatamodel.h"
#include "dbcontroller/Models/mediamodel.h"

class CreateQueueTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit CreateQueueTask(int id, QObject *parent = nullptr);
    void run() override;

signals:
    void createdQueue();

private:
    int id;

};

#endif // CREATEQUEUETASK_H
