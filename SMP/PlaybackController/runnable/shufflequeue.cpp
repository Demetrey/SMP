/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "shufflequeue.h"

ShuffleQueue::ShuffleQueue(int idCurrentComposition, QObject *parent) : QObject(parent) {
    this->idCurrentComposition = idCurrentComposition;
}

void ShuffleQueue::run() {
    QString name = "removeFromQueue";
    DBConnect dbc(name);
    dbc.connect();
    std::unique_ptr<QueueController> queueController
            (new QueueController(name));
    PlayQueueModel model(dbc.getDB());

    if (model.rowCount() < 2)
        return;
    QRandomGenerator *rg;
    rg = QRandomGenerator::global();
    QVector<int> ids(model.rowCount());

    for (int i = 0; i < model.rowCount(); i++) {
        ids[i] = model.data(model.index(i, 0), model.idRole).toInt();
    }

    qDebug() << "IDCURRENTCOMPOSITION:::::" << idCurrentComposition;
    qDebug() << "АЙДИШКИ ПОСЛЕ ПЕРЕМЕШКИ" << ids;
    for (int i = ids.size() - 1; i > 1; i--) {
        int j = rg->bounded(1, i);
        if (j == 0)
            continue;
        int temp = ids[i];
        ids[i] = ids[j];
        ids[j] = temp;
    }
    int indexCurrent = ids.indexOf(idCurrentComposition);
    ids[indexCurrent] = ids[0];
    ids[0] = idCurrentComposition;
    qDebug() << "АЙДИШКИ ПОСЛЕ ПЕРЕМЕШКИ" << ids;
    for (int i = 0; i < ids.size(); i++) {
        queueController->updateQueueNumbers(ids[i], i);
    }

    emit shuffledQueue();
}
