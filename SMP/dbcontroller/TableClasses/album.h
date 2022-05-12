/*
 * Представление альбома
 */

#ifndef ALBUM_H
#define ALBUM_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>
#include "AbstractTable.h"

class Album : public QObject, public AbstractTable
{
    Q_OBJECT
public:
    explicit Album(QString connectionName, QObject *parent = nullptr);


    // AbstractTable interface
public:
    int insert(const QVariantList &data) const override;
    void remove(const int id) override;
    void update(const int id, const QVariantList &data) override;

private:
    QString _connectionName;

    const QString tableName = "Album";
    const QVector<QString> rows {"id", "name"};

    int checkId(const QVariantList &data) const;

};

#endif // ALBUM_H
