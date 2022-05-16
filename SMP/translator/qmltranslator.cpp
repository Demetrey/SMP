/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "qmltranslator.h"
#include <QDebug>
#include <QGuiApplication>
#include <QDir>

QmlTranslator::QmlTranslator(QObject *parent)
    : QObject(parent) {
    this->translator = new QTranslator(this);
    setCurrentLang("en");
}

QString QmlTranslator::getEmptyString() {
    return QString();
}

void QmlTranslator::selectLanguage(QString language) {
    QString file;
    if (language == "ru") {
        file = ":/translations/QtLanguage_ru.qm";
        setCurrentLang("ru");
    }

    if (!translator->load(file)) {
        setCurrentLang("en");
        qDebug() << "Failed to load translation file, falling back to English";
    }
    qApp->installTranslator(translator);

    emit EmptyStringChanged();
}

QStringList QmlTranslator::getLangs() {
    return langs;
}

const QString &QmlTranslator::EmptyString() const
{
    return m_EmptyString;
}

void QmlTranslator::setEmptyString(const QString &newEmptyString)
{
    if (m_EmptyString == newEmptyString)
        return;
    m_EmptyString = newEmptyString;
    emit EmptyStringChanged();
}

const QString &QmlTranslator::CurrentLang() const
{
    return m_CurrentLang;
}

void QmlTranslator::setCurrentLang(const QString &newCurrentLang)
{
    if (m_CurrentLang == newCurrentLang)
        return;
    m_CurrentLang = newCurrentLang;
    emit CurrentLangChanged();
}
