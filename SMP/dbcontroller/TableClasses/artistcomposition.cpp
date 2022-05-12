#include "artistcomposition.h"

ArtistComposition::ArtistComposition(QString connectionName, QObject *parent) : QObject(parent)
{
    this->_connectionName = connectionName;
}

int ArtistComposition::insert(const QVariantList &data) const
{
    // data struct:
    // data[0] - idComposition
    // data[1] - idArtist
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "INSERT INTO " + tableName + " (" + rows.at(0) + ", " + rows.at(1) + ") " +
            "VALUES (:composition, :artist)";
    query.prepare(queryText);
    query.bindValue(":composition", data[0].toString());
    query.bindValue(":artist", data[1].toString());
    if(!query.exec()){
        return -1;
    }
    return query.lastInsertId().toInt();
}

void ArtistComposition::remove(const int id)
{
}

void ArtistComposition::update(const int id, const QVariantList &data)
{

}

int ArtistComposition::getArtistId(const int id) const
{
    int idArtist = -1;
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "SELECT  " + rows[1] + " FROM " + tableName + " WHERE " + rows[0] + " = " + QString::number(id);
    query.prepare(queryText);
    if(!query.exec()){
        return idArtist;
    }
    else {
        while (query.next()) {
            idArtist = query.value(0).toInt();
            return idArtist;
        }
    }
    return idArtist;

}

int ArtistComposition::getCount(const int id) const
{
    int count = -1;
    QSqlQuery querySelect(QSqlDatabase::database(_connectionName));
    QString queryText = "SELECT COUNT (*) FROM " + tableName +
            " WHERE " + rows.at(1) + " = " + QString::number(id);
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
