#include<iostream>
#include<string>
#include<mysql_driver.h>
#include<mysql_connection.h>
#include<cppconn/prepared_statement.h>
#include<cppconn/resultset.h>
#include<ctime>
#include "db.h"
#include "utils.h"

using namespace std;

void registerUser()
{
    string name, email, password;
    int age;

    cout << "\n--USER REGISTRATION--\n";
    cout << "Name : ";
    cin.ignore();
    getline(cin, name);
    cout << "Email : ";
    getline(cin, email);
    cout << "Age : ";
    cin >> age;
    cout << "Password : ";
    cin.ignore();
    getline(cin, password);

    try {
        sql::Connection* con = getDBConnection();

        // Insert user with plain password
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO users(name, email, age, password, created_at) VALUES (?, ?, ?, ?, NOW())"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, email);
        pstmt->setInt(3, age);
        pstmt->setString(4, password);  // plain password stored

        pstmt->executeUpdate();
        cout << "User registered successfully\n";

        delete pstmt;
        delete con;
    } catch (sql::SQLException &e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

int loginUser()
{
    string email, password;

    cout << "\n-- USER LOGIN --\n";
    cout << "Enter email: ";
    cin >> email;

    cout << "Enter Password: ";
    cin >> password;

    try {
        sql::Connection* con = getDBConnection();
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT user_id, name FROM users WHERE email = ? AND password = ?"
        );
        pstmt->setString(1, email);
        pstmt->setString(2, password);  // plain password compared

        sql::ResultSet* rs = pstmt->executeQuery();

        if (rs->next()) {
            cout << "Login successful. Welcome " << rs->getString("name") << endl;
            int user_id = rs->getInt("user_id");
            delete rs;
            delete pstmt;
            delete con;
            return user_id;  // return user id on success
        } else {
            cout << "Incorrect email or password.\n";
        }

        delete rs;
        delete pstmt;
        delete con;
    }
    catch (sql::SQLException &e) {
        cerr << "SQL error: " << e.what() << endl;
    }

    return -1;  // login failed
}
