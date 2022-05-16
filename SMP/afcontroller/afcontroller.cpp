#include "afcontroller.h"

#ifdef Q_OS_ANDROID

static void afGain(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки play в уведомлении
    emit AFController::instance()->isafGain();
    qDebug() << "onAFGain";
}

static void afLoss(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки play в уведомлении
    emit AFController::instance()->isafLoss();
    qDebug() << "onAFLose";
}

static void afLossTransient(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки play в уведомлении
    emit AFController::instance()->isafLossTransient();
    qDebug() << "onAFLossTransient";
}

static void afLossTransientCanDuck(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки play в уведомлении
    emit AFController::instance()->isafLossTransientCanDuck();
    qDebug() << "onAFLossTransientCanDuck";
}

static void afCorrect(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки play в уведомлении
    emit AFController::instance()->isafCorrect();
    qDebug() << "onAFCorrect";
}

static void afFailed(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки play в уведомлении
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

#endif
