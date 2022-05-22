/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "afworker.h"

#ifdef Q_OS_ANDROID

AFWorker::AFWorker(KernelPresenter *kPresenter,
                   QObject *parent)
    : QObject(parent) {
    this->kPresenter = kPresenter;

    connect(afController.instance(), SIGNAL(isafGain()), this, SLOT(onIsafGain()));
    connect(afController.instance(), SIGNAL(isafLoss()), this, SLOT(onIsafLoss()));
    connect(afController.instance(), SIGNAL(isafLossTransient()), this, SLOT(onIsafLossTransient()));
    connect(afController.instance(), SIGNAL(isafLossTransientCanDuck()), this, SLOT(onIsafLossTransientCanDuck()));
    connect(afController.instance(), SIGNAL(isafCorrect()), this, SLOT(onIsafCorrect()));
    connect(afController.instance(), SIGNAL(isafFailed()), this, SLOT(onIsafFailed()));
    connect(this->kPresenter, SIGNAL(StatementChanged()), this, SLOT(onPlay()));
}

/**
 * @brief AFWorker::onIsafGain
 * Обработка события возвращения аудиофокуса
 * Handling the Audio Focus Return Event
 */
void AFWorker::onIsafGain() {
    switch (currentState) {
    case afError:
        break;
    case afDefault:
        break;
    case afLossed:
        currentState = AFStates::afDefault;
        break;
    case afLossTransient:
        currentState = AFStates::afDefault;
        kPresenter->play();
        break;
    case afLossTransientCanDuck:
        kPresenter->setVolume(backVolume);
        backVolume = 0;
        break;
    }
}

/**
 * @brief AFWorker::onPlay
 * При начале воспроизведения выполняется запрос аудиофокуса
 * Audio focus request is made when playback starts
 */
void AFWorker::onPlay() {
    if (kPresenter->Statement() == KernelState::State::Play) {
        afController.AFRequest();
    }
}

/**
 * @brief AFWorker::onIsafLoss
 * При потери аудиофокуса выполняется остановка воспроизведения
 * Playback stops when audio focus is lost
 */
void AFWorker::onIsafLoss() {
    this->kPresenter->pause();
    currentState = AFStates::afLossed;
}

/**
 * @brief AFWorker::onIsafLossTransient
 * При кратковременной потери аудиофокуса выполняется приостановка воспроизведения
 * Momentary loss of audio focus pauses playback
 */
void AFWorker::onIsafLossTransient() {
    this->kPresenter->pause();
    currentState = AFStates::afLossTransient;
}

/**
 * @brief AFWorker::onIsafLossTransientCanDuck
 * При потери аудиофокуса на кратковременное воспроизведение звука другим
 * прилоежнием, уменьшается звук воспроизведения до 20%
 * When audio focus is lost on short-term sound playback by another application,
 * playback sound is reduced by up to 20%
 */
void AFWorker::onIsafLossTransientCanDuck() {
    backVolume = this->kPresenter->Volume();
    this->kPresenter->setVolume(20);
    currentState = AFStates::afLossTransientCanDuck;
}

/**
 * @brief AFWorker::onIsafCorrect
 * Обработка события корректного получения аудиофокуса
 * Handling the correctly received audio focus event
 */
void AFWorker::onIsafCorrect() {
    currentState = AFStates::afDefault;
}

/**
 * @brief AFWorker::onIsafFailed
 * Обработка события ошибки получения аудиофокуса
 * Handling the Audio Focus Getting Error Event
 */
void AFWorker::onIsafFailed() {
    currentState = AFStates::afError;
}

#endif //Q_OS_ANDROID
