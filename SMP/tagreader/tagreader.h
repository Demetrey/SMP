/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef TAGREADER_H
#define TAGREADER_H

#include <QMimeDatabase>
#include <QMimeType>

#include "taggetter.h"
#include "tagstructs.h"

class TagReader
{
public:
    TagReader();
    Tags *getTags(QString fileway);


private:
    QMimeDatabase mime;
    TagGetter tagGetter;
};

#endif // TAGREADER_H
