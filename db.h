#ifndef DB_H
#define DB_H

#include <mysql_connection.h>
#include <mysql_driver.h>

sql::Connection* getDBConnection();

#endif
