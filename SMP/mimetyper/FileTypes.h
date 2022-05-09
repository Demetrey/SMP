#ifndef FILETYPES_H
#define FILETYPES_H

#include <QObject>

class FileTypes : public QObject
{
    Q_OBJECT
public:
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
