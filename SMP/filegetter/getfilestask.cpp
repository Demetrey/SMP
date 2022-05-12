/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "getfilestask.h"

GetFilesTask::GetFilesTask(QObject *parent)
    : QObject(parent) {
}

void GetFilesTask::setTakenFiles(QStringList &takenFiles) {
    this->takenFiles = takenFiles;
}

/**
 * @brief GetFilesTask::run
 * Handling a list of file paths
 */
void GetFilesTask::run() {
    DBConnect dbc("addFiles");
    dbc.connect();
    QScopedPointer<TagReader> tagReader(new TagReader());
    QScopedPointer<MimeTyper> mimeTyper(new MimeTyper());
    QScopedPointer<CompositionController> compositionController
            (new CompositionController("addFiles"));

#ifdef Q_OS_ANDROID
    AndroidGetter androidGetter;
    takenFiles = androidGetter.getAbsolutePath(takenFiles);
#endif

    for (QString file : qAsConst(takenFiles)) {

        // File availability check
        QFile tryToOpen(file);
        if (!tryToOpen.exists())
            continue;

        // Checking for correct file type
        if (!mimeTyper->isCorrectType(file))
            continue;

        auto tags = tagReader->getTags(file);

        if (!tags.isNull()) {
            // If the tags are empty, "Unknown" is added
            if (tags->songAlbum.isEmpty())
                tags->songAlbum = QString("Unknown");
            if (tags->songName.isEmpty())
                tags->songName = QFileInfo(tryToOpen).fileName();
            tags->songArtists.removeAll(QString(""));
            if (tags->songArtists.isEmpty())
                tags->songArtists.append(QString("Unknown"));
            compositionController->insertComposition(file, tags.get());
        }
    }
    emit completedAdding();
}
