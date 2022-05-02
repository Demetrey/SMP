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
 *
 * @param fileway - The path to the file
 * @return Tag structure pointer (nullptr if there are no tags)
 */
Tags *TagReader::getTags(QString fileway) {
    QString mimeType = mime.mimeTypeForFile(fileway,
                                            QMimeDatabase::MatchContent).name();
    qDebug() << "Current mime:" << mimeType;
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
