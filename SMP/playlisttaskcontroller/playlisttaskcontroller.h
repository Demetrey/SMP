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
