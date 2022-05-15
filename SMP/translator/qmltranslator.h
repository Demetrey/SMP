#ifndef QMLTRANSLATOR_H
#define QMLTRANSLATOR_H

#include <QObject>
#include <QTranslator>

class QmlTranslator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString EmptyString READ EmptyString WRITE setEmptyString NOTIFY EmptyStringChanged)
public:
    explicit QmlTranslator(QObject *parent = nullptr);
    QString getEmptyString();
    Q_INVOKABLE void selectLanguage(QString language);

    const QString &EmptyString() const;
    void setEmptyString(const QString &newEmptyString);

signals:
    void EmptyStringChanged();

private:
    QTranslator *translator;

    QString m_EmptyString;
};

#endif // QMLTRANSLATOR_H
