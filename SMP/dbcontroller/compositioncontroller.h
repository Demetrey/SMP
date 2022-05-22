/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef COMPOSITIONCONTROLLER_H
#define COMPOSITIONCONTROLLER_H

#include "basecontroller.h"
#include "Interfaces/ICompositionController.h"
#include "Tables/album.h"
#include "Tables/artist.h"
#include "Tables/artistcomposition.h"
#include "Tables/composition.h"
#include "Tables/urlaudio.h"

/**
 * @brief The CompositionController class
 * Класс - контроллер доступа к записям композиций.
 * Представляет методы для добавления, удаления, изменения данных композиций и
 * URL-источников.
 * Class - controller of access to composition records.
 * Represents methods for adding, removing, modifying song data and URL sources.
 */
class CompositionController
        : public ICompositionController
{
    Q_OBJECT
public:
    CompositionController(QString connectionName);
    ~CompositionController();

signals:
    // ICompositionController interface
    void insertedComposition(int id);
    void deletedComposition(int id);
    void updatedComposition(int id);
    void changedMedia();

public slots:
    // ICompositionController interface
    void insertComposition(const QString &path, const Tags *tags) override;
    void deleteComposition(const int id) override;
    void updateComposition(const int id, const QString &path, const Tags *tags) override;

    void insertUrl(const QString &url, const QString &name) override;
    void deleteUrl(const int id) override;
    void updateUrl(const int id, QString &url, const QString &name) override;

private:
    Album *album;
    Artist *artist;
    ArtistComposition *artistComposition;
    Composition *composition;
    UrlAudio *urlAudio;

    int insertAlbum(const Tags *tags);
    QList<int> insertArtists(const Tags *tags);
    bool insertAC(const int idComposition, const QList<int> &idArtists);
    void cancelCompositionInsert(const int idAlbum,
                                 const QList<int> *idArtist = nullptr,
                                 const int idComposition = 0);
    void compositionCleanup(const int idAlbum, const QList<int> &idAstists);
};

#endif // COMPOSITIONCONTROLLER_H
