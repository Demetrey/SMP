/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "imagepresenter.h"

ImagePresenter::ImagePresenter() : QQuickImageProvider(QQuickImageProvider::Image) {
    this->image = QImage(":/cover/IMAGES/no_img.svg"); // Default image
    this->blockSignals(false);
}

QImage ImagePresenter::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
    if(size) {
        *size = this->image.size();
    }

    if(requestedSize.width() > 0 && requestedSize.height() > 0) {
        this->image.size() = this->image.size().scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);
    }

    return this->image;
}

/**
 * @brief Update Image
 * @param image - New image
 */
void ImagePresenter::updateImage(const QImage &image) {
    if(this->image != image) {
        if (image.isNull())
            this->image = QImage(":/cover/IMAGES/no_img.svg");
        else
            this->image = image;
        emit imageChanged();
    }
}
