/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QList>
#include <QDir>
#include <QStringList>
#include <QFileInfoList>
#include <bass.h>
#include "initializer.h"
#include "playbackcontroller.h"
#include "playbackparameters.h"
#include "readers/xmlloader.h"

class Kernel : public QObject
{
    Q_OBJECT
public:
    explicit Kernel(QObject *parent = nullptr);
    ~Kernel();

    QList<QString> loadPlugins();

signals:

private:
    Initializer initializer;
    PlaybackController pc;

};

#endif // KERNEL_H
