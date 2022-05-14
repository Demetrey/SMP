/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

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
    QStringList takenFiles = takeFiles();
    if (takenFiles.isEmpty())
        emit completedFilesAdding();
    startTask(takenFiles);
}

/**
 * @brief Get From Folder
 *
 * Gets a list of files from the selected directory and starts the task of
 * adding files to the database
 */
void FileGetter::getFromFolder() {
    emit startedFilesAdding();

    QString folder = takeFolder();
    if (folder.isEmpty())
        return;
    QDir dir(folder);
    QStringList files = dir.entryList(QDir::Files);

    QStringList takenFiles;
    for (QString file : files) {
        qDebug() << file;
        takenFiles.append(dir.absoluteFilePath(file));
    }

    startTask(takenFiles);
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
    qDebug() << "START GETTING FILES";
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
    qDebug() << "END GETTING FILES";
    return files;
}

/**
 * @brief Take Folder
 * @return The name of the selected directory
 */
QString FileGetter::takeFolder() {
    QString dir =
            QFileDialog::getExistingDirectory(0, (QString("Select directory").toUtf8()),
              QStandardPaths::writableLocation(QStandardPaths::MusicLocation),
              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    return dir;
}

/**
 * @brief Start Task
 *
 * Running the task of adding files to the database in a separate thread
 *
 * @param takeFiles List of files to add
 */
void FileGetter::startTask(QStringList takeFiles) {
    GetFilesTask *task = new GetFilesTask();
    task->setTakenFiles(takeFiles);
    connect(task, SIGNAL(completedAdding()), this, SLOT(onCompletedAdding()));
    task->setAutoDelete(true);
    QThreadPool::globalInstance()->start(task);
}
