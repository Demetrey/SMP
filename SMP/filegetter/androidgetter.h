/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef ANDROIDGETTER_H
#define ANDROIDGETTER_H

#include <QObject>
#include <QDebug>

#ifdef Q_OS_ANDROID

#include <QStringList>
#include <QFileInfo>

#include <QAndroidJniObject>
#include <QtAndroid>

/**
 * @brief The AndroidGetter class
 *
 * Working with a list of files on Android
 * Designed for Android only
 */
class AndroidGetter
{
public:
    explicit AndroidGetter();
    QStringList getAbsolutePath(QStringList files);

};

#endif // Q_OS_ANDROID
#endif // ANDROIDGETTER_H
