/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef IPLAYBACKQUEUECONTROLLER_H
#define IPLAYBACKQUEUECONTROLLER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QList>
#include <QSqlDatabase>

/**
 * @brief The IPlaybackQueueController class
 * Интерфейс для котнроллера работы с очередью воспроизведения
 * Interface for the playback queue controller
 */
class IPlaybackQueueController : public QObject {
public slots:
    virtual void insertToQueue(const int id) = 0;
    virtual void removeFromQueue(const int id) = 0;
    virtual void updateQueueNumbers(const int idComposition,
                                   const int number) = 0;
    virtual void clearQueue() = 0;

signals:
    void changedQueue();

};

#endif // IPLAYBACKQUEUECONTROLLER_H
