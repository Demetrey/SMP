/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef IPLAYLISTCONTROLLER_H
#define IPLAYLISTCONTROLLER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QList>
#include <QSqlDatabase>

class IPlaylistController : public QObject {
public slots:
    virtual void createPlaylist(const QString& name) = 0;
    virtual void deletePlaylist(const int id) = 0;
    virtual void updatePlaylist(const int id, const QString& name) = 0;

    virtual void insertToPlaylist(const int idPlaylist,
                                  const int idComposition) = 0;
    virtual void removeFromPlaylist(const int idPlaylist,
                                    const int idComposition) = 0;

signals:
    void insertedPlaylist(int id);
    void updatedPlaylist(int id);
    void deletedPlaylist(int id);
    void changedPlaylistData();
    void changedPlaylistStruct(int id);

};


#endif // IPLAYLISTCONTROLLER_H
