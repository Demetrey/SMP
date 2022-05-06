#include "playlistcomposition.h"

PlaylistComposition::PlaylistComposition(QString &connectionName) :
    BaseManyToMany(connectionName) {
    this->tableName = QString(PLAYLIST_COMPOSITION);
    this->rows.append("idComposition");
    this->rows.append("idPlaylist");
}
