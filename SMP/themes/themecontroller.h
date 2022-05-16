/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef THEMECONTROLLER_H
#define THEMECONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QDir>
#include <QFile>

#include "readers/xmlloader.h"

class ThemeController : public QObject
{
    Q_OBJECT
public:
    explicit ThemeController(QObject *parent = nullptr);
    QStringList loadThemeFiles();
    void setDefaultThemeFolder(const QString &defaultThemeFolder);
    QStringList getColors(const QString &file);

private:
    QString defaultThemeFolder;

};

#endif // THEMECONTROLLER_H
