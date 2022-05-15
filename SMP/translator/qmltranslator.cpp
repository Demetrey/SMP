#include "qmltranslator.h"
#include <QDebug>
#include <QGuiApplication>
#include <QDir>

QmlTranslator::QmlTranslator(QObject *parent)
    : QObject(parent) {
    this->translator = new QTranslator(this);
}

QString QmlTranslator::getEmptyString() {
    return QString();
}

void QmlTranslator::selectLanguage(QString language) {
    QString file;
    if (language == "ru") {
        file = ":/translations/QtLanguage_ru.qm";
    }

    if (!translator->load(file)) {
        qDebug() << "Failed to load translation file, falling back to English";
    }
    qApp->installTranslator(translator);

    emit EmptyStringChanged();
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
