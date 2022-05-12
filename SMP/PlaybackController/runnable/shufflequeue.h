#ifndef SHUFFLEQUEUE_H
#define SHUFFLEQUEUE_H

#include <QObject>
#include <QRunnable>
#include <QRandomGenerator>
#include <QVector>

#include "dbcontroller/queuecontroller.h"
#include "dbcontroller/Models/playqueuemodel.h"

class ShuffleQueue : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit ShuffleQueue(int idCurrentComposition, QObject *parent = nullptr);
    void run() override;

signals:
    void shuffledQueue();

private:
    int idCurrentComposition;

};

#endif // SHUFFLEQUEUE_H
