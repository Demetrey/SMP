/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QSqlQueryModel>

/**
 * @brief The PlaylistModel class
 * Playlist view model
 */
class PlaylistModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Roles {
        idRole = Qt::UserRole + 1,  // id
        nameRole                    // name
    };

    explicit PlaylistModel(QSqlDatabase db, QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
    QSqlDatabase db;

public slots:
    void updateModel(const QString search = QString());
    int getId(int rowIndex);

};

#endif // PLAYLISTMODEL_H
