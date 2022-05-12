#include "connectioncontroller.h"

ConnectionController::ConnectionController(QString connectName, QObject *parent) : QObject(parent)
{
    this->_dbc = new DBConnect(connectName);
    this->_playlist = new PlayList(connectName);
    this->_album = new Album(connectName);
    this->_artist = new Artist(connectName);
    this->_artistComposition = new ArtistComposition(connectName);
    this->_composition = new Composition(connectName);
    this->_playlistComposition = new PlaylistComposition(connectName);
    this->_current_playlist = -2;
}

ConnectionController::~ConnectionController()
{
    delete _playlist;
    delete _album;
    delete _artist;
    delete _artistComposition;
    delete _composition;
    delete _playlistComposition;
    delete _dbc;
}

void ConnectionController::dbconnect()
{
    _dbc->connect();
}

DBConnect *ConnectionController::getDBC()
{
    return this->_dbc;
}

void ConnectionController::insertIntoPlaylist(QString name)
{
    QVariantList data;
    data.append(name);
    _playlist->insert(data);
}

void ConnectionController::deleteFromPlaylist(int id)
{
    _playlist->remove(id);
    emit deleteComplete();
}

void ConnectionController::insertComposition(QString path, Tags *tags)
{
    QVariantList dataArtist;


    QStringList artists = tags->artist.split("/");
    QList<int> idsArtists;
    for (QString a : artists) {
        qDebug() << "UPPEND ARTIST" << a;
        dataArtist.append(a);
        idsArtists.append(_artist->insert(dataArtist));
        dataArtist.clear();
        /*if (idArtist == -1) {
            return;
        }*/
    }


    /*dataArtist.append(tags->artist);
    int idArtist = _artist->insert(dataArtist);
    if (idArtist == -1) {
        return;
    }*/

    QVariantList dataAlbum;
    dataAlbum.append(tags->album);
    int idAlbum = _album->insert(dataAlbum);
    if (idAlbum == -1) {
        return;
    }

    // Composition data struct:
    // data[0] - compositionPath
    // data[1] - compositionName
    // data[2] - compositionYear
    // data[3] - idAlbum
    QVariantList dataComposition;
    dataComposition.append(path);
    dataComposition.append(tags->song_name);
    dataComposition.append(tags->year);
    dataComposition.append(idAlbum);
    int idComposition = _composition->insert(dataComposition);
    if (idComposition == -1) {
        return;
    }

    // data struct:
    // data[0] - idComposition
    // data[1] - idArtist
    /*QVariantList dataArtistComposition;
    dataArtistComposition.append(idComposition);
    dataArtistComposition.append(idArtist);
    _artistComposition->insert(dataArtistComposition);*/


    for (int idArtist : idsArtists) {
        qDebug() << "UPPEND ARTIST_COMPOSITION" << idArtist;
        QVariantList dataArtistComposition;
        dataArtistComposition.append(idComposition);
        dataArtistComposition.append(idArtist);
        _artistComposition->insert(dataArtistComposition);
    }

}

void ConnectionController::deleteComposition(int id)
{
    int idArtist = _artistComposition->getArtistId(id);
    int idAlbum = _composition->getAlbum(id);
    _composition->remove(id);
    if (idAlbum != -1) {
        int albumCount = _composition->getAlbumCount(idAlbum);
        if (albumCount == 0) {
            _album->remove(idAlbum);
        }
    }
    if (idArtist != -1) {
        int artistCount = _artistComposition->getCount(idArtist);
        if (artistCount == 0) {
            _artist->remove(idArtist);
        }
    }
    emit deleteComplete();
}

void ConnectionController::addToPlaylist(const QList<int> &compositionIds, int idPlaylist)
{
    for (int idComposition : compositionIds) {
        QVariantList compositionData;
        compositionData.append(idComposition);
        compositionData.append(idPlaylist);
        _playlistComposition->insert(compositionData);
    }
}

void ConnectionController::removeFromPlaylist(int idComposition, int idPlaylist)
{
    _playlistComposition->removeFromPlaylist(idComposition, idPlaylist);
    emit deleteComplete();
}

void ConnectionController::createPlayQueue(int idPlaylist)
{
    // 0 - плейлист очереди воспроизведения
    if (idPlaylist == 0) {
        return;
    }
    if (idPlaylist == _current_playlist) {
        return;
    }
    else {
        _current_playlist = idPlaylist;
    }
    QList<int> ids;
    _playlistComposition->clearPlayQueue();

    if (idPlaylist == -1) {
        // Медиатека, добавить все файлы медиатеки в плейлист очереди
        ids = _composition->getAllId();
    }
    else {
        // Другие плейлисты, добавить все файлы этого плейлиста в очередь
        ids = _playlistComposition->getAllIds(idPlaylist);
    }
    addToPlaylist(ids, 0);
}

QList<QVariantList> ConnectionController::getAllFromPlaylist(const int idPlaylist)
{
    return _playlistComposition->getAllFromPlaylist(idPlaylist);
}
