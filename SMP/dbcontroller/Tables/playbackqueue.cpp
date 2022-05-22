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

/**
 * @brief Insert composition to queue
 * @param idComposition - composition id
 * @return true - true - success, false - failure
 */
bool PlaybackQueue::insert(const int idComposition) {
    QVariantList data = {idComposition, idQueue};
    return PlaylistComposition::insert(data);
}

/**
 * @brief Update queue number
 * @param idComposition - composition id
 * @param num - new number
 */
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

/**
 * @brief Remove composition from queue
 * @param idComosition - composition id
 */
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

/**
 * @brief Clear queue
 */
void PlaybackQueue::clear() {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE " + rows[1] + " = "
                        + QString::number(idQueue);
    query.prepare(queryText);
    if(!query.exec()) {
        qDebug() << query.lastError().text();
    }
}
