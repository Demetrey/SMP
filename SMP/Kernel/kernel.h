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
#include "initializer.h"
#include "playbackcontroller.h"
#include "playbackparameters.h"
#include "kernelstate.h"
#include "readers/xmlloader.h"

class Kernel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(KernelState::State kernelState READ kernelState WRITE setKernelState NOTIFY kernelStateChanged)
public:
    explicit Kernel(QObject *parent = nullptr);
    ~Kernel();

    QList<QString> loadPlugins();

    const KernelState::State &kernelState() const;
    void setKernelState(const KernelState::State &newKernelState);

signals:
    void timeUpdated(const int position);
    void endOfFile();

    void kernelStateChanged();

public slots:
    void initDevice(int device = -1, int freq = 44100);
    void play(const QString path = QString(), bool isFile = true);
    void pause();
    void stop();
    void setVolume(int value);
    void setReverb(int value);
    void setBalance(int value);
    void setTime(int value);    // ms


private:
    Initializer *initializer;
    PlaybackController *controller;
    PlaybackParameters *parameters;
    KernelState::State m_kernelState;
};

#endif // KERNEL_H
