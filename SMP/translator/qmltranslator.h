/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef QMLTRANSLATOR_H
#define QMLTRANSLATOR_H

#include <QObject>
#include <QTranslator>
#include <QStringList>

class QmlTranslator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString EmptyString READ EmptyString WRITE setEmptyString NOTIFY EmptyStringChanged)
    Q_PROPERTY(QString CurrentLang READ CurrentLang WRITE setCurrentLang NOTIFY CurrentLangChanged)
public:
    explicit QmlTranslator(QObject *parent = nullptr);
    QString getEmptyString();
    Q_INVOKABLE void selectLanguage(QString language);
    Q_INVOKABLE QStringList getLangs();

    const QString &EmptyString() const;
    void setEmptyString(const QString &newEmptyString);
    const QString &CurrentLang() const;
    void setCurrentLang(const QString &newCurrentLang);

signals:
    void EmptyStringChanged();
    void CurrentLangChanged();

private:
    QTranslator *translator;
    const QStringList langs = {"en", "ru"};

    QString m_EmptyString;
    QString m_CurrentLang;
};

#endif // QMLTRANSLATOR_H
