/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef QUEUECONTROLLER_H
#define QUEUECONTROLLER_H

#include "basecontroller.h"
#include "Interfaces/IPlaybackQueueController.h"
#include "Tables/playbackqueue.h"

class QueueController : public IPlaybackQueueController
{
    Q_OBJECT
public:
    QueueController(QString connectionName);
    ~QueueController();

signals:
    // IPlaybackQueueController interface
    void changedQueue();

public slots:
    // IPlaybackQueueController interface
    void insertToQueue(const int id) override;
    void removeFromQueue(const int id) override;
    void updateQueueNumbers(const int idComposition, const int number) override;
    void clearQueue() override;

private:
    PlaybackQueue *playQueue;
};

#endif // QUEUECONTROLLER_H
