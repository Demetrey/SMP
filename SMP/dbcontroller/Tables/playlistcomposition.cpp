/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playlistcomposition.h"

PlaylistComposition::PlaylistComposition(QString &connectionName) :
    BaseManyToMany(connectionName) {
    this->tableName = QString(PLAYLIST_COMPOSITION);
    this->rows.append("idComposition");
    this->rows.append("idPlaylist");
}

void PlaylistComposition::removeFromPlaylist(const int idPlaylist,
                                             const int idComposition) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "DELETE FROM " + tableName +
            " WHERE " + rows.at(0) + " = :idComposition, " + rows.at(1) + " = :idPLaylist";
    query.prepare(queryText);
    query.bindValue(":idComposition", QString::number(idComposition));
    query.bindValue(":idPLaylist", QString::number(idPlaylist));
    if(!query.exec()) {
        qDebug() << "Can't delete composition_playlist with IDPlaylist: "
                    << idPlaylist << "; IDComposition: " << idComposition;
        qDebug() << query.lastError().text();
    }
}
