#include "dbcontroller.h"

DBController::DBController(QString& connectionName) {
    dbc = new DBConnect(connectionName);
    album = new Album(connectionName);
    artist = new Artist(connectionName);
    artistComposition = new ArtistComposition(connectionName);
    composition = new Composition(connectionName);
    plqyQueue = new PlaybackQueue(connectionName);
    playlist = new Playlist(connectionName);
    playlistComposition = new PlaylistComposition(connectionName);
    urlAudio = new UrlAudio(connectionName);
}

DBController::~DBController() {
    delete dbc;
    delete album;
    delete artist;
    delete artistComposition;
    delete composition;
    delete plqyQueue;
    delete playlist;
    delete playlistComposition;
    delete urlAudio;
}

void DBController::connect() {
    dbc->connect();
}

QSqlDatabase DBController::getDB() {
    return dbc->getDB();
}

void DBController::insertComposition(const QString &path, const Tags *tags) {
    QVariantList data;
    // Insert album
    int albumId = insertAlbum(tags);
    if (albumId == -1) {
        qDebug() << "Can't add album!";
        return;
    }

    // Insert artist
    QList<int> artistId = insertArtists(tags);
    for (int i = 0; i < artistId.size(); i++) {
        if (artistId.at(i) == -1) {
            artistId.removeAt(i);
            i--;
        }
    }

    if (!artistId.length()) {
        qDebug() << "Can't add artists!";
        cancelCompositionInsert(albumId);
    }

    // InsertComposition
    data.clear();
    data.append(path);
    data.append(tags->songName);
    data.append(static_cast<int>(tags->songYear));
    data.append(albumId);
    if (composition->getId(data) != -1) {
        qDebug() << "Already exists";
        return;
    }
    qDebug() << data;
    int compositionId = composition->insert(data);
    if (compositionId == -1) {
        qDebug() << "Can't add composition!";
        cancelCompositionInsert(albumId, &artistId);
        return;
    }

    // Insert many-to-many artist_composition
    if (!insertAC(compositionId, artistId)) {
        qDebug() << "Can't add artist_composition!";
        cancelCompositionInsert(albumId, &artistId, compositionId);
    }
}

void DBController::deleteComposition(const int id) {
    QVariantList oldData = composition->getData(id);
    int idAlbum = oldData.at(3).toInt();
    QList<int> idArtists = artistComposition->getIdNonComposition(id);

    composition->remove(id);

    compositionCleanup(idAlbum, idArtists);
}

void DBController::updateComposition(const int id, const QString &path, const Tags *tags) {
    QVariantList oldData = composition->getData(id);
    // save old data from other tables
    int idAlbum = oldData.at(3).toInt();
    QList<int> oldArtists = artistComposition->getIdNonComposition(id);

    // insert new album (or get old id)
    int albumId = insertAlbum(tags);
    if (albumId == -1) {
        qDebug() << "Can't add album!";
        return;
    }

    // Insert artist
    QList<int> artistId = insertArtists(tags);
    for (int i = 0; i < artistId.size(); i++) {
        if (artistId.at(i) == -1) {
            artistId.removeAt(i);
            i--;
        }
    }

    if (!artistId.length()) {
        qDebug() << "Can't add artists!";
        cancelCompositionInsert(albumId);
    }

    // update composition
    // InsertComposition
    QVariantList data;
    data.append(path);
    data.append(tags->songName);
    data.append(tags->songYear);
    data.append(albumId);
    composition->update(id, data);

    // add M2M
    insertAC(id, artistId);

    compositionCleanup(idAlbum, oldArtists);
}

void DBController::insertUrl(const QString &url, const QString &name)
{

}

void DBController::deleteUrl(const int id)
{

}

void DBController::updateUrl(const int id, QString &url, const QString &name)
{

}

void DBController::createPlaylist(const QString &name)
{

}

void DBController::deletePlaylist(const int id)
{

}

void DBController::updatePlaylist(const int id, const QString &name)
{

}

void DBController::insertToPlaylist(const int idPlaylist, const int idComposition)
{

}

void DBController::removeFromPlaylist(const int idPlaylist, const int idComposition)
{

}

void DBController::insertToQueue(const int id)
{

}

void DBController::removeFromQueue(const int id)
{

}

void DBController::updateQueueumbers(const int idComposition, const int number)
{

}

int DBController::insertAlbum(const Tags *tags) {
    QVariantList data = {tags->songAlbum};
    return album->insert(data);
}

QList<int> DBController::insertArtists(const Tags *tags) {
    QVariantList data;
    QList<int> artistId;
    for (const QString &curArtist : tags->songArtists) {
        data.clear();
        data.append(curArtist);
        artistId.append(artist->insert(data));
    }
    return artistId;
}

bool DBController::insertAC(const int idComposition, const QList<int> &idArtists) {
    QVariantList data;
    bool isOk = false; // can't add
    data.clear();
    data.append(idComposition);
    data.append(0);
    for (const int id : idArtists) {
        if (id != -1) {
            data[1] = id;
            if (artistComposition->insert(data)) {
                isOk = true;
            }
        }
    }
    return isOk;
}

void DBController::cancelCompositionInsert(const int idAlbum,
                                           const QList<int> *idArtist,
                                           const int idComposition) {
    album->remove(idAlbum);

    for (const int id : *idArtist) {
        if (id != -1)
            artist->remove(id);
    }

    composition->remove(idComposition);
}

void DBController::compositionCleanup(const int idAlbum,
                                      const QList<int> &idAstists) {
    // Deleting unused albums
    if (composition->getAlbumCount(idAlbum) == 0) {
        album->remove(idAlbum);
    }
    // Removing unused artists
    for (const int idArtist : qAsConst(idAstists)) {
        if (!artistComposition->getIdComposition(idArtist).length()) {
            artist->remove(idArtist);
        }
    }
}
