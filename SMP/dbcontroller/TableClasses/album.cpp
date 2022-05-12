#include "album.h"

Album::Album(QString connectionName, QObject *parent) : QObject(parent)
{
    this->_connectionName = connectionName;
}

int Album::insert(const QVariantList &data) const
{
    int id = checkId(data);
    if (id != -1)
        return id;

    // data struct:
    // data[0] - name
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "INSERT INTO " + tableName + " (" + rows.at(1) + ") " +
            "VALUES (:name)";
    query.prepare(queryText);
    query.bindValue(":name", data[0].toString());
    if(!query.exec()){
        return -1;
    }
    return query.lastInsertId().toInt();
}

void Album::remove(const int id)
{
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE " + rows[0] + " = " + QString::number(id);
    query.prepare(queryText);
    if(!query.exec()){
        return;
    }
}

void Album::update(const int id, const QVariantList &data)
{
}

int Album::checkId(const QVariantList &data) const
{
    int id = -1;
    // Проверяем, что у нас есть добавляемый альбом
    QSqlQuery querySelect(QSqlDatabase::database(_connectionName));
    QString queryText = "SELECT " + rows.at(0) + " FROM " + tableName +
            " WHERE " + rows.at(1) + " = :name";
    querySelect.prepare(queryText);
    querySelect.bindValue(":name", data[0].toString());
    if(!querySelect.exec()){
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
