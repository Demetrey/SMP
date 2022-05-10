/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "androidgetter.h"

#ifdef Q_OS_ANDROID

AndroidGetter::AndroidGetter() {
}

/**
 * @brief getAbsolutePath
 *
 * Getting absolute paths of files by URI
 *
 * @param files - List of file URIs
 * @return List of absolute file paths
 */
QStringList AndroidGetter::getAbsolutePath(QStringList files) {
    // For each file, the URL must be converted to an absolute path
    for (int i = 0; i < files.size(); i++) {
        try {
            qDebug() << "GET APATH:::::" << files.at(i);
            QAndroidJniObject uri = QAndroidJniObject::callStaticObjectMethod(
                        "android/net/Uri", "parse",
                        "(Ljava/lang/String;)Landroid/net/Uri;",
                        QAndroidJniObject::fromString(files.at(i))
                                                                .object<jstring>());
            files[i] = QAndroidJniObject::callStaticObjectMethod(
                         "com/demetrey/getpath/PathUtil", "getPath",
                         "(Landroid/net/Uri;Landroid/content/Context;)Ljava/lang/String;",
                         uri.object(), QtAndroid::androidContext()
                                                                  .object())
                                                                  .toString();
            // If the file is on the SD card (one of)
            if(files.at(i).left(4) == "null") {
                 QAndroidJniObject stringway = QAndroidJniObject::fromString
                         (files.at(i).right(files.at(i).size() - 4));
                 files[i] = QAndroidJniObject::callStaticObjectMethod(
                         "com/demetrey/getpath/PathUtil", "getSdPath",
                         "(Ljava/lang/String;)Ljava/lang/String;",
                         stringway.object()).toString();
            }
        }
        catch(...) {
            qDebug() << "AAAAAAAAAAAAAAA";
            continue;
        }
    }
    return files;
}

#endif
