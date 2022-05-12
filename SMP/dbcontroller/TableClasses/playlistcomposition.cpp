#include "playlistcomposition.h"

PlaylistComposition::PlaylistComposition(QString connectionName, QObject *parent) : QObject(parent)
{
    this->_connectionName = connectionName;
}

int PlaylistComposition::insert(const QVariantList &data) const
{
    // data struct:
    // data[0] - idComposition
    // data[1] - idPlaylist
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "INSERT INTO " + tableName + " (" + rows.at(0) + ", " + rows.at(1) + ") " +
            "VALUES (:composition, :playlist)";
    query.prepare(queryText);
    query.bindValue(":composition", data[0].toString());
    query.bindValue(":playlist", data[1].toString());
    if(!query.exec()){
        return -1;
    }
    return query.lastInsertId().toInt();
}

void PlaylistComposition::remove(const int id)
{
}

void PlaylistComposition::update(const int id, const QVariantList &data)
{

}

void PlaylistComposition::removeFromPlaylist(const int idComposition, const int idPlaylist)
{
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "DELETE FROM " + tableName +
            " WHERE " + rows[0] + " = " + QString::number(idComposition) +
            " AND "  + rows[1] + " = " + QString::number(idPlaylist);
    query.prepare(queryText);
    if(!query.exec()){
        return;
    }
}

void PlaylistComposition::clearPlayQueue(const int idPlaylist)
{
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "DELETE FROM " + tableName +
            " WHERE " + rows[1] + " = " + QString::number(idPlaylist);
    query.prepare(queryText);
    if(!query.exec()){
        return;
    }
}

QList<int> PlaylistComposition::getAllIds(const int idPlaylist)
{
    QList<int> ids;
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    QString queryText = "SELECT " + rows.at(0) + " FROM " + tableName +
            " WHERE " + rows.at(1) + " = " + QString::number(idPlaylist);
    query.prepare(queryText);
    if(!query.exec()){
        return ids;
    }
    while (query.next()) {
        ids.append(query.value(0).toInt());
    }
    return ids;
}

QList<QVariantList> PlaylistComposition::getAllFromPlaylist(const int idPlaylist)
{
    QList<QVariantList> res;
    QString queryText = "select composition.id, compositionName, "
"compositionPath, artist.name "
"from playlist_composition "
"join composition on composition.id = playlist_composition.idComposition "
"join artist_composition on artist_composition.idComposition = composition.id "
"join artist on artist.id = idArtist where idPlaylist = " + QString::number(idPlaylist)
            + " order by compositionName";
    QSqlQuery query(QSqlDatabase::database(_connectionName));
    query.prepare(queryText);
    if(!query.exec()){
        return res;
    }
    while (query.next()) {
        QVariantList item;
        item.append(query.value(0).toInt());
        item.append(query.value(1).toString());
        item.append(query.value(2).toString());
        item.append(query.value(3).toString());
        res.append(item);
    }
    return res;
}
