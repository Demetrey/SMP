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
