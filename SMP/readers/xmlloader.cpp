/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU Lesser General Public License (LGPL).
 */

#include "xmlloader.h"

XmlLoader::XmlLoader(QObject *parent) : QObject(parent) {

}

/**
 * Getting center values ​​for an equalizer
 * @brief XmlLoader::loadCenters
 * @param file - Path to xml file
 * @return List of center values
 */
QVector<int> XmlLoader::loadCenters(QString file) {
    QVector<int> result;
    QFile ofile(file);
    if (ofile.open(QFile::ReadOnly | QFile::Text)) {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&ofile);
        xmlReader.readNext();
        while (!xmlReader.atEnd() && !xmlReader.hasError()) {
            if (xmlReader.isStartElement()) {
                if (xmlReader.name() == "c")
                    result.append(xmlReader.readElementText().toInt());
            }
            xmlReader.readNext();
        }
        xmlReader.clear();
        ofile.close();
    }
    for (int v : result) {
        qDebug() << v;
    }
    return result;
}
