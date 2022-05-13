/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
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
    return result;
}

/**
 * Getting plugin filenames to load
 * @brief XmlLoader::loadPlugFiles
 * @param file - Path to xml file
 * @return List of filenames
 */
QStringList XmlLoader::loadPlugFiles(QString file) {
    QStringList result;
    QFile ofile(file);
    if (ofile.open(QFile::ReadOnly | QFile::Text)) {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&ofile);
        xmlReader.readNext();
        while (!xmlReader.atEnd() && !xmlReader.hasError()) {
            if (xmlReader.isStartElement()) {
                if (xmlReader.name() == "p")
                    result.append(xmlReader.readElementText());
            }
            xmlReader.readNext();
        }
        xmlReader.clear();
        ofile.close();
    }
    return result;
}

/**
 * @brief Load colors from file
 * @param file - Path to xml file
 * @return [Theme, Background, Primary, Accent, TextColor, ListItemColor, SelectedListItemColor]
 */
QStringList XmlLoader::loadThem(QString file) {
    QStringList result;
    QFile ofile(file);
    if (ofile.open(QFile::ReadOnly | QFile::Text)) {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&ofile);
        xmlReader.readNext();
        while (!xmlReader.atEnd() && !xmlReader.hasError()) {
            if (xmlReader.isStartElement()) {
                if (xmlReader.name() == "theme")
                    result.append(xmlReader.readElementText());
                if (xmlReader.name() == "background")
                    result.append(xmlReader.readElementText());
                if (xmlReader.name() == "primary")
                    result.append(xmlReader.readElementText());
                if (xmlReader.name() == "accent")
                    result.append(xmlReader.readElementText());
                if (xmlReader.name() == "textcolor")
                    result.append(xmlReader.readElementText());
                if (xmlReader.name() == "listitem")
                    result.append(xmlReader.readElementText());
                if (xmlReader.name() == "listitemselected")
                    result.append(xmlReader.readElementText());
            }
            xmlReader.readNext();
        }
        xmlReader.clear();
        ofile.close();
    }
    return result;
}
