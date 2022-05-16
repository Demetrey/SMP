/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef PLAYLISTTASKCONTROLLER_H
#define PLAYLISTTASKCONTROLLER_H

#include <QObject>
#include <QThreadPool>
#include <QDebug>

#include "inserttopltask.h"

class PlaylistTaskController : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistTaskController(QObject *parent = nullptr);

public slots:
    void insertToPlaylist(QList<int> ids, int id);

    void onInsertFinished();

signals:
    void startInPlaylistAdding();
    void endInPlaylistAdding();

};

#endif // PLAYLISTTASKCONTROLLER_H
