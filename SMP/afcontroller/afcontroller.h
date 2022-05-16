#ifndef AFCONTROLLER_H
#define AFCONTROLLER_H

#include <QObject>
#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QDebug>

class AFController : public QObject
{
    Q_OBJECT
public:
    explicit AFController(QObject *parent = nullptr);
    static AFController *instance() { return afInstance; }

signals:
    void isafGain();
    void isafLoss();
    void isafLossTransient();
    void isafLossTransientCanDuck();
    void isafCorrect();
    void isafFailed();

private:
    static AFController *afInstance;

};

#endif
#endif // AFCONTROLLER_H
