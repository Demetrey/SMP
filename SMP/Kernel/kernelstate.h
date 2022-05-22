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
    /**
     * @brief The State enum
     * Перечисление доступных состояний ядра воспроизведения
     * Enumeration of available replay engine states
     */
    enum class State : int {
        Stop,
        Play,
        Pause
    };
    Q_ENUM(State)
};

#endif // KERNELSTATE_H
