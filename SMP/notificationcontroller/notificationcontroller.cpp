#include "notificationcontroller.h"

#ifdef Q_OS_ANDROID

static void nPlayButtonClicked(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки play в уведомлении
    emit NotificationController::instance()->playButtonClicked();
    qDebug() << "Play clicked";
}

static void nNextButtonClicked(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки next в уведомлении
    emit NotificationController::instance()->nextButtonClicked();
    qDebug() << "Next clicked";
}

static void nPreviousButtonClicked(JNIEnv * /*env*/, jobject /*obj*/) {
    // отслеживание нажатия кнопки prev в уведомлении
    emit NotificationController::instance()->previousButtonClicked();
    qDebug() << "Prev clicked";
}

NotificationController *NotificationController::nInstance = nullptr;

NotificationController::NotificationController(QObject *parent)
    : QObject(parent) {

    nInstance = this;

    connect(this, &NotificationController::onNotificationUpdate, this, &NotificationController::showNotification);

    //регистрация функций в jni
    JNINativeMethod methods[] {{"nPlayButtonClicked", "()V", (void *)nPlayButtonClicked},
                               {"nPreviousButtonClicked", "()V", (void *)nPreviousButtonClicked},
                               {"nNextButtonClicked", "()V", (void *)nNextButtonClicked}};
    QAndroidJniObject javaClass("com/demetrey/notification/NFunctions");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);

}

void NotificationController::notificate(QString string, bool paused) {
    emit onNotificationUpdate(string, paused);
}

void NotificationController::showNotification(QString string, bool paused) {
    // Создание медиауведомления
    QAndroidJniObject name = QAndroidJniObject::fromString(string);
    jboolean state = paused;
    QAndroidJniObject::callStaticMethod<void>("com/demetrey/notification/NController",
                                              "notify",
                                              "(Landroid/content/Context;Ljava/lang/String;Z)V",
                                              QtAndroid::androidContext().object(),
                                              name.object<jstring>(),
                                              state);
}

#endif // Q_OS_ANDROID
