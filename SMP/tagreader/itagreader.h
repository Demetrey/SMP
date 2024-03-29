/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef ITAGREADER_H
#define ITAGREADER_H

#include <QImage>
#include <QSharedPointer>

#include "tagstructs.h"

class ITagReader {
public:
    virtual QSharedPointer<Tags> getTags(QString&) = 0;
    virtual QSharedPointer<Art> getArt(QString&) = 0;
    virtual QImage getCoverArt(QString&) = 0;
};

#endif // ITAGREADER_H
