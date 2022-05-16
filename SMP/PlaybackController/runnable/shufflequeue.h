/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

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
