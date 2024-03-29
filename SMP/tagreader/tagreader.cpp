/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "tagreader.h"

TagReader::TagReader() {

}

/**
 * @brief Get tags
 *
 * Getting tags with method selection depending on file mime type
 * The memory of the returned pointer must be freed manually after further use
 *
 * @param fileway - The path to the file
 * @return Tag structure pointer (nullptr if there are no tags)
 */
QSharedPointer<Tags> TagReader::getTags(QString &fileway) {
    FileTypes::FileType fileType = typer.getType(fileway);

    switch (fileType) {
    case FileTypes::FileType::Mpeg:
        return tagGetter.getMPEG(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Mp4:
        return tagGetter.getMP4(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Aiff:
        return tagGetter.getAiff(fileway.toLocal8Bit().data());
    case FileTypes::FileType::S3m:
        return tagGetter.getS3m(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Mod:
        return tagGetter.getMod(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Ape:
        return tagGetter.getApe(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Flac:
        return tagGetter.getFlac(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Opus:
        return tagGetter.getOpus(fileway.toLocal8Bit().data());
    default:
        return QSharedPointer<Tags>::create();
    }
}

/**
 * @brief Get album cover
 *
 * Getting a cover with a choice of method depending on file mime type
 * The memory of the returned pointer must be freed manually after further use
 *
 * @param fileway - The path to the file
 * @return Cover structure pointer (nullptr if there is no cover)
 */
QSharedPointer<Art> TagReader::getArt(QString &fileway) {
    FileTypes::FileType fileType = typer.getType(fileway);

    switch (fileType) {
    case FileTypes::FileType::Mpeg:
        return tagGetter.getArtMPEG(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Mp4:
        return tagGetter.getArtMP4(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Flac:
        return tagGetter.getArtFlac(fileway.toLocal8Bit().data());
    case FileTypes::FileType::Opus:
        return tagGetter.getArtOpus(fileway.toLocal8Bit().data());
    default:
        return QSharedPointer<Art>::create();
    }
}

/**
 * @brief Get Cover Art
 * @param fileway - The path to the file
 * @return Cover image of a QImage, or an empty image if none
 */
QImage TagReader::getCoverArt(QString &fileway) {
    QSharedPointer<Art> art = getArt(fileway);
    QImage coverArt = QImage();
    if (art) {
        coverArt.loadFromData(reinterpret_cast<const uchar*>(art->data), art->size);
    }
    return coverArt;
}
