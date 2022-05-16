/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

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
