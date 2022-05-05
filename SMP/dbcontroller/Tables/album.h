/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef ALBUM_H
#define ALBUM_H

#include "basetable.h"

class Album : public BaseTable
{
public:
    Album(QString connectionName);

};

#endif // ALBUM_H
