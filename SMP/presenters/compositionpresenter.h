/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef COMPOSITIONPRESENTER_H
#define COMPOSITIONPRESENTER_H

#include <QObject>
#include <QString>
#include <QStringList>

class CompositionPresenter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Title READ Title WRITE setTitle NOTIFY TitleChanged)
    Q_PROPERTY(QString Album READ Album WRITE setAlbum NOTIFY AlbumChanged)
    Q_PROPERTY(QString Artisr READ Artisr WRITE setArtisr NOTIFY ArtisrChanged)
    Q_PROPERTY(int Year READ Year WRITE setYear NOTIFY YearChanged)

    QString m_Title;
    QString m_Album;
    QString m_Artisr;
    int m_Year;

public:
    explicit CompositionPresenter(QObject *parent = nullptr);
    void setArtists(const QString &artists);

    const QString &Title() const;
    void setTitle(const QString &newTitle);
    const QString &Album() const;
    void setAlbum(const QString &newAlbum);
    const QString &Artisr() const;
    void setArtisr(const QString &newArtisr);
    int Year() const;
    void setYear(int newYear);

signals:
    void TitleChanged();
    void AlbumChanged();
    void ArtisrChanged();
    void YearChanged();
};

#endif // COMPOSITIONPRESENTER_H
