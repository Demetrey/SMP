/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */


#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>

#include "dbcontroller/dbnames.h"

class Composition
{
public:
    Composition(QString &connectionName);

    int insert(const QVariantList &data) const;
    void remove(const int id);
    void update(const int id, const QVariantList &data);
    int getId(const QVariantList &data) const;
    QVariantList getData(const int id) const;
    int getAlbumCount(const int id) const;

private:
    QString connectionName;
    QString tableName;
    const QVector<QString> rows {"id", "compositionPath", "compositionName",
                                 "compositionYear", "idAlbum"};

};

#endif // COMPOSITION_H
