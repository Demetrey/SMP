/*
 * Copyright (c) 2022, Dmitry Fomin.
 * This program is distributed under the terms of
 * the GNU General Public License v3.0 (GPL-3.0).
 */

#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "Interfaces/IBaseController.h"
#include "dbconnect.h"
#include "dbnames.h"

class BaseController : public IBaseController
{
public:
    BaseController(DBConnect *dbc);
    ~BaseController();

    // IBaseController interface
public:
    QSqlDatabase getDB() override;

protected:
    DBConnect *dbc;

};

#endif // BASECONTROLLER_H
