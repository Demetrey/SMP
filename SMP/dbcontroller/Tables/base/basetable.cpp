/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "basetable.h"

BaseTable::BaseTable(QString &connectionName) {
    this->connectionName = connectionName;
    tableName = QString(ALBUM);
}

/**
 * @brief Insert
 * @param data - data struct: data[0] - data (String)
 * @return id of the added (maybe earlier) data
 */
int BaseTable::insert(const QVariantList &data) {
    int id = getId(data);
    if (id != -1)
        return id;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "INSERT INTO " + tableName + " (name) " +
            "VALUES (:name)";
    query.prepare(queryText);
    query.bindValue(":name", data[0].toString());
    if(!query.exec()) {
        qDebug() << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

/**
 * @brief Delete data by id
 * @param id - data id to delete
 */
void BaseTable::remove(const int id) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE id = "
                        + QString::number(id);
    query.prepare(queryText);
    if(!query.exec()) {
        qDebug() << "Can't delete with id" << id;
        qDebug() << query.lastError().text();
    }
}

/**
 * @brief Update
 * @param id - updated data id
 * @param data - data struct: data[0] - data (String)
 */
void BaseTable::update(const int id, const QVariantList &data) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "UPDATE " + tableName + " SET name = :name WHERE id = "
                        + QString::number(id);
    query.prepare(queryText);
    query.bindValue(":name", data[0].toString());
    if(!query.exec()) {
        qDebug() << "Can't update with id" << id;
        qDebug() << query.lastError().text();
    }
}

/**
 * @brief Search data id by name
 * @param data - data struct: data[0] - data (String)
 * @return found data id or -1
 */
int BaseTable::getId(const QVariantList &data) const {
    int id = -1;
    QSqlQuery querySelect(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT id FROM " + tableName +
            " WHERE name = :name";
    querySelect.prepare(queryText);
    querySelect.bindValue(":name", data[0].toString());
    if(!querySelect.exec()) {
        return -1;
    }
    else {
        while (querySelect.next()) {
            id = querySelect.value(0).toInt();
            return id;
        }
    }
    return id;
}

/**
 * @brief Get Data by ID
 * @param id - data id
 * @return data
 */
QVariantList BaseTable::getData(int id) const {
    QVariantList result;
    QSqlQuery querySelect(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT name FROM " + tableName +
            " WHERE id = :id";
    querySelect.prepare(queryText);
    querySelect.bindValue(":id", QString::number(id));
    if(querySelect.exec()) {
        while (querySelect.next()) {
            result.append(querySelect.value(0));
        }
    }
    return result;
}
