#ifndef IDBCONTROLLER_H
#define IDBCONTROLLER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QList>
#include <QSqlDatabase>
#include "tagreader/tagstructs.h"

class IDBController : public QObject {
public:
    virtual void connect() = 0;
    virtual QSqlDatabase getDB() = 0;

public slots:
    virtual void insertComposition(const QString& path, const Tags* tags) = 0;
    virtual void deleteComposition(const int id) = 0;
    virtual void updateComposition(const int id, const QString& path,
                                   const Tags* tags) = 0;

    virtual void insertUrl(const QString& url, const QString& name) = 0;
    virtual void deleteUrl(const int id) = 0;
    virtual void updateUrl(const int id, QString& url, const QString& name) = 0;

    virtual void createPlaylist(const QString& name) = 0;
    virtual void deletePlaylist(const int id) = 0;
    virtual void updatePlaylist(const int id, const QString& name) = 0;

    virtual void insertToPlaylist(const int idPlaylist,
                                  const int idComposition) = 0;
    virtual void removeFromPlaylist(const int idPlaylist,
                                    const int idComposition) = 0;

    virtual void insertToQueue(const int id) = 0;
    virtual void removeFromQueue(const int id) = 0;
    virtual void updateQueueumbers(const int idComposition,
                                   const int number) = 0;

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
};

#endif // IDBCONTROLLER_H
