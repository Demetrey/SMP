/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef KERNELSTATE_H
#define KERNELSTATE_H

#include <QObject>

class KernelState : public QObject
{
    Q_OBJECT
public:
    enum class State : int {
        Stop,
        Play,
        Pause
    };
    Q_ENUM(State)
};

#endif // KERNELSTATE_H
