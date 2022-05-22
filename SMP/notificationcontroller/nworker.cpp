/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "nworker.h"

#ifdef Q_OS_ANDROID
NWorker::NWorker(KernelPresenter *kp, PlayQueueController *pqc,
                 CompositionPresenter *cp, QObject *parent)
    : QObject(parent) {
    this->kp = kp;
    this->pqc = pqc;
    this->cp = cp;

    connect(kp, SIGNAL(StatementChanged()), this, SLOT(updateNotification()));
    connect(cp, SIGNAL(TitleChanged()), this, SLOT(updateNotification()));

    connect(nController.instance(), SIGNAL(nextButtonClicked()), pqc, SLOT(nextFile()));
    connect(nController.instance(), SIGNAL(previousButtonClicked()), pqc, SLOT(prevFile()));
    connect(nController.instance(), SIGNAL(playButtonClicked()), this, SLOT(pausePlay()));
}

/**
 * @brief Update Notification
 * Обновление уведомления
 * Notification update
 */
void NWorker::updateNotification() {
    nController.notificate(cp->Title() + "/" + cp->Artisr(),
                           kp->Statement() != KernelState::State::Play);
}

/**
 * @brief Pause/Play
 * Обработка нажатия на кнопку Pause/Play
 * Handling the Pause/Play Button Press
 */
void NWorker::pausePlay() {
    if (kp->Statement() == KernelState::State::Play) {
        kp->pause();
    }
    else if (kp->Statement() == KernelState::State::Pause) {
        kp->play();
    }
}

#endif
