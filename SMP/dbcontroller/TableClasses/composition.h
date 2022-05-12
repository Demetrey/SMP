/*
 * Представление композиции
 */

#ifndef COMPOSITION_H
#define COMPOSITION_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QList>
#include <QDebug>
#include "AbstractTable.h"

class Composition : public QObject, public AbstractTable
{
    Q_OBJECT
public:
    explicit Composition(QString connectionName, QObject *parent = nullptr);


    // AbstractTable interface
public:
    int insert(const QVariantList &data) const override;
    void remove(const int id) override;
    void update(const int id, const QVariantList &data) override;
    int getAlbum(const int id) const;
    int getAlbumCount(const int id) const;
    QList<int> getAllId();

private:
    QString _connectionName;

    const QString tableName = "Composition";
    const QVector<QString> rows {"id", "compositionPath", "compositionName", "compositionYear", "idAlbum"};

};

#endif // COMPOSITION_H
