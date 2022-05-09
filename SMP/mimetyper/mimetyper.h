/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef MIMETYPER_H
#define MIMETYPER_H

#include <QMimeDatabase>
#include <QMimeType>
#include <QStringList>
#include <QMap>

#include "FileTypes.h"

class MimeTyper
{
public:
    MimeTyper();
    FileTypes::FileType getType(const QString& path);
    bool isCorrectType(const QString& path);

private:
    QMimeDatabase mime;
    QMap<QString, FileTypes::FileType> typeMap;

    void loadTypeMap();

};

#endif // MIMETYPER_H
