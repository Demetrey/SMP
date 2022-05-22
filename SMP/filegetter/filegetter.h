/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef FILEGETTER_H
#define FILEGETTER_H

#include <QObject>
#include <QThreadPool>
#include <QFileDialog>
#include <QStandardPaths>

#include "getfilestask.h"

/**
 * @brief The FileGetter class
 * Класс, реализующий выбор файлов и добавление записей о композициях в БД
 * A class that implements the selection of files and adding records about
 * compositions to the database
 */
class FileGetter : public QObject
{
    Q_OBJECT
public:
    explicit FileGetter(QObject *parent = nullptr);

signals:
    void completedFilesAdding();
    void startedFilesAdding();

public slots:
    void onCompletedAdding();
    void getFiles();
    void getFromFolder();

private:
    QStringList takeFiles();
    QString takeFolder();
    void startTask(QStringList takeFiles);

};

#endif // FILEGETTER_H
