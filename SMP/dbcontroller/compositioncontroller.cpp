/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "compositioncontroller.h"

CompositionController::CompositionController(QString connectionName) {
    album = new Album(connectionName);
    artist = new Artist(connectionName);
    artistComposition = new ArtistComposition(connectionName);
    composition = new Composition(connectionName);
    urlAudio = new UrlAudio(connectionName);
}

CompositionController::~CompositionController() {
    delete album;
    delete artist;
    delete artistComposition;
    delete composition;
    delete urlAudio;
}

/**
 * @brief Insert Composition
 * @param path - Path to composition
 * @param tags - Composition tags
 */
void CompositionController::insertComposition(const QString &path, const Tags *tags) {
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

    emit insertedComposition(compositionId);
    emit changedMedia();
}

/**
 * @brief Delet composition
 * @param id - id of the composition to delete
 */
void CompositionController::deleteComposition(const int id) {
    QVariantList oldData = composition->getData(id);
    if (oldData.isEmpty()) // no data in DB
        return;
    int idAlbum = oldData.at(3).toInt();
    QList<int> idArtists = artistComposition->getIdNonComposition(id);

    composition->remove(id);

    compositionCleanup(idAlbum, idArtists);
    emit deletedComposition(id);
    emit changedMedia();
}

/**
 * @brief Update composition
 * @param id - Composition id to update
 * @param path - Path to composition
 * @param tags - Composition tags
 */
void CompositionController::updateComposition(const int id, const QString &path,
                                     const Tags *tags) {
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

    emit updatedComposition(id);
    emit changedMedia();
}

/**
 * @brief Insert URL
 * @param url - URL \_(^-_-^)_/
 * @param name - Alias ​​for audio source
 */
void CompositionController::insertUrl(const QString &url, const QString &name) {
    QVariantList data = {url, name};
    urlAudio->insert(data);
}

/**
 * @brief Delete URL
 * @param id - id URL to delete
 */
void CompositionController::deleteUrl(const int id) {
    urlAudio->remove(id);
}

/**
 * @brief Update URL
 * @param id - id URL to update
 * @param url - URL \_(^-_-^)_/
 * @param name - Alias ​​for audio source
 */
void CompositionController::updateUrl(const int id, QString &url, const QString &name) {
    QVariantList data = {url, name};
    urlAudio->update(id, data);
}

/**
 * @brief Insert Album
 * @param tags - Tags to extract album title
 * @return - Added Album ID
 */
int CompositionController::insertAlbum(const Tags *tags) {
    QVariantList data = {tags->songAlbum};
    return album->insert(data);
}

/**
 * @brief Insert Artists
 * @param tags - Tags to extract artists
 * @return - List of id added artists
 */
QList<int> CompositionController::insertArtists(const Tags *tags) {
    QVariantList data;
    QList<int> artistId;
    for (const QString &curArtist : tags->songArtists) {
        data.clear();
        data.append(curArtist);
        artistId.append(artist->insert(data));
    }
    return artistId;
}

/**
 * @brief Insert to Artist_Composition
 * @param idComposition - Composition id
 * @param idArtists - Artist id
 * @return true - successful insertion, false - failure
 */
bool CompositionController::insertAC(const int idComposition, const QList<int> &idArtists) {
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

/**
 * @brief Unpaste composition
 * @param idAlbum - Inserted Album ID
 * @param idArtist - IDs of added artists
 * @param idComposition -
 */
void CompositionController::cancelCompositionInsert(const int idAlbum,
                                           const QList<int> *idArtist,
                                           const int idComposition) {
    album->remove(idAlbum);

    if (idArtist) {
        for (const int id : *idArtist) {
            if (id != -1)
                artist->remove(id);
        }
    }
    composition->remove(idComposition);
}

/**
 * @brief Composition cleanup
 * @param idAlbum - Old Album ID
 * @param idAstists - Old Artist IDs
 */
void CompositionController::compositionCleanup(const int idAlbum,
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
