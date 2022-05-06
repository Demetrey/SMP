/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "composition.h"

Composition::Composition(QString &connectionName) {
    this->connectionName = connectionName;
    this->tableName = QString(COMPOSITION);
}

int Composition::insert(const QVariantList &data) const {
    int id = getId(data);
    if (id != -1)
        return id;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "INSERT INTO " + tableName +
            " (" + rows.at(1) + ", " + rows.at(2) + ", " + rows.at(3) + ", " + rows.at(4) + ") " +
            "VALUES (:path, :name, :year, :albumname)";
    query.prepare(queryText);
    query.bindValue(":path", data[0].toString());
    query.bindValue(":name", data[1].toString());
    query.bindValue(":year", data[2].toInt());
    query.bindValue(":albumname", data[3].toInt());
    if(!query.exec()) {
        qDebug() << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

void Composition::remove(const int id) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE id = "
                        + QString::number(id);
    query.prepare(queryText);
    if(!query.exec()) {
        qDebug() << "Can't delete composition with id" << id;
        qDebug() << query.lastError().text();
    }
}

void Composition::update(const int id, const QVariantList &data) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "UPDATE " + tableName +
            " SET " + rows.at(1) + " = :path, " + rows.at(2) + " = :name, "
            + rows.at(3) + " = :year, " + rows.at(4) + " = :albumname WHERE id = "
            + QString::number(id);
    query.prepare(queryText);
    query.bindValue(":path", data[0].toString());
    query.bindValue(":name", data[1].toString());
    query.bindValue(":year", data[2].toInt());
    query.bindValue(":albumname", data[3].toInt());
    if(!query.exec()) {
        qDebug() << "Can't update composition with ID: " << id;
        qDebug() << query.lastError().text();
    }
}

int Composition::getId(const QVariantList &data) const {
    int id = -1;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT id FROM " + tableName +
            " WHERE " + rows.at(1) + " = :path AND " + rows.at(2) + " = :name AND "
            + rows.at(3) + " = :year AND " + rows.at(4) + "= :albumname";
    query.prepare(queryText);
    query.bindValue(":path", data[0].toString());
    query.bindValue(":name", data[1].toString());
    query.bindValue(":year", data[2].toInt());
    query.bindValue(":albumname", data[3].toInt());
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

QVariantList Composition::getData(const int id) const {
    QVariantList result;
    QSqlQuery querySelect(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT " + rows.at(1) + ", " + rows.at(2) + ", "
                        + rows.at(3) + ", " + rows.at(4) + " FROM " + tableName +
            " WHERE id = :id";
    querySelect.prepare(queryText);
    querySelect.bindValue(":id", QString::number(id));
    if(querySelect.exec()) {
        while (querySelect.next()) {
            result.append(querySelect.value(0));
            result.append(querySelect.value(1));
            result.append(querySelect.value(2));
            result.append(querySelect.value(3));
        }
    }
    return result;
}

int Composition::getAlbumCount(const int id) const {
    int count = -1;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT COUNT (*) FROM " + tableName +
            " WHERE " + rows.at(4) + " = :id";
    query.prepare(queryText);
    query.bindValue(":id", QString::number(id));
    if(query.exec()) {
        while (query.next()) {
            return query.value(0).toInt();
        }
    }
    return count;
}
