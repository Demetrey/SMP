#ifndef FILEGETTER_H
#define FILEGETTER_H

#include <QObject>
#include <QThreadPool>
#include <QFileDialog>
#include <QStandardPaths>

#include "getfilestask.h"

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

private:
    QStringList takeFiles();

};

#endif // FILEGETTER_H
