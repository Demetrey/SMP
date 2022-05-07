/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playlistcontroller.h"

PlaylistController::PlaylistController(QString connectionName)
    : BaseController(connectionName) {
    playlist = new Playlist(connectionName);
    playlistComposition = new PlaylistComposition(connectionName);
}

PlaylistController::~PlaylistController() {
    delete playlist;
    delete playlistComposition;
}

/**
 * @brief Insert playlist
 * @param name - Playlist name
 */
void PlaylistController::createPlaylist(const QString &name) {
    QVariantList data = {name};
    int id = playlist->insert(data);
    emit insertedPlaylist(id);
    emit changedPlaylists();
}

/**
 * @brief Delete playlist
 * @param id - playlist id
 */
void PlaylistController::deletePlaylist(const int id) {
    playlist->remove(id);
    emit deletedPlaylist(id);
    emit changedPlaylists();
}

/**
 * @brief Update Playlist
 * @param id - playlist id
 * @param name - Playlist name
 */
void PlaylistController::updatePlaylist(const int id, const QString &name) {
    QVariantList data = {name};
    playlist->update(id, data);
    emit updatedPlaylist(id);
    emit changedPlaylists();
}

/**
 * @brief Insert composition To Playlist
 * @param idPlaylist - playlist id
 * @param idComposition  - composition id
 */
void PlaylistController::insertToPlaylist(const int idPlaylist, const int idComposition) {
    QVariantList data = {idComposition, idPlaylist};
    playlistComposition->insert(data);
    emit changedPlaylistStruct(idPlaylist);
}

/**
 * @brief Remove from playlist
 * @param idPlaylist - playlist id
 * @param idComposition  - composition id
 */
void PlaylistController::removeFromPlaylist(const int idPlaylist, const int idComposition) {
    playlistComposition->removeFromPlaylist(idPlaylist, idComposition);
    emit changedPlaylistStruct(idPlaylist);
}
