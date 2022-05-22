/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */


#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "base/basetable.h"

/**
 * @brief The Album class
 * Класс реализует работу с таблицей PLAYLIST
 * The class implements work with the PLAYLIST table
 */
class Playlist : public BaseTable
{
public:
    Playlist(QString &connectionName);
};

#endif // PLAYLIST_H
