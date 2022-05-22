/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "settings.h"

Settings::Settings(PlayQueueController *pqController,
                   KernelPresenter *kPresenter,
                   QmlTranslator *translator,
                   ThemePresenter *tPresenter,
                   QObject *parent)
    : QObject(parent) {
    timer = new QTimer(this);
    timer->setInterval(SAVE_INTERVAL);

    isKernelChanged = 0;
    isGUIChanged = 0;
    isPQChanged = 0;
    isEqChanged = 0;

    this->kPresenter = kPresenter;
    this->pqController = pqController;
    this->translator = translator;
    this->tPresenter = tPresenter;

    connect(this->kPresenter, &KernelPresenter::BalanceChanged,
            this, &Settings::onKernelChanged);
    connect(this->kPresenter, &KernelPresenter::ReverbChanged,
            this, &Settings::onKernelChanged);
    connect(this->kPresenter, &KernelPresenter::VolumeChanged,
            this, &Settings::onKernelChanged);
    connect(this->kPresenter, &KernelPresenter::eqChanged,
            this, &Settings::onEqChanged);

    connect(this->pqController, &PlayQueueController::CurrentPlayIdChanged,
            this, &Settings::onPQChanged);
    connect(this->pqController, &PlayQueueController::IsFileChanged,
            this, &Settings::onPQChanged);
    connect(this->pqController, &PlayQueueController::IsShuffledChanged,
            this, &Settings::onPQChanged);

    connect(this->translator, &QmlTranslator::CurrentLangChanged,
            this, &Settings::onGUIChanged);

    connect(this->tPresenter, &ThemePresenter::CurrentThemeIndexChanged,
            this, &Settings::onGUIChanged);

    connect(this->timer, &QTimer::timeout, this, &Settings::onTimerTick);
}

void Settings::loadSettings() {
    QSettings settings(SETTINGS_FILE, QSettings::IniFormat);
    // kernel parameters
    settings.beginGroup("KernelParameters");
        kPresenter->setBalance(settings.value("Balance", 0).toInt());
        kPresenter->setVolume(settings.value("Volume", 100).toInt());
        kPresenter->setReverb(settings.value("Reverberation", 0).toInt());
    settings.endGroup();
    // Эквалайзер
    settings.beginGroup("EQValues");
        QStringList keys = settings.childKeys();
        for (const QString &key : qAsConst(keys)) {
            kPresenter->setEqValue(key.toInt(), settings.value(key, 0).toDouble());
        }

    settings.endGroup();
    // playbackcontroller
    settings.beginGroup("PlayQController");
        bool isFile = settings.value("IsFile", true).toBool();
        bool isShuffled = settings.value("Shuffled", false).toBool();
        int currentID = settings.value("CurrentID", -1).toInt();
        pqController->settingsSet(currentID, isFile, isShuffled);
    settings.endGroup();
    // interface
    settings.beginGroup("Interface");
        translator->selectLanguage(settings.value("Lang", "en").toString());
        tPresenter->setTheme(settings.value("Theme", 0).toInt());
    settings.endGroup();
}

void Settings::saveSettings() {
    timer->stop();
    QSettings settings(SETTINGS_FILE, QSettings::IniFormat);
    // Параметры контроля воспроизведения
    if (isPQChanged) {
        settings.beginGroup("PlayQController");
            settings.setValue("CurrentID", pqController->CurrentPlayId());
            settings.setValue("Shuffled", pqController->IsShuffled());
            settings.setValue("IsFile", pqController->IsFile());
            isPQChanged = 0;
        settings.endGroup();
    }
    // Параметры воспроизведения
    if (isKernelChanged) {
        settings.beginGroup("KernelParameters");
            settings.setValue("Volume", kPresenter->Volume());
            settings.setValue("Balance", kPresenter->Balance());
            settings.setValue("Reverberation", kPresenter->Reverb());
            isKernelChanged = 0;
        settings.endGroup();
    }
    // Эквалайзер
    if (isEqChanged) {
        settings.beginGroup("EQValues");
            QList<int> eqCenters = kPresenter->getEqCenters();
            QList<double> eqValues = kPresenter->getEqValues();
            if (eqCenters.size() == eqValues.size()) {
                for (int i = 0; i < eqCenters.size(); i++)
                    settings.setValue(QString::number(eqCenters.at(i)),
                                      eqValues.at(i));
            }
            isEqChanged = 0;
        settings.endGroup();
    }
    // интерфей
    if (isGUIChanged) {
        settings.beginGroup("Interface");
            settings.setValue("Lang", translator->CurrentLang());
            settings.setValue("Theme", tPresenter->CurrentThemeIndex());
            isGUIChanged = 0;
        settings.endGroup();
    }
}

void Settings::onKernelChanged() {
    timer->start();
    isKernelChanged = 1;
}

void Settings::onPQChanged() {
    timer->start();
    isPQChanged = 1;
}

void Settings::onGUIChanged() {
    timer->start();
    isGUIChanged = 1;
}

void Settings::onEqChanged() {
    timer->start();
    isEqChanged = 1;
}

void Settings::onTimerTick() {
    saveSettings();
}
