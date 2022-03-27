/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU Lesser General Public License (LGPL).
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

signals:

};

#endif // XMLLOADER_H
