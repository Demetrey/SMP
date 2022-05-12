/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "basecontroller.h"

BaseController::BaseController(DBConnect *dbc) {
    this->dbc = dbc;
}

BaseController::~BaseController() {
}

/**
 * @brief Get QSqlDatabase object
 * @return QSqlDatabase object
 */
QSqlDatabase BaseController::getDB() {
    return dbc->getDB();
}
