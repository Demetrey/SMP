/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */


#ifndef BASETABLE_H
#define BASETABLE_H

#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>

#include "dbcontroller/dbnames.h"

/**
 * @brief The BaseTable class
 * Базовый класс, реализующий работу с однотипными таблицами БД
 * The base class that implements work with the same type of database tables
 */
class BaseTable
{
public:
    BaseTable(QString &connectionName);

    int insert(const QVariantList &data);
    void remove(const int id);
    void update(const int id, const QVariantList &data);
    int getId(const QVariantList &data) const;
    QVariantList getData(int id) const;

protected:
    QString connectionName;
    QString tableName;

};

#endif // BASETABLE_H
