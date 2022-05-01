#include "tagreader.h"

TagReader::TagReader()
{

}

Tags *TagReader::getTags(QString fileway) {
    Tags *tags = nullptr;
    qDebug() << mime.mimeTypeForFile(fileway, QMimeDatabase::MatchContent).name();
    return tags;
}
