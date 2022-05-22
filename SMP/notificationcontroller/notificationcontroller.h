#ifndef NOTIFICATIONCONTROLLER_H
#define NOTIFICATIONCONTROLLER_H

#include <QObject>
#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QDebug>

/**
 * @brief The NotificationController class
 * Класс реализации вывода медиауведомлений для Android
 * Android Media Notification Implementation Class
 */
class NotificationController : public QObject
{
    Q_OBJECT
public:
    explicit NotificationController(QObject *parent = nullptr);
    static NotificationController *instance() { return nInstance; }
    void notificate(QString string, bool paused);

signals:
    void onNotificationUpdate(QString string, bool paused);
    void playButtonClicked();
    void nextButtonClicked();
    void previousButtonClicked();

private slots:
    void showNotification(QString string, bool paused);

private:
    static NotificationController *nInstance;

};

#endif // Q_OS_ANDROID
#endif // NOTIFICATIONCONTROLLER_H
