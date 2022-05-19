#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QTimer>
#include <QDebug>

#include "PlaybackController/playqueuecontroller.h"
#include "presenters/kernelpresenter.h"
#include "translator/qmltranslator.h"
#include "presenters/themepresenter.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(PlayQueueController *pqContriller,
                      KernelPresenter *kPresenter,
                      QmlTranslator *translator,
                      ThemePresenter *tPresenter,
                      QObject *parent = nullptr);
    void loadSettings();
    void saveSettings();

public slots:
    void onKernelChanged();
    void onPQChanged();
    void onGUIChanged();
    void onEqChanged();

signals:

private slots:
    void onTimerTick();

private:
    const QString SETTINGS_FILE = "settings.ini";
    const int SAVE_INTERVAL = 2500;

    bool isKernelChanged;
    bool isGUIChanged;
    bool isPQChanged;
    bool isEqChanged;

    PlayQueueController *pqController;
    KernelPresenter *kPresenter;
    QmlTranslator *translator;
    ThemePresenter *tPresenter;

    QTimer *timer;

};

#endif // SETTINGS_H
