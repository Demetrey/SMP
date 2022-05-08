/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef PLAYQUEUEMODEL_H
#define PLAYQUEUEMODEL_H

#include "mediamodel.h"

/**
 * @brief The PlayQueueModel class
 * Replay queue data representation model
 */
class PlayQueueModel : public MediaModel
{
    Q_OBJECT
public:
    explicit PlayQueueModel(QSqlDatabase db, QObject *parent = nullptr);

public slots:
    void updateModel(bool isSorted = false, const QString search = QString());
};

#endif // PLAYQUEUEMODEL_H
