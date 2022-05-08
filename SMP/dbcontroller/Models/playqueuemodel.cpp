/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playqueuemodel.h"

PlayQueueModel::PlayQueueModel(QSqlDatabase db, QObject *parent)
    : MediaModel(db, parent) {
}

/**
 * @brief Update model
 * @param isSorted - true - display queue sorted by number (to display the
 * current queue when shuffling); false - display the queue in alphabetical
 * order (by composition title)
 * @param search - String to search using the pattern "LIKE %search%", if not empty
 */
void PlayQueueModel::updateModel(bool isSorted, const QString search) {
    QString queryText  = "select composition.id, compositionPath, compositionName, "
                    "compositionYear, group_concat(artist.name), album.name "
                    "from playlist_composition "
                    "join composition on playlist_composition.idComposition = composition.id "
                    "and  playlist_composition.idPlaylist = 0 "
                    "join artist_composition on composition.id = artist_composition.idComposition "
                    "join artist on idArtist = artist.id "
                    "join album on album.id = idAlbum ";

    if (!search.isEmpty()) {
        queryText += " where compositionName like \"%" + search + "%\" "
                    "or artist.name like \"%" + search + "%\" "
                    "or album.name like \"%" + search + "%\"";
    }

    queryText += " ORDER BY ";
    if (isSorted) {
        queryText += "number";
    }
    else {
        queryText += "compositionName";
    }
    this->setQuery(queryText, db);
}
