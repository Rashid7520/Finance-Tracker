#include <iostream>
#include <stdexcept>

// MySQL Connector Headers
#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/statement.h>
#include <cppconn/resultset.h>

using namespace std;

int main() {
    try {
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        // Connect to MySQL server
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://192.168.0.102:3306", "root", "7520");

        // Connect to the specific DB
        con->setSchema("finance");

        // Create and execute a query
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Users");

        cout << "User Data:" << endl;
        while (res->next()) {
            cout << "ID: " << res->getInt("user_id")
                 << ", Name: " << res->getString("name")
                 << ", Email: " << res->getString("email")
                 << ", Created_at: "<<res->getString("created_at") << endl;
        }

        // Clean up
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Exception: " << e.what() << endl;
    }
    catch (exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
