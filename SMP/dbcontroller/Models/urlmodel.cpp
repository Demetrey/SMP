/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "urlmodel.h"

UrlModel::UrlModel(QSqlDatabase db, QObject *parent)
    : QSqlQueryModel(parent) {
    this->db = db;
    updateModel();
}

QVariant UrlModel::data(const QModelIndex &index, int role) const {
    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> UrlModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[idRole] = "id";
    roles[urlRole] = "url";
    roles[nameRole] = "name";
    return roles;
}

/**
 * @brief Update model
 * @param search - String to search using the pattern "LIKE %search%", if not empty
 */
void UrlModel::updateModel(const QString search) {
    QString queryText  = "select id, link, name from url_audio";

    if (!search.isEmpty()) {
        queryText += " where name like lower(\"%" + search + "%\") "
                    "or link like \"%" + search + "%\"";
    }

    queryText += " ORDER BY name";
    this->setQuery(queryText, db);
}

/**
 * @brief PlaylistModel::getId
 * @param rowIndex - Row index to get ID
 * @return ID
 */
int UrlModel::getId(int rowIndex) {
    return this->data(this->index(rowIndex, 0), idRole).toInt();
}
