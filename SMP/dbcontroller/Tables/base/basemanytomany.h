/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef BASEMANYTOMANY_H
#define BASEMANYTOMANY_H

#include <QString>
#include <QStringList>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>

#include "dbcontroller/dbnames.h"

/**
 * @brief The BaseManyToMany class
 * Базовый класс, реализующий работу в бд с таблицами со связью М:М
 * The base class that implements work in the database with tables with M:M
 * relationship
 */
class BaseManyToMany
{
public:
    BaseManyToMany(QString &connectionName);

    bool insert(const QVariantList &data);
    QList<int> getIdNonComposition(const int idComposition);
    QList<int> getIdComposition(const int idNonComposition);
    int compositionCount(int idNonComposition);

protected:
    QString connectionName;
    QString tableName;
    QStringList rows;
};

#endif // BASEMANYTOMANY_H
