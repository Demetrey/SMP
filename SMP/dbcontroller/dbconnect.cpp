/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "dbconnect.h"

DBConnect::DBConnect(QString connectionName) {
    this->connectionName = connectionName;
    this->generationFile = QString(GENERATION_FILE);
    // default name initialization
    hostName = QString(MUSIC_HOST_NAME);
    filePath = QString(MUSIC_FILE_PATH);
    fileName = QString(MUSIC_FILE_NAME);
}

DBConnect::~DBConnect() {
    qDebug() << "DBDisconnect";
    this->disconnect();
}

/**
 * @brief Set DB parameters
 *
 * Setting database name parameters
 *
 * @param hostName - \_(^-_-^)_/
 * @param filePath - \_(^-_-^)_/
 * @param fileName - \_(^-_-^)_/
 */
void DBConnect::setParams(QString hostName, QString filePath, QString fileName) {
    this->fileName = fileName;
    this->filePath = filePath;
    this->hostName = hostName;
}

/**
 * @brief Database connection
 *
 * Establishes a connection with the specified name to the database
 * Name setting required for parallel access
 * If there is no directory for the database file or the file itself, the
 * missing components are created. The database is filled with tables loaded
 * from the generation file.
 */
void DBConnect::connect() {
    qDebug() << filePath;
    if(!QDir(filePath).exists()) {
        QDir().mkdir(filePath);
    }
    if(!QFile(filePath + fileName).exists()) {
        QFile createFile(filePath + fileName);
        createFile.open(QIODevice::WriteOnly);
        createFile.close();
        if(!this->openFile()) {
            return;
        }
        if(!this->createTables()) {
            return;
        }
    }
    else {
        if(!this->openFile()) {
            return;
        }
        else {
            QSqlQuery query(QSqlDatabase::database(connectionName));
            if (!query.exec("PRAGMA foreign_keys = ON;")) {
                qDebug() << query.lastError().text();
                this->disconnect();
                return;
            }
            QStringList lst_tables = db.tables();
            qDebug() << lst_tables;
        }
    }
}

QSqlDatabase DBConnect::getDB() {
    return db;
}

/**
 * @brief Opening a connection to a database file
 * @return true - success, false - failure
 */
bool DBConnect::openFile() {
    db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setHostName(hostName);
    db.setDatabaseName(filePath + fileName);

    return db.open();
}

/**
 * @brief Creating tables according to the generation file
 *
 * No generation file means no need to create tables
 *
 * @return true - success, false - failure
 */
bool DBConnect::createTables() {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    if (generationFile.isEmpty())
        return 1;
    QFile scriptFile(generationFile);
    if(scriptFile.open(QIODevice::ReadOnly)) {
        QStringList queries = QTextStream(&scriptFile).readAll().split(';');
        foreach(auto current, queries) {
            if(current.trimmed().isEmpty()) {
                continue;
            }
            if(!query.exec(current)) {
                qDebug() << query.lastError().text();
                return 0;
            }
            query.finish();
        }
    }
    else {
        qDebug() << "Can't open GENERATION file";
        return 0;
    }
    return 1;
}

/**
 * @brief Closing a connection
 */
void DBConnect::disconnect() {
    db.close();
}
