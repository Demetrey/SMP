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
    QString mimeType = mime.mimeTypeForFile(fileway,
                                            QMimeDatabase::MatchContent).name();
    const char *chFileway = fileway.toLocal8Bit().data();
    if (mimeType.contains("mpeg"))
        return tagGetter.getMPEG(chFileway);
    else if (mimeType.contains("mp4"))
        return tagGetter.getMP4(chFileway);
    else if (mimeType.contains("aiff"))
        return tagGetter.getAiff(chFileway);
    else if (mimeType.contains("s3m"))
        return tagGetter.getS3m(chFileway);
    else if (mimeType.contains("mod"))
        return tagGetter.getMod(chFileway);
    else if (mimeType.contains("ape"))
        return tagGetter.getApe(chFileway);
    else if (mimeType.contains("flac"))
        return tagGetter.getFlac(chFileway);
    else if (mimeType.contains("opus"))
        return tagGetter.getOpus(chFileway);
    else return nullptr;
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
    QString mimeType = mime.mimeTypeForFile(fileway,
                                            QMimeDatabase::MatchContent).name();
    const char *chFileway = fileway.toLocal8Bit().data();
    if (mimeType.contains("mpeg"))
        return tagGetter.getArtMPEG(chFileway);
    else if (mimeType.contains("mp4"))
        return tagGetter.getArtMP4(chFileway);
    else if (mimeType.contains("flac"))
        return tagGetter.getArtFlac(chFileway);
    else if (mimeType.contains("opus"))
        return tagGetter.getArtOpus(chFileway);
    else return nullptr;
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
