/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef PLAYLISTCOMPOSITION_H
#define PLAYLISTCOMPOSITION_H

#include "base/basemanytomany.h"

/**
 * @brief The Album class
 * Класс реализует работу с таблицей PLAYLIST_COMPOSITION
 * The class implements work with the PLAYLIST_COMPOSITION table
 */
class PlaylistComposition : public BaseManyToMany
{
public:
    PlaylistComposition(QString &connectionName);
    void removeFromPlaylist(const int idPlaylist, const int idComposition);

};

#endif // PLAYLISTCOMPOSITION_H
