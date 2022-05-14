#include "getarttask.h"

GetArtTask::GetArtTask(QString path, QObject *parent) : QObject(parent) {
    this->path = path;
}

void GetArtTask::run() {
    TagReader tagReader;
    QImage result = tagReader.getCoverArt(path);
    emit completed(result);
}
