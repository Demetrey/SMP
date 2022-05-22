/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef REMOVEFROMQUEUETASK_H
#define REMOVEFROMQUEUETASK_H

#include <QObject>
#include <QRunnable>

#include "dbcontroller/queuecontroller.h"

/**
 * @brief The RemoveFromQueueTask class
 * Удаление композиции из очереди в другом потоке
 * Removing a composition from a queue in another thread
 */
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
