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

    ids[0] = idCurrentComposition;
    for (int i = ids.size() - 1; i > 1; i--) {
        int j = rg->bounded(1, i);
        if (j == idCurrentComposition)
            continue;
        int temp = ids[i];
        ids[i] = ids[j];
        ids[j] = temp;
    }
    for (int i = 0; i < ids.size(); i++) {
        queueController->updateQueueNumbers(ids[i], i);
    }

    emit shuffledQueue();
}
