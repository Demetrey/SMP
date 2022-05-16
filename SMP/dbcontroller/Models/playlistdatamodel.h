/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef PLAYLISTDATAMODEL_H
#define PLAYLISTDATAMODEL_H

#include "mediamodel.h"

/**
 * @brief The PlaylistDataModel class
 * Модель представления данных композиций в плейлисте
 * Data view of audio files added to a playlist
 */
class PlaylistDataModel : public MediaModel
{
    Q_OBJECT
public:
    explicit PlaylistDataModel(QSqlDatabase db, QObject *parent = nullptr);

public slots:
    void updateModel(const int id, const QString search = QString());
};

#endif // PLAYLISTDATAMODEL_H
