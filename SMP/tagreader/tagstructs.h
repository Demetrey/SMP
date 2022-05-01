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
