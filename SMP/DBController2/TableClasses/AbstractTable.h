/*
 * Интерфейс класса, представляющего таблицу БД
 */

#ifndef ABSTRACTTABLE_H
#define ABSTRACTTABLE_H

#include <QVariantList>

class AbstractTable {
public:
    virtual int insert(const QVariantList&) const = 0;
    virtual void remove(const int) = 0;
    virtual void update(const int, const QVariantList&) = 0;
};

#endif // ABSTRACTTABLE_H
