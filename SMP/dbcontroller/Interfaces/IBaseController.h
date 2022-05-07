/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef IBASECONTROLLER_H
#define IBASECONTROLLER_H

#include <QSqlDatabase>

class IBaseController {
public:
    virtual void dbConnect() = 0;
    virtual QSqlDatabase getDB() = 0;
};

#endif // IBASECONTROLLER_H
