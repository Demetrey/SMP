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
}

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

void AFWorker::onIsafLoss() {
    this->kPresenter->pause();
    currentState = AFStates::afLossed;
}

void AFWorker::onIsafLossTransient() {
    this->kPresenter->pause();
    currentState = AFStates::afLossTransient;
}

void AFWorker::onIsafLossTransientCanDuck() {
    backVolume = this->kPresenter->Volume();
    this->kPresenter->setVolume(20);
    currentState = AFStates::afLossTransientCanDuck;
}

void AFWorker::onIsafCorrect() {
    currentState = AFStates::afDefault;
}

void AFWorker::onIsafFailed() {
    currentState = AFStates::afError;
}

#endif
