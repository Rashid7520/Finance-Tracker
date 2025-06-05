#include "summary.h"
#include "db.h"

#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iomanip>

using namespace std;

void viewSummary(int user_id)
{
    try {
        sql::Connection* con = getDBConnection();
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT MONTH(txn_date) AS month, YEAR(txn_date) AS year, type, SUM(amount) AS total "
            "FROM Transactions "
            "WHERE user_id = ? "
            "GROUP BY year, month, type "
            "ORDER BY year DESC, month DESC"
        );

        pstmt->setInt(1, user_id);
        sql::ResultSet* rs = pstmt->executeQuery();

        cout << "\n--- Monthly Financial Summary ---\n";
        cout << left << setw(10) << "Month"
             << setw(10) << "Year"
             << setw(12) << "Type"
             << "Total Amount\n";
        cout << string(45, '-') << endl;

        while (rs->next()) {
            int month = rs->getInt("month");
            int year = rs->getInt("year");
            string type = rs->getString("type");
            double total = rs->getDouble("total");

            cout << left << setw(10) << month
                 << setw(10) << year
                 << setw(12) << type
                 << fixed << setprecision(2) << "$" << total << endl;
        }

        delete rs;
        delete pstmt;
        delete con;
    }
    catch (sql::SQLException &e) {
        cerr << "Error viewing summary: " << e.what() << endl;
    }
}
