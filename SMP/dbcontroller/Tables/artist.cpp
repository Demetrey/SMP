/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "artist.h"

Artist::Artist(QString connectionName) : BaseTable(connectionName) {
    this->tableName = QString(ARTIST);
}
