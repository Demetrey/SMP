/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "mimetyper.h"

MimeTyper::MimeTyper() {
    loadTypeMap();
}

/**
 * @brief Get type
 * @param path - Path to file
 * @return File type number from enum
 */
FileTypes::FileType MimeTyper::getType(const QString &path) {
    QString mimeType = mime.mimeTypeForFile(path,
                                            QMimeDatabase::MatchContent).name();
    mimeType.contains("aiff");
    for (auto iter = typeMap.begin(); iter != typeMap.end(); iter++) {
        if (mimeType.contains(iter.key())) {
            return iter.value();
        }
    }
    return FileTypes::FileType::Unknown;
}

/**
 * @brief Checking for correct file type
 * @param path - Path to file
 * @return true - file type is correct; false - file type is not supported
 */
bool MimeTyper::isCorrectType(const QString &path) {
    return (getType(path) != FileTypes::FileType::Unknown);
}

/**
 * @brief Load typeMap
 */
void MimeTyper::loadTypeMap() {
    typeMap.insert("aiff", FileTypes::FileType::Aiff);
    typeMap.insert("ape", FileTypes::FileType::Ape);
    typeMap.insert("flac", FileTypes::FileType::Flac);
    typeMap.insert("mod", FileTypes::FileType::Mod);
    typeMap.insert("mp4", FileTypes::FileType::Mp4);
    typeMap.insert("mpeg", FileTypes::FileType::Mpeg);
    typeMap.insert("opus", FileTypes::FileType::Opus);
    typeMap.insert("s3m", FileTypes::FileType::S3m);
}
