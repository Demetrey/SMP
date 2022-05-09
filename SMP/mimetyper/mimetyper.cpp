#include "mimetyper.h"

MimeTyper::MimeTyper() {
    loadTypeMap();
}

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
