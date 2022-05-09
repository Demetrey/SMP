/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef TAGREADER_H
#define TAGREADER_H

#include <QImage>

#include "mimetyper/mimetyper.h"
#include "itagreader.h"
#include "taggetter.h"
#include "tagstructs.h"

class TagReader : public ITagReader
{
public:
    TagReader();
    QSharedPointer<Tags> getTags(QString &fileway) override;
    QSharedPointer<Art> getArt(QString &fileway) override;
    QImage getCoverArt(QString &fileway) override;


private:
    TagGetter tagGetter;
    MimeTyper typer;
};

#endif // TAGREADER_H
