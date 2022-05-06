#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include "dbconnect.h"
#include "idbcontroller.h"
#include "Tables/album.h"
#include "Tables/artist.h"
#include "Tables/artistcomposition.h"
#include "Tables/composition.h"
#include "Tables/playbackqueue.h"
#include "Tables/playlist.h"
#include "Tables/playlistcomposition.h"
#include "Tables/urlaudio.h"

class DBController : public IDBController
{
    Q_OBJECT
public:
    explicit DBController(QString &connectionName);
    ~DBController();

signals:
    void insertedComposition(int id);
    void deletedComposition(int id);
    void updatedComposition(int id);
    void changedMedia();

    void insertedPlaylist(int id);
    void updatedPlaylist(int id);
    void deletedPlaylist(int id);
    void changedPlaylistData();

    void changedPlaylistStruct(int id);

    void changedQueue();

    // IDBController interface
public:
    void connect() override;
    QSqlDatabase getDB() override;

public slots:
    void insertComposition(const QString &path, const Tags *tags) override;
    void deleteComposition(const int id) override;
    void updateComposition(const int id, const QString &path, const Tags *tags) override;

    void insertUrl(const QString &url, const QString &name) override;
    void deleteUrl(const int id) override;
    void updateUrl(const int id, QString &url, const QString &name) override;

    void createPlaylist(const QString &name) override;
    void deletePlaylist(const int id) override;
    void updatePlaylist(const int id, const QString &name) override;

    void insertToPlaylist(const int idPlaylist, const int idComposition) override;
    void removeFromPlaylist(const int idPlaylist, const int idComposition) override;

    void insertToQueue(const int id) override;
    void removeFromQueue(const int id) override;
    void updateQueueumbers(const int idComposition, const int number) override;

private:
    DBConnect *dbc;
    Album *album;
    Artist *artist;
    ArtistComposition *artistComposition;
    Composition *composition;
    PlaybackQueue *plqyQueue;
    Playlist *playlist;
    PlaylistComposition *playlistComposition;
    UrlAudio *urlAudio;

    int insertAlbum(const Tags *tags);
    QList<int> insertArtists(const Tags *tags);
    bool insertAC(const int idComposition, const QList<int> &idArtists);
    void cancelCompositionInsert(const int idAlbum,
                                 const QList<int> *idArtist = nullptr,
                                 const int idComposition = 0);
    void compositionCleanup(const int idAlbum, const QList<int> &idAstists);
};

#endif // DBCONTROLLER_H
