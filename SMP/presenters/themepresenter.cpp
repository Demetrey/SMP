#include "themepresenter.h"

ThemePresenter::ThemePresenter(QObject *parent) : QObject(parent) {
    themeController = new ThemeController();
    updateThemeList();
    setTheme(0);
}

ThemePresenter::~ThemePresenter() {
    delete themeController;
}

/**
 * @brief Get themes
 * @return List of topic titles
 */
QStringList ThemePresenter::getThemes() {
    QStringList result;
    for (const QString &theme : qAsConst(themes)) {
        QFileInfo fileInfo(theme);
        result.append(fileInfo.baseName());
    }
    return result;
}

/**
 * @brief Update list of color schemes
 */
void ThemePresenter::updateThemeList() {
    this->themes = themeController->loadThemeFiles();
}

/**
 * @brief Set theme
 * @param index - index of theme
 */
void ThemePresenter::setTheme(int index) {
    if (themes.size() - 1 < index)
        return;
    QStringList colors = themeController->getColors(themes.at(index));
    qDebug() << colors;
    setBackground(colors.at(0));
    setPrimary(colors.at(1));
    setAccent(colors.at(2));
    setTextcolor(colors.at(3));
    setListitem(colors.at(4));
    setListitemselected(colors.at(5));
}


// For properties
const QString &ThemePresenter::Background() const
{
    return m_Background;
}

void ThemePresenter::setBackground(const QString &newBackground)
{
    if (m_Background == newBackground)
        return;
    m_Background = newBackground;
    emit BackgroundChanged();
}

const QString &ThemePresenter::Primary() const
{
    return m_Primary;
}

void ThemePresenter::setPrimary(const QString &newPrimary)
{
    if (m_Primary == newPrimary)
        return;
    m_Primary = newPrimary;
    emit PrimaryChanged();
}

const QString &ThemePresenter::Accent() const
{
    return m_Accent;
}

void ThemePresenter::setAccent(const QString &newAccent)
{
    if (m_Accent == newAccent)
        return;
    m_Accent = newAccent;
    emit AccentChanged();
}

const QString &ThemePresenter::Textcolor() const
{
    return m_Textcolor;
}

void ThemePresenter::setTextcolor(const QString &newTextcolor)
{
    if (m_Textcolor == newTextcolor)
        return;
    m_Textcolor = newTextcolor;
    emit TextcolorChanged();
}

const QString &ThemePresenter::Listitem() const
{
    return m_Listitem;
}

void ThemePresenter::setListitem(const QString &newListitem)
{
    if (m_Listitem == newListitem)
        return;
    m_Listitem = newListitem;
    emit ListitemChanged();
}

const QString &ThemePresenter::Listitemselected() const
{
    return m_Listitemselected;
}

void ThemePresenter::setListitemselected(const QString &newListitemselected)
{
    if (m_Listitemselected == newListitemselected)
        return;
    m_Listitemselected = newListitemselected;
    emit ListitemselectedChanged();
}
