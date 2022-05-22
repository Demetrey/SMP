/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "dbnames.h"

/**
 * @brief The DBConnect class
 * Установка соединения с БД
 * Establishing a database connection
 */
class DBConnect
{
public:
    explicit DBConnect(QString connectionName);
    ~DBConnect();

    void setParams(QString hostName, QString filePath, QString fileName);
    void connect();
    QSqlDatabase getDB();
    void disconnect();

private:
    QSqlDatabase db;
    QString connectionName;

    QString hostName;
    QString filePath;
    QString fileName;
    QString generationFile;

    bool openFile();
    bool createTables();

};

#endif // DBCONNECT_H
