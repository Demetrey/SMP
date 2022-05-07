/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef ICOMPOSITIONCONTROLLER_H
#define ICOMPOSITIONCONTROLLER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QList>
#include <QSqlDatabase>
#include "tagreader/tagstructs.h"

class ICompositionController : public QObject {
public slots:
    virtual void insertComposition(const QString& path, const Tags* tags) = 0;
    virtual void deleteComposition(const int id) = 0;
    virtual void updateComposition(const int id, const QString& path,
                                   const Tags* tags) = 0;

    virtual void insertUrl(const QString& url, const QString& name) = 0;
    virtual void deleteUrl(const int id) = 0;
    virtual void updateUrl(const int id, QString& url, const QString& name) = 0;

signals:
    void insertedComposition(int id);
    void deletedComposition(int id);
    void updatedComposition(int id);
    void changedMedia();

};

#endif // ICOMPOSITIONCONTROLLER_H
