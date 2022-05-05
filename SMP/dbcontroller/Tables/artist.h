/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef ARTIST_H
#define ARTIST_H

#include "basetable.h"

class Artist : public BaseTable
{
public:
    Artist(QString connectionName);

};

#endif // ARTIST_H
