/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef AFWORKER_H
#define AFWORKER_H

#include <QObject>

#ifdef Q_OS_ANDROID

#include "afcontroller.h"
#include "presenters/kernelpresenter.h"
#include "PlaybackController/playqueuecontroller.h"

/**
 * @brief The AFWorker class
 *
 * Класс предназначен для взаимодействия с объектами C++ при обработке событий
 * аудиофокуса
 *
 * The class is designed to interact with C++ objects when handling audio focus
 * events
 */
class AFWorker : public QObject
{
    Q_OBJECT
public:
    explicit AFWorker(KernelPresenter *kPresenter,
                      QObject *parent = nullptr);

signals:

private slots:
    void onIsafGain();
    void onIsafLoss();
    void onIsafLossTransient();
    void onIsafLossTransientCanDuck();
    void onIsafCorrect();
    void onIsafFailed();
    void onPlay();

private:
    enum AFStates {
        afError = -1,
        afDefault,
        afLossed,
        afLossTransient,
        afLossTransientCanDuck
    };

    PlayQueueController *pqController;
    KernelPresenter *kPresenter;
    AFController afController;

    AFStates currentState = AFStates::afDefault;
    int backVolume;

};

#endif
#endif // AFWORKER_H
