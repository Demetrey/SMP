/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef FILETYPES_H
#define FILETYPES_H

#include <QObject>

class FileTypes : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The FileType enum
     * Доступные форматы аудиофайлов
     * Available audio file formats
     */
    enum class FileType : int {
        Unknown,
        Mpeg,
        Mp4,
        Aiff,
        S3m,
        Mod,
        Ape,
        Flac,
        Opus
    };
    Q_ENUM(FileType)
};

#endif // FILETYPES_H
