/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef GETFILESTASK_H
#define GETFILESTASK_H

#include <QObject>
#include <QRunnable>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QScopedPointer>
#include <QDebug>

#include "dbcontroller/compositioncontroller.h"
#include "tagreader/tagreader.h"
#include "mimetyper/mimetyper.h"
#include "androidgetter.h"

/**
 * @brief The GetFilesTask class
 *
 * Adding data of received files with received paths to the database
 * Designed to run on a separate thread
 */
class GetFilesTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit GetFilesTask(QObject *parent = nullptr);
    void setTakenFiles(QStringList &takenFiles);

signals:
    void completedAdding();

protected:
    void run() override;

private:
    QStringList takenFiles;

};

#endif // GETFILESTASK_H
