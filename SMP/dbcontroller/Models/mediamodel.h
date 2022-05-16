/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef MEDIAMODEL_H
#define MEDIAMODEL_H

#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

/**
 * @brief The MediaModel class
 * Модель представления данных композиции
 * Composition Data Representation Model
 */
class MediaModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Roles {
        idRole = Qt::UserRole + 1,  // id
        pathRole,                   // path
        nameRole,                   // name
        yearRole,                   // year
        artistRole,                 // artist
        albumRole                   // album
    };

    explicit MediaModel(QSqlDatabase db, QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
    QSqlDatabase db;

public slots:
    void updateModel(const QString search = QString());
    int getId(int rowIndex);

};

#endif // MEDIAMODEL_H
