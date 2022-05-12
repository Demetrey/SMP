/*
 * Представление таблицы artist_composition, реализующей устранение связи М:М
 */

#ifndef ARTISTCOMPOSITION_H
#define ARTISTCOMPOSITION_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>
#include "AbstractTable.h"

class ArtistComposition : public QObject, public AbstractTable
{
    Q_OBJECT
public:
    explicit ArtistComposition(QString connectionName, QObject *parent = nullptr);


    // AbstractTable interface
public:
    int insert(const QVariantList &) const;
    void remove(const int);
    void update(const int id, const QVariantList &);
    int getArtistId(const int id) const;
    int getCount(const int id) const;

private:
    QString _connectionName;

    const QString tableName = "artist_composition";
    const QVector<QString> rows {"idComposition", "idArtist"};
};

#endif // ARTISTCOMPOSITION_H
