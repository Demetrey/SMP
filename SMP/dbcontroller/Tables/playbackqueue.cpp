/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playbackqueue.h"

PlaybackQueue::PlaybackQueue(QString &connectionName)
    : PlaylistComposition(connectionName) {
    this->rows.append("number");
}

bool PlaybackQueue::insert(const int idComposition) {
    QVariantList data = {idComposition, idQueue};
    return PlaylistComposition::insert(data);
}

void PlaybackQueue::updateNumber(const int idComposition, const int num) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "UPDATE " + tableName
                        + " SET " + rows[2] + " = :num WHERE " + rows[1] +
                        " = :idQueue AND " + rows[0] + " = :idComposition";
    query.prepare(queryText);
    query.bindValue(":num", num);
    query.bindValue(":idQueue", idQueue);
    query.bindValue(":idComposition", idComposition);
    if(!query.exec()) {
        qDebug() << query.lastError().text();
    }
}

void PlaybackQueue::remove(const int idComosition) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE " + rows[1] + " = "
                        + QString::number(idQueue) + " AND " + rows[0] + " = "
                        + QString::number(idComosition);
    query.prepare(queryText);
    if(!query.exec()) {
        qDebug() << query.lastError().text();
    }
}

void PlaybackQueue::clear() {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE " + rows[1] + " = "
                        + QString::number(idQueue);
    query.prepare(queryText);
    if(!query.exec()) {
        qDebug() << query.lastError().text();
    }
}
