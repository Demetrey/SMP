/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "kernelpresenter.h"
#include <QDebug>

KernelPresenter::KernelPresenter(QObject *parent, IKernel *kernel) : QObject(parent) {
    this->kernel = kernel;
    m_Statement = KernelState::State::Stop;
    m_Volume = this->kernel->getVolume();
    m_Reverb = this->kernel->getReverb();
    m_Balance = this->kernel->getBalance();

    timer = new QTimer();
    timer->setInterval(500); //ms
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTick()));

    // connections
    connect(this, SIGNAL(play()), this->kernel, SLOT(play()));
    connect(this, SIGNAL(pause()), this->kernel, SLOT(pause()));
    connect(this->kernel, SIGNAL(timeUpdated(int)),
            this, SLOT(onTimeUpdated(int)));
    connect(this->kernel, SIGNAL(kernelStateChanged(const KernelState::State)),
            this, SLOT(onKernelStatementChanged(const KernelState::State)));
    connect(this->kernel, SIGNAL(volumeChanged(int)), this, SLOT(onVolumeChanged(int)));
    connect(this->kernel, SIGNAL(reverbChanged(int)), this, SLOT(onReverbChanged(int)));
    connect(this->kernel, SIGNAL(balanceChanged(int)), this, SLOT(onBalanceChanged(int)));
    connect(this, SIGNAL(VolumeChanged(int)), this->kernel, SLOT(setVolume(int)));
    connect(this, SIGNAL(BalanceChanged(int)), this->kernel, SLOT(setBalance(int)));
    connect(this, SIGNAL(ReverbChanged(int)), this->kernel, SLOT(setReverb(int)));
    timer->start();
}

KernelPresenter::~KernelPresenter() {
    delete timer;
}


int KernelPresenter::CompositionTime() const {
    return m_CompositionTime;
}

void KernelPresenter::setCompositionTime(int newCompositionTime) {
    if (m_CompositionTime == newCompositionTime)
        return;
    m_CompositionTime = newCompositionTime;
    emit CompositionTimeChanged();
}

int KernelPresenter::Volume() const {
    return m_Volume;
}

void KernelPresenter::setVolume(int newVolume) {
    if (m_Volume == newVolume)
        return;
    m_Volume = newVolume;
    emit VolumeChanged(m_Volume);
}

int KernelPresenter::Reverb() const {
    return m_Reverb;
}

void KernelPresenter::setReverb(int newReverb) {
    if (m_Reverb == newReverb)
        return;
    m_Reverb = newReverb;
    emit ReverbChanged(m_Reverb);
}

int KernelPresenter::Balance() const {
    return m_Balance;
}

void KernelPresenter::setBalance(int newBalance) {
    if (m_Balance == newBalance)
        return;
    m_Balance = newBalance;
    emit BalanceChanged(m_Balance);
}

const KernelState::State &KernelPresenter::Statement() const {
    return m_Statement;
}

void KernelPresenter::setStatement(const KernelState::State &newStatement) {
    if (m_Statement == newStatement)
        return;
    m_Statement = newStatement;
    emit StatementChanged();
}

QList<double> KernelPresenter::getEqValues() {
    return kernel->getEqValues();
}

QList<int> KernelPresenter::getEqCenters() {
    return kernel->getEqCenters();
}

void KernelPresenter::setEqValue(int center, double value) {
    kernel->setEqValue(center, value);
    emit eqChanged();
}

int KernelPresenter::getCurrentPosition() {
    return kernel->getCurrentTime();
}

void KernelPresenter::onKernelStatementChanged(const KernelState::State statement) {
    setStatement(statement);
}

void KernelPresenter::onTimeUpdated(int time) {
    setCompositionTime(time);
}

void KernelPresenter::onVolumeChanged(int value) {
    setVolume(value);
}

void KernelPresenter::onReverbChanged(int value) {
    setReverb(value);
}

void KernelPresenter::onBalanceChanged(int value) {
    setBalance(value);
}

void KernelPresenter::onTimerTick() {
    setCurrentTime(kernel->getCurrentTime());
}

int KernelPresenter::CurrentTime() const
{
    return m_CurrentTime;
}

void KernelPresenter::setCurrentTime(int newCurrentTime)
{
    if (m_CurrentTime == newCurrentTime)
        return;
    m_CurrentTime = newCurrentTime;
    emit CurrentTimeChanged();
}
