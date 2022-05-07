/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "urlaudio.h"

UrlAudio::UrlAudio(QString &connectionName) {
    this->connectionName = connectionName;
    tableName = QString(URL_AUDIO);
}

int UrlAudio::insert(const QVariantList &data) {
    int id = getId(data);
    if (id != -1)
        return id;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "INSERT INTO " + tableName +
            " (" + rows.at(1) + ", " + rows.at(2) + ") " +
            "VALUES (:link, :name)";
    query.prepare(queryText);
    query.bindValue(":link", data[0].toString());
    query.bindValue(":name", data[1].toString());
    if(!query.exec()) {
        qDebug() << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

void UrlAudio::remove(const int id) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE id = "
                        + QString::number(id);
    query.prepare(queryText);
    if(!query.exec()) {
        qDebug() << "Can't delete composition with id" << id;
        qDebug() << query.lastError().text();
    }
}

void UrlAudio::update(const int id, const QVariantList &data) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "UPDATE " + tableName +
            " SET " + rows.at(1) + " = :link, " + rows.at(2) + " = :name WHERE id = :id";
    query.prepare(queryText);
    query.bindValue(":id", QString::number(id));
    query.bindValue(":link", data[0].toString());
    query.bindValue(":name", data[1].toString());
    if(!query.exec()) {
        qDebug() << "Can't update composition with ID: " << id;
        qDebug() << query.lastError().text();
    }
}

int UrlAudio::getId(const QVariantList &data) const {
    int id = -1;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT id FROM " + tableName +
            " WHERE " + rows.at(1) + " = :link AND " + rows.at(2) + " = :name";
    query.prepare(queryText);
    query.bindValue(":link", data[0].toString());
    query.bindValue(":name", data[1].toString());
    if(!query.exec()) {
        qDebug() << query.lastError().text();
    }
    else {
        while (query.next()) {
            id = query.value(0).toInt();
            return id;
        }
    }
    return id;
}
