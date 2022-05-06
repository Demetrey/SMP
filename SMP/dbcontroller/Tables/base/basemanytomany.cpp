#include "basemanytomany.h"

BaseManyToMany::BaseManyToMany(QString &connectionName) {
    this->connectionName = connectionName;
}

/**
 * @brief Insert
 * @param data - struct: data[0] = idFirstCol (int), data[1] = idSecondCol (int)
 * @return id of the added data
 */
bool BaseManyToMany::insert(const QVariantList &data) {
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "INSERT INTO " + tableName + " (" + rows.at(0) + ", " + rows.at(1) + ") " +
            "VALUES (:composition, :noComposition)";
    query.prepare(queryText);
    query.bindValue(":composition", data[0].toString());
    query.bindValue(":noComposition", data[1].toString());
    if(!query.exec()) {
        return false;
    }
    return true;
}

/**
 * @brief All idNonComposition of the composition with the specified id
 * @param idComposition - composition id
 * @return List of NonComposition id
 */
QList<int> BaseManyToMany::getIdNonComposition(const int idComposition) {
    QList<int> idNonComposition;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT  " + rows[1] + " FROM " + tableName + " WHERE "
                        + rows[0] + " = :id";
    query.prepare(queryText);
    query.bindValue(":id", QString::number(idComposition));
    if(!query.exec()){
        return idNonComposition;
    }
    else {
        while (query.next()) {
            idNonComposition.append(query.value(0).toInt());
        }
    }
    return idNonComposition;
}

/**
 * @brief All compositions of the NonComposition with the specified id
 * @param idNonComposition - NonComposition id
 * @return Composition id list
 */
QList<int> BaseManyToMany::getIdComposition(const int idNonComposition) {
    QList<int> idComposition;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT  " + rows[0] + " FROM " + tableName + " WHERE "
                        + rows[1] + " = :id";
    query.prepare(queryText);
    query.bindValue(":id", QString::number(idNonComposition));
    if(!query.exec()){
        return idComposition;
    }
    else {
        while (query.next()) {
            idComposition.append(query.value(0).toInt());
        }
    }
    return idComposition;
}

/**
 * @brief Number of songs by idNonComposition
 * @param idNonComposition  - NonComposition id
 * @return The number of songs by the idNonComposition or -1 in case of a query execution error
 */
int BaseManyToMany::compositionCount(int idNonComposition) {
    int count = -1;
    QSqlQuery query(QSqlDatabase::database(connectionName));
    QString queryText = "SELECT COUNT (*) FROM " + tableName +
            " WHERE " + rows.at(1) + " = :id";
    query.prepare(queryText);
    query.bindValue(":id", QString::number(idNonComposition));
    if(!query.exec()) {
        return count;
    }
    else {
        while (query.next()) {
            return query.value(0).toInt();
        }
    }
    return count;
}
