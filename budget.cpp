#include <iostream>
#include <iomanip>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include "db.h"

using namespace std;

void addBudget(int user_id) {
    int category_id;
    string month;
    double amount;

    cout << "\n--- Add Budget ---\n";
    cout << "Enter Category ID: ";
    cin >> category_id;
    cout << "Enter Month (YYYY-MM): ";
    cin >> month;
    cout << "Enter Amount: ";
    cin >> amount;

    try {
        sql::Connection* con = getDBConnection();
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO budget (user_id, category_id, month, amount) VALUES (?, ?, ?, ?)"
        );
        pstmt->setInt(1, user_id);
        pstmt->setInt(2, category_id);
        pstmt->setString(3, month);
        pstmt->setDouble(4, amount);
        pstmt->executeUpdate();

        cout << "✅ Budget added successfully.\n";

        delete pstmt;
        delete con;
    } catch (sql::SQLException& e) {
        cout << "❌ Error adding budget: " << e.what() << "\n";
    }
}

void viewBudget(int user_id) {
    cout << "\n--- View Budget ---\n";

    try {
        sql::Connection* con = getDBConnection();
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT b.budget_id, c.name AS category_name, b.month, b.amount "
            "FROM budget b "
            "JOIN categories c ON b.category_id = c.category_id "
            "WHERE b.user_id = ? "
            "ORDER BY b.month ASC"
        );

        pstmt->setInt(1, user_id);
        sql::ResultSet* rs = pstmt->executeQuery();

        cout << left << setw(10) << "ID" 
             << setw(20) << "Category" 
             << setw(12) << "Month" 
             << "Amount\n";
        cout << "----------------------------------------------\n";

        while (rs->next()) {
            cout << left << setw(10) << rs->getInt("budget_id")
                 << setw(20) << rs->getString("category_name")
                 << setw(12) << rs->getString("month")
                 << "$" << rs->getDouble("amount") << "\n";
        }

        delete rs;
        delete pstmt;
        delete con;
    } catch (sql::SQLException& e) {
        cout << "❌ Error viewing budget: " << e.what() << "\n";
    }
}
