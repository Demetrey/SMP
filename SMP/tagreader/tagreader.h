#ifndef TAGREADER_H
#define TAGREADER_H

#include <QMimeDatabase>
#include <QMimeType>

#include "taggetter.h"
#include "tagstructs.h"

class TagReader
{
public:
    TagReader();
    Tags *getTags(QString fileway);


private:
    QMimeDatabase mime;
};

#endif // TAGREADER_H
