/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "artistcomposition.h"

ArtistComposition::ArtistComposition(QString connectionName)
    : BaseManyToMany(connectionName) {
    tableName = QString(ARTIST_COMPOSITION);
    this->rows.append("idComposition");
    this->rows.append("idArtist");
}
