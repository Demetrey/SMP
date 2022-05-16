#ifndef IKERNEL_H
#define IKERNEL_H

#include <QObject>
#include "kernelstate.h"

class IKernel : public QObject {
public:
    virtual ~IKernel() {};
    virtual void initialize() = 0;
    virtual int getVolume() = 0;
    virtual int getReverb() = 0;
    virtual int getBalance() = 0;
    virtual int getCompositionTime() = 0;   // ms
    virtual int getCurrentTime() = 0;       // ms
    virtual QList<double> getEqValues() = 0;
    virtual QList<int> getEqCenters() = 0;
    Q_INVOKABLE virtual QList<double> getVizValues() = 0;

private:
    virtual QList<QString> loadPlugins() = 0;

signals:
    void timeUpdated(int);
    void endOfFile();
    void kernelStateChanged(const KernelState::State);
    void volumeChanged(int);
    void reverbChanged(int);
    void balanceChanged(int);

public slots:
    virtual QStringList getDevices() = 0;
    virtual void initDevice(QString, int) = 0;
    virtual void play(const QString path = QString(), bool isFile = true) = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void setVolume(int) = 0;
    virtual void setReverb(int) = 0;
    virtual void setBalance(int) = 0;
    virtual void setTime(int) = 0;
    virtual void setEqValue(int, double) = 0; // center, value
    virtual void cycleFile() = 0;

};
Q_DECLARE_INTERFACE(IKernel, "IKernel")

#endif // IKERNEL_H
