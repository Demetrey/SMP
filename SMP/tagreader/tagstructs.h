/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef TAGSTRUCTS_H
#define TAGSTRUCTS_H

#include <QString>
#include <QStringList>

struct Tags {
    QString songName = QString();
    QStringList songArtists = QStringList();
    QString songAlbum = QString();
    unsigned short songYear = 0;
};

#endif // TAGSTRUCTS_H
