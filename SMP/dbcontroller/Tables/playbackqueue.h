/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef PLAYBACKQUEUE_H
#define PLAYBACKQUEUE_H

#include "playlistcomposition.h"

/**
 * @brief The Album class
 * Класс реализует работу с таблицей PLAYLIST_COMPOSITION (idPlaylist 0)
 * The class implements work with the PLAYLIST_COMPOSITION table (idPlaylist 0)
 */
class PlaybackQueue : private PlaylistComposition
{
public:
    PlaybackQueue(QString &connectionName);

    bool insert(const int idComposition);
    void updateNumber(const int idCompositio, const int num);
    void remove(const int idComosition);
    void clear();

private:
    int idQueue = 0;
};

#endif // PLAYBACKQUEUE_H
