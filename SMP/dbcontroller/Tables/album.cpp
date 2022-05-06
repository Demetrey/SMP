/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "album.h"

Album::Album(QString &connectionName) : BaseTable(connectionName) {
    this->tableName = QString(ALBUM);
}
