/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef KERNELPRESENTER_H
#define KERNELPRESENTER_H

#include <QObject>
#include <QTimer>
#include "Kernel/kernelstate.h"
#include "Kernel/IKernel.h"

class KernelPresenter : public QObject
{
    Q_OBJECT

    // Properties
    // Displaying the current state of the kernel
    Q_PROPERTY(KernelState::State Statement READ Statement WRITE setStatement NOTIFY StatementChanged)
    // Display current song time (0 for streams)
    Q_PROPERTY(int CompositionTime READ CompositionTime WRITE setCompositionTime NOTIFY CompositionTimeChanged)
    // Displaying the current volume level (%)
    Q_PROPERTY(int Volume READ Volume WRITE setVolume NOTIFY VolumeChanged)
    // Display of the current reverb level (%)
    Q_PROPERTY(int Reverb READ Reverb WRITE setReverb NOTIFY ReverbChanged)
    // Display current balance level (%)
    Q_PROPERTY(int Balance READ Balance WRITE setBalance NOTIFY BalanceChanged)
    // Display current composition time
    Q_PROPERTY(int CurrentTime READ CurrentTime WRITE setCurrentTime NOTIFY CurrentTimeChanged)

    int m_CompositionTime;
    int m_Volume;
    int m_Reverb;
    int m_Balance;
    int m_CurrentTime;
    KernelState::State m_Statement;

    IKernel *kernel;
    QTimer *timer;

public:
    explicit KernelPresenter(QObject *parent = nullptr, IKernel *kernel = nullptr);
    ~KernelPresenter();

    // For properties
    int CompositionTime() const;
    void setCompositionTime(int newCompositionTime);
    int Volume() const;
    void setVolume(int newVolume);
    int Reverb() const;
    void setReverb(int newReverb);
    int Balance() const;
    void setBalance(int newBalance);
    const KernelState::State &Statement() const;
    void setStatement(const KernelState::State &newStatement);

    Q_INVOKABLE QList<double> getEqValues();
    Q_INVOKABLE QList<int> getEqCenters();
    Q_INVOKABLE void setEqValue(int center, double value);
    Q_INVOKABLE int getCurrentPosition(); // Query current playback position (ms)

    int CurrentTime() const;
    void setCurrentTime(int newCurrentTime);

signals:
    void pause();
    void play();
    // For properties
    void CompositionTimeChanged();
    void VolumeChanged(int);
    void ReverbChanged(int);
    void BalanceChanged(int);
    void StatementChanged();

    void CurrentTimeChanged();

public slots:
    // Updating properties with values ​​from the kernel
    void onKernelStatementChanged(const KernelState::State statement);
    void onTimeUpdated(int time);
    void onVolumeChanged(int value);
    void onReverbChanged(int value);
    void onBalanceChanged(int value);

private slots:
    void onTimerTick();

};

#endif // KERNELPRESENTER_H
