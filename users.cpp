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

    cout<<"\n--USER REGISTRATION--\n";
    cout<<"Name : ";
    cin.ignore();
    getline(cin,name);
    cout<<"Email : ";
    getline(cin,email);
    cout<<"Age ";
    cin>>age;
    cout<<"Password : ";
    cin.ignore();
    getline(cin,password);

    try {
        sql::Connection* con = getDBConnection();

        //insert User
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO Users(name, email, age, password, created_at) VALUES (?, ?, ?, ?, NOW())"
        );
        pstmt->setString(1, name);
        pstmt->setString(2, email);
        pstmt->setInt(3, age);
        pstmt->setString(4, generateSaltedhash(password));
        //pstmt->setString(4, password);

        pstmt->executeUpdate();
        cout<<"User registered successfully"<<endl;

        delete pstmt;
        delete con;
    } catch (sql::SQLException &e) {
        cerr <<"SQL Error: "<< e.what() << endl;
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

    string hashedPassword = generateSaltedhash(password);  // hash the entered password

    try {
        sql::Connection* con = getDBConnection();
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "SELECT * FROM users WHERE email = ? AND password = ?"
        );
        pstmt->setString(1, email);
        sql::ResultSet* rs = pstmt->executeQuery();

        if (rs->next()) {
            string storedPassword = rs->getString("password");
            if (storedPassword == hashedPassword) {
                int user_id = rs->getInt("user_id");
                cout << "Login successful!\n";
                delete con;
                delete pstmt;
                delete rs;
                return user_id;
            } else {
                cout << "Incorrect password.\n";
            }
        } else {
            cout << "Username not found.\n";
        }

        delete con;
        delete pstmt;
        delete rs;
    }
    catch (sql::SQLException &e) {
        cerr << "SQL error: " << e.what() << endl;
    }

    return -1;  // login failed
}

