/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef ARTIST_H
#define ARTIST_H

#include "base/basetable.h"

/**
 * @brief The Album class
 * Класс реализует работу с таблицей ARTIST
 * The class implements work with the ARTIST table
 */
class Artist : public BaseTable
{
public:
    Artist(QString &connectionName);

};

#endif // ARTIST_H
