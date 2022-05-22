/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "afcontroller.h"

#ifdef Q_OS_ANDROID

/**
 * @brief afGain
 * Обработка события возвращения аудиофокуса приложению
 * Handling the audio focus return event to the application
 */
static void afGain(JNIEnv * /*env*/, jobject /*obj*/) {
    emit AFController::instance()->isafGain();
    qDebug() << "onAFGain";
}

/**
 * @brief afLoss
 * Обработка события потери аудиофокуса
 * Handling the audio focus loss event
 */
static void afLoss(JNIEnv * /*env*/, jobject /*obj*/) {
    emit AFController::instance()->isafLoss();
    qDebug() << "onAFLose";
}

/**
 * @brief afLossTransient
 * Обработка события кратковременной потери аудиофокуса
 * Handling the momentary loss of audio focus event
 */
static void afLossTransient(JNIEnv * /*env*/, jobject /*obj*/) {
    emit AFController::instance()->isafLossTransient();
    qDebug() << "onAFLossTransient";
}

/**
 * @brief afLossTransientCanDuck
 * Обработка события потери аудиофокуса на кратковременное воспроизведение звука
 * другим приложением
 * Handling the audio focus loss event for a momentary audio playback by another
 * application
 */
static void afLossTransientCanDuck(JNIEnv * /*env*/, jobject /*obj*/) {
    emit AFController::instance()->isafLossTransientCanDuck();
    qDebug() << "onAFLossTransientCanDuck";
}

/**
 * @brief afCorrect
 * Обработка события корректного получения аудиофокуса
 * Handling the correctly received audio focus event
 */
static void afCorrect(JNIEnv * /*env*/, jobject /*obj*/) {
    emit AFController::instance()->isafCorrect();
    qDebug() << "onAFCorrect";
}

/**
 * @brief afFailed
 * Обработка события ошибки получения аудиофокуса
 * Handling the Audio Focus Getting Error Event
 */
static void afFailed(JNIEnv * /*env*/, jobject /*obj*/) {
    emit AFController::instance()->isafFailed();
    qDebug() << "onAFFailed";
}

AFController *AFController::afInstance = nullptr;

AFController::AFController(QObject *parent) : QObject(parent) {
    afInstance = this;

    //регистрация функций в jni
    JNINativeMethod methods[] {
                               {"afGain", "()V", (void *)afGain},
                               {"afLoss", "()V", (void *)afLoss},
                               {"afLossTransient", "()V", (void *)afLossTransient},
                               {"afLossTransientCanDuck", "()V", (void *)afLossTransientCanDuck},
                               {"afCorrect", "()V", (void *)afCorrect},
                               {"afFailed", "()V", (void *)afFailed}};
    QAndroidJniObject javaClass("com/demetrey/audiofocus/AFFunctions");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);

    QAndroidJniObject::callStaticMethod<void>("com/demetrey/audiofocus/AFReceiver",
                                              "startService",
                                              "(Landroid/content/Context;)V",
                                              QtAndroid::androidActivity().object());
}

/**
 * @brief AFController::AFRequest
 * Запрос аудиофокуса
 * Audio focus request
 */
void AFController::AFRequest() {
    QAndroidJniObject::callStaticMethod<void>("com/demetrey/audiofocus/AFReceiver",
                                              "requestAudioFocus",
                                              "(Landroid/content/Context;)V",
                                              QtAndroid::androidActivity().object());
}

#endif //Q_OS_ANDROID
