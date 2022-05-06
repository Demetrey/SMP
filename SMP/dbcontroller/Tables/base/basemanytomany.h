#ifndef BASEMANYTOMANY_H
#define BASEMANYTOMANY_H

#include <QString>
#include <QStringList>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>

#include "dbcontroller/dbnames.h"

class BaseManyToMany
{
public:
    BaseManyToMany(QString connectionName);

    int insert(const QVariantList &data);
    QList<int> getIdNonComposition(const int idComposition);
    QList<int> getIdComposition(const int idNonComposition);
    int compositionCount(int idNonComposition);

protected:
    QString connectionName;
    QString tableName;
    QStringList rows;
};

#endif // BASEMANYTOMANY_H
