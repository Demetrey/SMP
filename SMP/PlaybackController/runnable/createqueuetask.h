/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

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

/**
 * @brief The CreateQueueTask class
 * Создание очереди в другом потоке
 * Creating a queue on another thread
 */

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
