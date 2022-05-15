/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QList>
#include <QDir>
#include <QStringList>
#include <QFileInfoList>
#include <QMap>
#include <bass.h>
#include "IKernel.h"
#include "initializer.h"
#include "playbackcontroller.h"
#include "playbackparameters.h"
#include "kernelstate.h"
#include "readers/xmlloader.h"

class Kernel : public IKernel
{
    Q_OBJECT
    Q_INTERFACES(IKernel)

public:
    explicit Kernel();
    ~Kernel();
    // IKernel interface
    void initialize() override; // first call for setup default settings
    int getVolume() override;
    int getReverb() override;
    int getBalance() override;
    int getCompositionTime() override;
    int getCurrentTime() override;
    QList<double> getEqValues() override;
    QList<int> getEqCenters() override;

private:
    QList<QString> loadPlugins() override;

signals:
    // IKernel interface
    void timeUpdated(int time);
    void endOfFile();
    void kernelStateChanged(const KernelState::State);
    void volumeChanged(int);
    void reverbChanged(int);
    void balanceChanged(int);

public slots:
    // IKernel interface
    QStringList getDevices() override;
    void initDevice(QString deviceName = QString(), int freq = 44100) override;
    void play(const QString path = QString(), bool isFile = true) override;
    void pause() override;
    void stop() override;
    void setVolume(int value) override;
    void setReverb(int value) override;
    void setBalance(int value) override;
    void setTime(int value) override;
    void setEqValue(int center, double value) override;
    void cycleFile() override;


private:
    Initializer *initializer;
    PlaybackController *controller;
    PlaybackParameters *parameters;

};

#endif // KERNEL_H
