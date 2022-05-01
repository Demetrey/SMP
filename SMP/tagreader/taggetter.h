#ifndef TAGGETTER_H
#define TAGGETTER_H

#include <QString>
#include <QDebug>
#include <tag.h>
#include <fileref.h>
#include <mpegfile.h>
#include <mp4file.h>
#include <opusfile.h>
#include <oggfile.h>
#include <flacfile.h>
#include <aifffile.h>
#include <s3mfile.h>
#include <modfile.h>
#include <apefile.h>
#include <tstring.h>

#include "tagstructs.h"

class TagGetter
{
public:
    TagGetter();
    Tags *getCommonTags(const char* fileway); // Unreliable
    Tags *getMPEG(const char* fileway);
    Tags *getMP4(const char* fileway);
    Tags *getOpus(const char* fileway);
    Tags *getFlac(const char* fileway);
    Tags *getAiff(const char* fileway);
    Tags *getS3m(const char* fileway);
    Tags *getMod(const char* fileway);
    Tags *getApe(const char* fileway);

private:
    Tags *packer(TagLib::String artist, TagLib::String title,
                 TagLib::String albun, unsigned short year);

    /**
     * @brief Getting common tags for different file types
     *
     *  Template method for different types of TagLib files (TagLib::Type::File)
     * Returns a pointer to a tag structure, or nullptr if there are
     * no tags or the file cannot be opened
     *
     * @param file File pointer (TagLib)
     * @return Tag structure pointer
     */
    template<typename T>
    Tags* getCommon(T *file) {
        Tags *tags = nullptr;
        if (file->isOpen() && !file->tag()->isEmpty()) {
            tags = packer(file->tag()->artist(), file->tag()->title(),
                          file->tag()->album(), file->tag()->year());
        }
        return tags;
    }
};

#endif // TAGGETTER_H
