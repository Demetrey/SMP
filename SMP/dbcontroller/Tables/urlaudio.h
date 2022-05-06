#ifndef URLAUDIO_H
#define URLAUDIO_H

#include <QString>
#include <QVector>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QDebug>

#include "dbcontroller/dbnames.h"

class UrlAudio
{
public:
    UrlAudio(QString connectionName);

    int insert(const QVariantList &data);
    void remove(const int id);
    void update(const int id, const QVariantList &data);
    int getId(const QVariantList &data) const;

private:
    QString connectionName;
    QString tableName;
    const QVector<QString> rows {"id", "link", "name"};

};

#endif // URLAUDIO_H
