/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef CYCLESTATE_H
#define CYCLESTATE_H

#include <QObject>

class CycleState : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The Cycle enum
     * Перечисление состояний зацикливания очереди воспроизведения
     * Enumeration of looping states of the playback queue
     */
    enum class Cycle : int {
        CycleNo,
        CycleQueue,
        CycleOne
    };
    Q_ENUM(Cycle)

};

#endif // CYCLESTATE_H
