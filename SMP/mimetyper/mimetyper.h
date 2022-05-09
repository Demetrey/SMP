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

private:
    QMimeDatabase mime;
    QMap<QString, FileTypes::FileType> typeMap;

    void loadTypeMap();

};

#endif // MIMETYPER_H
