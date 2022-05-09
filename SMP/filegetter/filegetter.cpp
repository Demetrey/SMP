#include "filegetter.h"

FileGetter::FileGetter(QObject *parent)
    : QObject(parent) {
}

void FileGetter::onCompletedAdding() {
    emit completedFilesAdding();
}

/**
 * @brief Get Files
 *
 * Starting a task to process the list of received file paths
 * and add them to the database.
 */
void FileGetter::getFiles() {
    emit startedFilesAdding();
    GetFilesTask *task = new GetFilesTask();
    QStringList takenFiles = takeFiles();
    task->setTakenFiles(takenFiles);
    connect(task, SIGNAL(completedAdding()), this, SLOT(onCompletedAdding()));
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);
}

/**
 * @brief Take files
 *
 * Getting a list of paths to files of specified formats using the
 * standard QFileDialog.
 * Unfortunately, some graphical shells do not allow us to perform
 * this task in a separate thread.
 *
 * @return File paths
 */
QStringList FileGetter::takeFiles() {
    QString filter_string = "MP3 (*.mp3);;"
                            "AAC (*.aac);;"
                            "APE (*.ape);;"
                            "AIFF (*.aiff);;"
                            "M4A (*.m4a);;"
                            "MOD (*.mod);;"
                            "OGG (*.ogg);;"
                            "OPUS (*.opus);;"
                            "S3M (*.s3m);;"
                            "All Files (*.*)";
    QStringList files =
                QFileDialog::getOpenFileNames(0, (QString("Select files").toUtf8()),
                  QStandardPaths::writableLocation(QStandardPaths::MusicLocation),
                  filter_string.toUtf8());
    return files;
}
