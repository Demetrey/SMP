#ifndef THEMEPRESENTER_H
#define THEMEPRESENTER_H

#include <QObject>
#include <QStringList>
#include <QFileInfo>

#include "themes/themecontroller.h"

class ThemePresenter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Background READ Background WRITE setBackground NOTIFY BackgroundChanged)
    Q_PROPERTY(QString Primary READ Primary WRITE setPrimary NOTIFY PrimaryChanged)
    Q_PROPERTY(QString Accent READ Accent WRITE setAccent NOTIFY AccentChanged)
    Q_PROPERTY(QString Textcolor READ Textcolor WRITE setTextcolor NOTIFY TextcolorChanged)
    Q_PROPERTY(QString Listitem READ Listitem WRITE setListitem NOTIFY ListitemChanged)
    Q_PROPERTY(QString Listitemselected READ Listitemselected WRITE setListitemselected NOTIFY ListitemselectedChanged)
public:
    explicit ThemePresenter(QObject *parent = nullptr);
    ~ThemePresenter();
    Q_INVOKABLE QStringList getThemes();

    const QString &Background() const;
    void setBackground(const QString &newBackground);
    const QString &Primary() const;
    void setPrimary(const QString &newPrimary);
    const QString &Accent() const;
    void setAccent(const QString &newAccent);
    const QString &Textcolor() const;
    void setTextcolor(const QString &newTextcolor);
    const QString &Listitem() const;
    void setListitem(const QString &newListitem);
    const QString &Listitemselected() const;
    void setListitemselected(const QString &newListitemselected);

public slots:
    void setTheme(int index);
    void updateThemeList();

signals:
    void BackgroundChanged();
    void PrimaryChanged();
    void AccentChanged();
    void TextcolorChanged();
    void ListitemChanged();
    void ListitemselectedChanged();

private:
    QStringList themes;
    ThemeController *themeController;

    QString m_Background;
    QString m_Primary;
    QString m_Accent;
    QString m_Textcolor;
    QString m_Listitem;
    QString m_Listitemselected;
};

#endif // THEMEPRESENTER_H
