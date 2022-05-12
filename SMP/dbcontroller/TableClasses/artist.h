/*
 * Представление исполнителя
 */

#ifndef ARTIST_H
#define ARTIST_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>
#include "AbstractTable.h"

class Artist : public QObject, public AbstractTable
{
    Q_OBJECT
public:
    explicit Artist(QString connectionName, QObject *parent = nullptr);

    // AbstractTable interface
public:
    int insert(const QVariantList &data) const override;
    void remove(const int id) override;
    void update(const int id, const QVariantList &data) override;

private:
    QString _connectionName;

    const QString tableName = "Artist";
    const QVector<QString> rows {"id", "name"};

    int checkId(const QVariantList &data) const;
};

#endif // ARTIST_H
