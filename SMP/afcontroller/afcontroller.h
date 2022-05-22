/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef AFCONTROLLER_H
#define AFCONTROLLER_H

#include <QObject>
#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QDebug>

/**
 * @brief The AFController class
 *
 * Класс предназначен для обработки событий, возникающих при работе с
 * аудиофокусом для устройств на базе Android.
 *
 * The class is designed to handle events that occur when working with autofocus
 * for Android devices.
 */
class AFController : public QObject
{
    Q_OBJECT
public:
    explicit AFController(QObject *parent = nullptr);
    static AFController *instance() { return afInstance; }
    void AFRequest();

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
