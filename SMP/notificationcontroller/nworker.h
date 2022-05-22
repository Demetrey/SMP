/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef NWORKER_H
#define NWORKER_H

#include <QObject>
#ifdef Q_OS_ANDROID

#include "notificationcontroller.h"
#include "presenters/kernelpresenter.h"
#include "PlaybackController/playqueuecontroller.h"
#include "presenters/compositionpresenter.h"

/**
 * @brief The NWorker class
 * Класс для работы с уведомлениями из C++
 * Class for working with notifications from C++
 */
class NWorker : public QObject
{
    Q_OBJECT
public:
    explicit NWorker(KernelPresenter *kp,
                     PlayQueueController *pqc,
                     CompositionPresenter *cp,
                     QObject *parent = nullptr);

private slots:
    void updateNotification();
    void pausePlay();

private:
    KernelPresenter *kp;
    PlayQueueController *pqc;
    CompositionPresenter *cp;
    NotificationController nController;

};

#endif
#endif // NWORKER_H
