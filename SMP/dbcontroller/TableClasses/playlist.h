/*
 * Представление плейлиста
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>
#include "AbstractTable.h"

class PlayList : public QObject, public AbstractTable
{
    Q_OBJECT
public:
    explicit PlayList(QString connectionName, QObject *parent = nullptr);


    // AbstractTable interface
public:
    int insert(const QVariantList &data) const override;
    void remove(const int id) override;
    void update(const int id, const QVariantList &data) override;

private:
    QString _connectionName;

    const QString tableName = "Playlist";
    const QVector<QString> rows {"id", "name"};
};

#endif // PLAYLIST_H
