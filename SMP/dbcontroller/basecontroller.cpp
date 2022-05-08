/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "basecontroller.h"

BaseController::BaseController(QString connectionName) {
    dbc = new DBConnect(connectionName, QString(GENERATION_FILE));
}

BaseController::~BaseController() {
    delete dbc;
}

/**
 * @brief Connect to database
 */
void BaseController::dbConnect() {
    dbc->connect();
}

/**
 * @brief Get QSqlDatabase object
 * @return QSqlDatabase object
 */
QSqlDatabase BaseController::getDB() {
    return dbc->getDB();
}
