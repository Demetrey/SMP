/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "mediamodel.h"

MediaModel::MediaModel(QSqlDatabase db, QObject *parent)
    : QSqlQueryModel(parent) {
    this->db = db;
    updateModel();
}

QVariant MediaModel::data(const QModelIndex &index, int role) const {
    // the column number is determined by the role number
    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);
    // extract the required data
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> MediaModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[pathRole] = "path";
    roles[nameRole] = "name";
    roles[yearRole] = "year";
    roles[artistRole] = "artist";
    roles[albumRole] = "album";
    return roles;
}

/**
 * @brief Update model
 * Updating model data
 * @param search - String to search using the pattern "LIKE %search%", if not empty
 */
void MediaModel::updateModel(const QString search) {
    QString queryText  = "select composition.id, compositionPath, compositionName, "
                    "compositionYear, group_concat(artist.name), album.name "
                    "from composition join artist_composition on "
                    "composition.id = idComposition join artist on "
                    "idArtist = artist.id join album on album.id = idAlbum";

    if (!search.isEmpty()) {
        queryText += " where compositionName like \"%" + search + "%\" "
                    "or artist.name like \"%" + search + "%\" "
                    "or album.name like \"%" + search + "%\"";
    }

    queryText += " GROUP BY composition.id ORDER BY compositionName";
    this->setQuery(queryText, db);
}

/**
 * @brief Get ID
 * @param rowIndex - Row index to get ID
 * @return ID
 */
int MediaModel::getId(int rowIndex) {
    return this->data(this->index(rowIndex, 0), idRole).toInt();
}
