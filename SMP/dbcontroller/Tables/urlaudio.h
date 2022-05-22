/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef URLAUDIO_H
#define URLAUDIO_H

#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>

#include "dbcontroller/dbnames.h"

/**
 * @brief The Album class
 * Класс реализует работу с таблицей URL_AUDIO
 * The class implements work with the URL_AUDIO table
 */
class UrlAudio
{
public:
    UrlAudio(QString &connectionName);

    int insert(const QVariantList &data);
    void remove(const int id);
    void update(const int id, const QVariantList &data);
    int getId(const QVariantList &data) const;

private:
    QString connectionName;
    QString tableName;
    const QVector<QString> rows {"id", "link", "name"};

};

#endif // URLAUDIO_H
