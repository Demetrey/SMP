#ifndef INSERTTOQUEUETASK_H
#define INSERTTOQUEUETASK_H

#include <QObject>
#include <QRunnable>

#include "dbcontroller/queuecontroller.h"

class InsertToQueueTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit InsertToQueueTask(int id, QObject *parent = nullptr);
    void run() override;

signals:
    void insertCompleted();

private:
    int id;

};

#endif // INSERTTOQUEUETASK_H
