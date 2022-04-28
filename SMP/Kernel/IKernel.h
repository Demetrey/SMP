#ifndef IKERNEL_H
#define IKERNEL_H

#include <QObject>
#include "kernelstate.h"

class IKernel : public QObject {
public:
    virtual ~IKernel() {};
    virtual void initialize() = 0;
    virtual QList<QString> getDevices() = 0;
    virtual int getVolume() = 0;
    virtual int getReverb() = 0;
    virtual int getBalance() = 0;
    virtual int getCompositionTime() = 0;   // ms
    virtual int getCurrentTime() = 0;       // ms
    virtual QList<float> getEqValues() = 0;

private:
    virtual QList<QString> loadPlugins() = 0;

signals:
    void endOfFile();
    void kernelStateChanged(const KernelState::State);

public slots:
    virtual void initDevice(int, int) = 0;
    virtual void play(const QString, bool isFile = true) = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void setVolume(int) = 0;
    virtual void setReverb(int) = 0;
    virtual void setBalance(int) = 0;
    virtual void setTime(int) = 0;
    virtual void setEqValue(int, float) = 0;    // center, value

};
Q_DECLARE_INTERFACE(IKernel, "IKernel")

#endif // IKERNEL_H
