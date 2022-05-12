/*
 * Представление таблицы playlist_composition, устраняющей связь типа М:М
 */

#ifndef PLAYLISTCOMPOSITION_H
#define PLAYLISTCOMPOSITION_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>
#include "AbstractTable.h"

class PlaylistComposition : public QObject, public AbstractTable
{
    Q_OBJECT
public:
    explicit PlaylistComposition(QString connectionName, QObject *parent = nullptr);


    // AbstractTable interface
public:
    int insert(const QVariantList &data) const;
    void remove(const int id);
    void update(const int id, const QVariantList &data);
    void removeFromPlaylist(const int idComposition, const int idPlaylist);
    void clearPlayQueue(const int idlaylist = 0);
    QList<int> getAllIds(const int idPlaylist);
    QList<QVariantList> getAllFromPlaylist(const int idPlaylist);

private:
    QString _connectionName;

    const QString tableName = "playlist_composition";
    const QVector<QString> rows {"idComposition", "idPlaylist"};
};

#endif // PLAYLISTCOMPOSITION_H
