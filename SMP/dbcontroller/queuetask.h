/*
 * Задача многопоточного доступа к БД для создания очереди
 */

#ifndef QUEUETASK_H
#define QUEUETASK_H

#include <QObject>
#include <QRunnable>
#include "Code/DBController/connectioncontroller.h"

class QueueTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    QueueTask(int id, QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void completed();

private:
    int _id;

};

#endif // QUEUETASK_H
