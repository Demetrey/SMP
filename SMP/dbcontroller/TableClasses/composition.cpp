#include "composition.h"

Composition::Composition(QString connectionName, QObject *parent) : QObject(parent)
{
    this->_connectionName = connectionName;
}

int Composition::insert(const QVariantList &data) const
{
    // data struct:
    // data[0] - compositionPath
    // data[1] - compositionName
    // data[2] - compositionYear
    // data[3] - idAlbum
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "INSERT INTO " + tableName +
            " (" + rows.at(1) + ", " + rows.at(2) + ", " + rows.at(3) + ", " + rows.at(4) + ") " +
            "VALUES (:path, :name, :year, :albumname)";
    query.prepare(queryText);
    query.bindValue(":path", data[0].toString());
    query.bindValue(":name", data[1].toString());
    query.bindValue(":year", data[2].toInt());
    query.bindValue(":albumname", data[3].toInt());
    if(!query.exec()){
        return -1;
    }
    return query.lastInsertId().toInt();
}

void Composition::remove(const int id)
{
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "DELETE FROM " + tableName + " WHERE " + rows[0] + " = " + QString::number(id);
    query.prepare(queryText);
    if(!query.exec()){
        return;
    }
}

void Composition::update(const int id, const QVariantList &data)
{

}

int Composition::getAlbum(const int id) const
{
    // Сохраним id альбома композиции
    int idAlbum = -1;
    QSqlQuery querySelect(QSqlDatabase::database(_connectionName));
    QString queryText = "SELECT " + rows.at(4) + " FROM " + tableName +
            " WHERE " + rows.at(0) + " = " + QString::number(id);
    querySelect.prepare(queryText);
    if(!querySelect.exec()){
        return -1;
    }
    else {
        while (querySelect.next()) {
            idAlbum = querySelect.value(0).toInt();
            return idAlbum;
        }
    }
    return idAlbum;
}

int Composition::getAlbumCount(const int id) const
{
    int count = -1;
    QSqlQuery querySelect(QSqlDatabase::database(_connectionName));
    QString queryText = "SELECT COUNT (*) FROM " + tableName +
            " WHERE " + rows.at(4) + " = " + QString::number(id);
    querySelect.prepare(queryText);
    if(!querySelect.exec()){
        return count;
    }
    else {
        while (querySelect.next()) {
            count = querySelect.value(0).toInt();
            return count;
        }
    }
    return count;
}

QList<int> Composition::getAllId()
{
    QList<int> ids;
    QSqlQuery querySelect(QSqlDatabase::database(_connectionName));
    QString queryText = "SELECT id FROM " + tableName;
    querySelect.prepare(queryText);
    if(!querySelect.exec()){
        return ids;
    }
    while (querySelect.next()) {
        ids.append(querySelect.value(0).toInt());
    }
    return ids;
}
