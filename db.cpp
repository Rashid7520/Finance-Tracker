#include "db.h"

sql::Connection* getDBConnection()
{
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://192.168.0.102:3306", "root", "7520");
    con->setSchema("finance");
    return con;
}
