#ifndef INSERTTOPLTASK_H
#define INSERTTOPLTASK_H

#include <QObject>
#include <QRunnable>
#include <QList>

#include "dbcontroller/playlistcontroller.h"
#include "dbcontroller/dbconnect.h"

class InsertToPlTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit InsertToPlTask(int id, QList<int> ids, QObject *parent = nullptr);
    void run() override;

signals:
    void insertCompleted();

private:
    int id;
    QList<int> ids;

};

#endif // INSERTTOPLTASK_H
