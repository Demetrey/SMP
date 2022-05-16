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

void NWorker::updateNotification() {
    nController.notificate(cp->Title(), kp->Statement() != KernelState::State::Play);
}

void NWorker::pausePlay() {
    if (kp->Statement() == KernelState::State::Play) {
        kp->pause();
    }
    else if (kp->Statement() == KernelState::State::Pause) {
        kp->play();
    }
}

#endif
