#ifndef AFWORKER_H
#define AFWORKER_H

#include <QObject>

#ifdef Q_OS_ANDROID

#include "afcontroller.h"
#include "presenters/kernelpresenter.h"
#include "PlaybackController/playqueuecontroller.h"


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
