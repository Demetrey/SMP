/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playlistdatamodel.h"

PlaylistDataModel::PlaylistDataModel(QSqlDatabase db, QObject *parent)
    : MediaModel(db, parent) {
}

/**
 * @brief Update Model
 * Обновление модели
 * @param id - Playlist ID to display
 * @param search - String to search using the pattern "LIKE %search%", if not empty
 */
void PlaylistDataModel::updateModel(const int id, const QString search) {
    QString queryText  = "select composition.id, compositionPath, compositionName, "
                    "compositionYear, group_concat(artist.name), album.name "
                    "from playlist_composition "
                    "join composition on playlist_composition.idComposition = composition.id "
                    "and  playlist_composition.idPlaylist = " + QString::number(id) +
                    " join artist_composition on composition.id = artist_composition.idComposition "
                    "join artist on idArtist = artist.id "
                    "join album on album.id = idAlbum ";

    if (!search.isEmpty()) {
        queryText += " where compositionName like \"%" + search + "%\" "
                    "or artist.name like \"%" + search + "%\" "
                    "or album.name like \"%" + search + "%\"";
    }

    queryText += " GROUP BY composition.id ORDER BY compositionName";
    this->setQuery(queryText, db);
}
