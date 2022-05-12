#ifndef CYCLESTATE_H
#define CYCLESTATE_H

#include <QObject>

class CycleState : public QObject
{
    Q_OBJECT
public:
    enum class Cycle : int {
        CycleNo,
        CycleQueue,
        CycleOne
    };
    Q_ENUM(Cycle)

};

#endif // CYCLESTATE_H
