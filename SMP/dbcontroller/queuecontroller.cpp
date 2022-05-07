/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "queuecontroller.h"

QueueController::QueueController(QString connectionName)
    : BaseController(connectionName) {
    playQueue = new PlaybackQueue(connectionName);
}

QueueController::~QueueController() {
    delete playQueue;
}

/**
 * @brief InsertToQueue
 * @param id - composition id
 */
void QueueController::insertToQueue(const int id) {
    playQueue->insert(id);
}

/**
 * @brief RemoveFromQueue
 * @param id - composition id
 */
void QueueController::removeFromQueue(const int id) {
    playQueue->remove(id);
}

/**
 * @brief UpdateQueueNumbers
 * @param idComposition -  - composition id
 * @param number - Sequence number of the song in the list
 */
void QueueController::updateQueueNumbers(const int idComposition, const int number) {
    playQueue->updateNumber(idComposition, number);
}
