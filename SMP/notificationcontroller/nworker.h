#ifndef NWORKER_H
#define NWORKER_H

#include <QObject>
#ifdef Q_OS_ANDROID

#include "notificationcontroller.h"
#include "presenters/kernelpresenter.h"
#include "PlaybackController/playqueuecontroller.h"
#include "presenters/compositionpresenter.h"

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
