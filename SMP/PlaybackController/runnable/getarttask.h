#ifndef GETARTTASK_H
#define GETARTTASK_H

#include <QObject>
#include <QRunnable>
#include <QImage>

#include "tagreader/tagreader.h"

class GetArtTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit GetArtTask(QString path, QObject *parent = nullptr);
    void run() override;

signals:
    void completed(QImage);

private:
    QString path;

};

#endif // GETARTTASK_H
