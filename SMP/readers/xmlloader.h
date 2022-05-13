/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <QObject>
#include <QFile>
#include <QVector>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QDebug>

class XmlLoader : public QObject
{
    Q_OBJECT
public:
    explicit XmlLoader(QObject *parent = nullptr);
    static QVector<int> loadCenters(QString file);
    static QStringList loadPlugFiles(QString file);
    static QStringList loadThem(QString file);

signals:

};

#endif // XMLLOADER_H
