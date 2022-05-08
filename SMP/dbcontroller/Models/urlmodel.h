/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef URLMODEL_H
#define URLMODEL_H

#include <QSqlQueryModel>

/**
 * @brief The UrlModel class
 * URL sources presentation model
 */
class UrlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Roles {
        idRole = Qt::UserRole + 1,  // id
        urlRole,                    // URL
        nameRole                    // name
    };

    explicit UrlModel(QSqlDatabase db, QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;
    QSqlDatabase db;

public slots:
    void updateModel(const QString search = QString());
    int getId(int rowIndex);
};

#endif // URLMODEL_H
