/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include "basecontroller.h"
#include "Interfaces/IPlaylistController.h"
#include "Tables/playlist.h"
#include "Tables/playlistcomposition.h"

/**
 * @brief The PlaylistController class
 * Контроллер доступа к данным плейлистов.
 * Предоставляет методы для добавления, удаления, изменения данных плейлистов,
 * в том числе их содержимого.
 * Controller for accessing playlist data.
 * Provides methods for adding, removing, modifying playlist data, including
 * their content.
 */
class PlaylistController : public IPlaylistController
{
    Q_OBJECT
public:
    PlaylistController(QString connectionName);
    ~PlaylistController();

signals:
    // IPlaylistController interface
    void insertedPlaylist(int id);
    void updatedPlaylist(int id);
    void deletedPlaylist(int id);
    void changedPlaylists();
    void changedPlaylistStruct(int id);

public slots:
    // IPlaylistController interface
    void createPlaylist(const QString &name) override;
    void deletePlaylist(const int id) override;
    void updatePlaylist(const int id, const QString &name) override;

    void insertToPlaylist(const int idPlaylist, const int idComposition) override;
    void removeFromPlaylist(const int idPlaylist, const int idComposition) override;

private:
    Playlist *playlist;
    PlaylistComposition *playlistComposition;
};

#endif // PLAYLISTCONTROLLER_H
