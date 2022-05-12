/*
 * Контроллер доступа к БД
 */

#ifndef CONNECTIONCONTROLLER_H
#define CONNECTIONCONTROLLER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QList>
#include "dbconnect.h"
#include "TableClasses/playlist.h"
#include "TableClasses/artist.h"
#include "TableClasses/album.h"
#include "TableClasses/composition.h"
#include "TableClasses/artistcomposition.h"
#include "TableClasses/playlistcomposition.h"
#include "Code/TagReader/datastructs.h"

class ConnectionController : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionController(QString connectName, QObject *parent = nullptr);
    ~ConnectionController();

    void dbconnect();
    DBConnect *getDBC();

    Q_INVOKABLE QList<QVariantList> getAllFromPlaylist(const int idPlaylist);

public slots:
    void insertIntoPlaylist(QString name);
    void deleteFromPlaylist(int id);
    void insertComposition(QString path, Tags *tags);
    void deleteComposition(int id);
    void addToPlaylist(const QList<int> &compositionIds, int idPlaylist);
    void removeFromPlaylist(int idComposition, int idPlaylist);
    void createPlayQueue(int idPlaylist);

signals:
    void deleteComplete();

private:
    DBConnect *_dbc;
    PlayList *_playlist;
    Album *_album;
    Artist *_artist;
    Composition *_composition;
    ArtistComposition *_artistComposition;
    PlaylistComposition *_playlistComposition;
    int _current_playlist;

};

#endif // CONNECTIONCONTROLLER_H
