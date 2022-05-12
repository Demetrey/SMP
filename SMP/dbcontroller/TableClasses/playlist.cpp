#include "playlist.h"

PlayList::PlayList(QString connectionName, QObject *parent) : QObject(parent)
{
    this->_connectionName = connectionName;
}

int PlayList::insert(const QVariantList &data) const
{
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

void PlayList::remove(const int id)
{
    if (id == 0)
        return;
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE " + rows[0] + " = " + QString::number(id);
    query.prepare(queryText);
    if(!query.exec()){
        return;
    }
}

void PlayList::update(const int id, const QVariantList &data)
{

}

