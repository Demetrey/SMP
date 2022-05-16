/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#include "compositionpresenter.h"

CompositionPresenter::CompositionPresenter(QObject *parent)
    : QObject(parent) {
    m_Artisr = "...";
    m_Title = "...";
    m_Album = "...";
}

void CompositionPresenter::setArtists(const QString &artists) {
    QStringList artistNames = artists.split(",");
    QString artistStr;
    for (int i = 0; i < artistNames.size(); i++) {
        artistStr += artistNames.at(i);
        if (i < artistNames.size() - 1) {
            artistStr += ", ";
        }
    }
    setArtisr(artistStr);
}

const QString &CompositionPresenter::Title() const
{
    return m_Title;
}

void CompositionPresenter::setTitle(const QString &newTitle)
{
    if (m_Title == newTitle)
        return;
    m_Title = newTitle;
    emit TitleChanged();
}

const QString &CompositionPresenter::Album() const
{
    return m_Album;
}

void CompositionPresenter::setAlbum(const QString &newAlbum)
{
    if (m_Album == newAlbum)
        return;
    m_Album = newAlbum;
    emit AlbumChanged();
}

const QString &CompositionPresenter::Artisr() const
{
    return m_Artisr;
}

void CompositionPresenter::setArtisr(const QString &newArtisr)
{
    if (m_Artisr == newArtisr)
        return;
    m_Artisr = newArtisr;
    emit ArtisrChanged();
}

int CompositionPresenter::Year() const
{
    return m_Year;
}

void CompositionPresenter::setYear(int newYear)
{
    if (m_Year == newYear)
        return;
    m_Year = newYear;
    emit YearChanged();
}
