/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "taggetter.h"

TagGetter::TagGetter() {

}

/**
 * @brief Getting tags common to different formats
 *
 * The method is not recommended for use due to unreliability and the
 * inability to catch possible errors in the try-catch block
 * (The one who implemented this method has small paws :3)
 *
 * @param fileway - The path to the file
 * @return Tag structure pointer (nullptr if there are no tags)
 */
Tags *TagGetter::getCommonTags(const char *fileway) {
    Tags *tags = nullptr;
    try {
        TagLib::FileRef file(fileway);
        if (!file.isNull() && !file.tag()->isEmpty()) {
            tags = packer(file.tag()->artist(), file.tag()->title(),
                          file.tag()->album(), file.tag()->year());
        }
    }
    catch(...) {
        qDebug() << "getCommonTags -> Can't read tags";
    }
    return tags;
}

Tags *TagGetter::getMPEG(const char *fileway) {
    TagLib::MPEG::File file(fileway);
    Tags *tags = getCommon<TagLib::MPEG::File> (&file);
    return tags;
}

Tags *TagGetter::getMP4(const char *fileway) {
    TagLib::MP4::File file(fileway);
    Tags *tags = getCommon<TagLib::MP4::File> (&file);
    return tags;
}

Tags *TagGetter::getOpus(const char *fileway) {
    TagLib::Ogg::Opus::File file(fileway);
    Tags *tags = getCommon<TagLib::Ogg::Opus::File> (&file);
    return tags;
}

Tags *TagGetter::getFlac(const char *fileway) {
    TagLib::FLAC::File file(fileway);
    Tags *tags = getCommon<TagLib::FLAC::File> (&file);
    return tags;
}

Tags *TagGetter::getAiff(const char *fileway) {
    TagLib::RIFF::AIFF::File file(fileway);
    Tags *tags = getCommon<TagLib::RIFF::AIFF::File> (&file);
    return tags;
}

Tags *TagGetter::getS3m(const char *fileway) {
    TagLib::S3M::File file(fileway);
    Tags *tags = getCommon<TagLib::S3M::File> (&file);
    return tags;
}

Tags *TagGetter::getMod(const char *fileway) {
    TagLib::Mod::File file(fileway);
    Tags *tags = getCommon<TagLib::Mod::File> (&file);
    return tags;
}

Tags *TagGetter::getApe(const char *fileway) {
    TagLib::APE::File file(fileway);
    Tags *tags = getCommon<TagLib::APE::File> (&file);
    return tags;
}

Art *TagGetter::getArtMPEG(const char *fileway) {
    Art *art = nullptr;
    TagLib::MPEG::File file(fileway);
    if (file.isOpen() && file.hasID3v2Tag()) {
        auto framelist = file.ID3v2Tag(true)->frameList("APIC");
        if (!framelist.isEmpty()) {
            art = new Art;
            auto *coverImage = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(framelist.front());
            art->data = new char[coverImage->picture().size()];
            memcpy(art->data, coverImage->picture().data(),
                   coverImage->picture().size());
            art->size = coverImage->picture().size();
        }
    }
    return art;
}

Art *TagGetter::getArtMP4(const char *fileway) {
    Art *art = nullptr;
    TagLib::MP4::File file(fileway);
    if (file.isOpen() && file.hasMP4Tag() && !file.tag()->isEmpty()) {
        TagLib::MP4::CoverArtList coverArtList =
                file.tag()->itemListMap()["covr"].toCoverArtList();
        if (!coverArtList.isEmpty()) {
            art = new Art;
            auto coverArt = coverArtList.front();
            art->data = new char[coverArt.data().size()];
            memcpy(art->data, coverArt.data().data(), coverArt.data().size());
            art->size = coverArt.data().size();
        }
    }
    return art;
}

Art *TagGetter::getArtOpus(const char *fileway) {
    Art *art = nullptr;
    TagLib::Ogg::Opus::File file(fileway);
    if (!file.isOpen() && !file.tag()->isEmpty()) {
        auto pictureList = file.tag()->pictureList();
        if (!pictureList.isEmpty()) {
            art = new Art;
            auto *coverImage = pictureList.back();
            art->data = new char[coverImage->data().size()];
            memcpy(art->data, coverImage->data().data(), coverImage->data().size());
            art->size = coverImage->data().size();
        }
    }
    return art;
}

Art *TagGetter::getArtFlac(const char *fileway) {
    Art *art = nullptr;
    TagLib::FLAC::File file(fileway);
    if (!file.isOpen() && !file.pictureList().isEmpty()) {
        art = new Art;
        auto coverImage = file.pictureList().back();
        art->data = new char[coverImage->data().size()];
        memcpy(art->data, coverImage->data().data(), coverImage->data().size());
        art->size = coverImage->data().size();
    }
    return art;
}

Tags *TagGetter::packer(TagLib::String artist, TagLib::String title,
                        TagLib::String albun, unsigned short year) {
    Tags *tags = new Tags;
    tags->songName = title.toCString(true);
    tags->songAlbum = albun.toCString(true);
    tags->songYear = year;
    tags->songArtists = QString(artist.toCString(true)).split("/");
    return tags;
}