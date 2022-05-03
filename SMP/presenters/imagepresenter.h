/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef IMAGEPRESENTER_H
#define IMAGEPRESENTER_H

#include <QObject>
#include <QImage>
#include <QIcon>
#include <QQuickImageProvider>

#include "tagreader/itagreader.h"

class ImagePresenter : public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    ImagePresenter();

    // QQuickImageProvider interface
    QImage requestImage(const QString &id, QSize *size,
                        const QSize &requestedSize) override;

public slots:
    void updateImage(const QImage &image);

signals:
    void imageChanged();

private:
    QImage image;

};

#endif // IMAGEPRESENTER_H
