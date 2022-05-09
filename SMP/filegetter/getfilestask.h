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
