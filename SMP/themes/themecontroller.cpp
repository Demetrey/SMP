#include "themecontroller.h"

ThemeController::ThemeController(QObject *parent)
    : QObject(parent) {
    defaultThemeFolder = "./themes/";
}

/**
 * @brief Load themes from files and standard themes
 * @return Theme file paths
 */
QStringList ThemeController::loadThemeFiles() {
    QStringList themeFalise = {":/themes/XML/themes/light.xml", ":/themes/XML/themes/dark.xml"};

    QDir path(defaultThemeFolder);
    if (path.exists()) {
        QStringList filter = {"*.xml"};
        QStringList  files = path.entryList(filter, QDir::Files);
        for (const QString &file : qAsConst(files)) {
            themeFalise.append(defaultThemeFolder + file);
        }
    }

    return themeFalise;
}

/**
 * @brief Setting the theme directory
 * @param defaultThemeFolder - new path
 */
void ThemeController::setDefaultThemeFolder(const QString &defaultThemeFolder) {
    this->defaultThemeFolder = defaultThemeFolder;
}

QStringList ThemeController::getColors(const QString &file) {
    return XmlLoader::loadThem(file);
}
