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
    QScopedPointer<TagReader> tagReader(new TagReader());
    QScopedPointer<MimeTyper> mimeTyper(new MimeTyper());
    QScopedPointer<CompositionController> compositionController
            (new CompositionController("addFiles"));
    compositionController->dbConnect();

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
                tags->songName = QString("Unknown");
            tags->songArtists.removeAll(QString(""));
            if (tags->songArtists.isEmpty())
                tags->songArtists.append(QString("Unknown"));
            compositionController->insertComposition(file, tags.get());
        }
    }
    emit completedAdding();
}
