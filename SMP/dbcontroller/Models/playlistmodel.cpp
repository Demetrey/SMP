/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QSqlDatabase db, QObject *parent)
    : QSqlQueryModel(parent) {
    this->db = db;
    updateModel();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[nameRole] = "name";
    return roles;
}

/**
 * @brief Update model
 * Updating model data
 * @param search - String to search using the pattern "LIKE %search%", if not empty
 */
void PlaylistModel::updateModel(const QString search) {
    QString queryText  = "select id, name from playlist "
                         "where id > 0";

    if (!search.isEmpty()) {
        queryText += " and name like \"%" + search + "%\"";
    }

    queryText += " GROUP BY name";
    this->setQuery(queryText, db);
}

/**
 * @brief PlaylistModel::getId
 * @param rowIndex - Row index to get ID
 * @return ID
 */
int PlaylistModel::getId(int rowIndex) {
    return this->data(this->index(rowIndex, 0), idRole).toInt();
}
