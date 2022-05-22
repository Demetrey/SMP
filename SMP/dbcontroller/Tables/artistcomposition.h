/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef ARTISTCOMPOSITION_H
#define ARTISTCOMPOSITION_H

#include "base/basemanytomany.h"

/**
 * @brief The Album class
 * Класс реализует работу с таблицей ARTIST_COMPOSITION
 * The class implements work with the ARTIST_COMPOSITION table
 */
class ArtistComposition : public BaseManyToMany
{
public:
    ArtistComposition(QString &connectionName) ;

};

#endif // ARTISTCOMPOSITION_H
