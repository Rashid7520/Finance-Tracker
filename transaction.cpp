#include "transaction.h"
#include "db.h"

#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iomanip>
#include <algorithm>

using namespace std;

void addTransaction(int user_id)
{
    int category_id;
    double amount;
    string type, date, description;

    cout << "\n-- ADD TRANSACTION --\n";
    cout << "Category ID: ";
    cin >> category_id;

    cout << "Type (Income/Expense): ";
    cin >> type;

    // Convert type to lowercase for uniformity
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type != "income" && type != "expense") {
        cout << "Invalid type entered. Please enter either 'Income' or 'Expense'.\n";
        return;
    }

    cout << "Amount: ";
    cin >> amount;

    cout << "Date (YYYY-MM-DD): ";
    cin >> date;
    cin.ignore();  // clear newline before reading description

    cout << "Description: ";
    getline(cin, description);

    try {
        sql::Connection* con = getDBConnection();
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO Transactions(user_id, category_id, amount, type, txn_date, description, created_at) "
            "VALUES (?, ?, ?, ?, ?, ?, NOW())"
        );

        pstmt->setInt(1, user_id);
        pstmt->setInt(2, category_id);
        pstmt->setDouble(3, amount);
        pstmt->setString(4, type);
        pstmt->setString(5, date);
        pstmt->setString(6, description);

        pstmt->executeUpdate();
        cout << "Transaction added successfully.\n";

        delete pstmt;
        delete con;

    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void viewTransactions(int user_id)
{
    try {
        sql::Connection* con = getDBConnection();
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT t.txn_id, c.name AS category_name, t.amount, t.type, t.txn_date, t.description "
            "FROM Transactions t "
            "JOIN Categories c ON t.category_id = c.category_id "
            "WHERE t.user_id = ? "
            "ORDER BY t.txn_date DESC"
        );

        pstmt->setInt(1, user_id);
        sql::ResultSet* rs = pstmt->executeQuery();

        cout << "\n-- VIEW TRANSACTIONS --\n";
        cout << left << setw(8) << "ID"
             << setw(20) << "Category"
             << setw(15) << "Amount"
             << setw(10) << "Type"
             << setw(15) << "Date"
             << "Description\n";
        cout << string(80, '-') << endl;

        while (rs->next()) {
            cout << left << setw(8)  << rs->getInt("txn_id")
                 << setw(20) << rs->getString("category_name")
                 << setw(15) << rs->getDouble("amount")
                 << setw(10) << rs->getString("type")
                 << setw(15) << rs->getString("txn_date")
                 << rs->getString("description") << endl;
        }

        delete rs;
        delete pstmt;
        delete con;

    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}
