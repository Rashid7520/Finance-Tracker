#include <iostream>
#include <string>
#include "users.h"
#include "transaction.h"
#include "budget.h"
#include "summary.h"
#include "db.h"

using namespace std;

int loggedInUserID = -1; // Global user ID to track login

void displayWelcomeMenu()
{
    cout << "\n================================" << endl;
    cout << " Welcome to Finance Management System" << endl;
    cout << "================================" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

void displayDashboard()
{
    cout << "\n================================" << endl;
    cout << " Dashboard - Finance Management" << endl;
    cout << "================================" << endl;
    cout << "1. Add Transaction" << endl;
    cout << "2. View Transactions" << endl;
    cout << "3. Set Budget" << endl;
    cout << "4. View Budget" << endl;
    cout << "5. Monthly Summary" << endl;
    cout << "6. Logout" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    int choice;

    while (true)
    {
        if (loggedInUserID == -1)
        {
            displayWelcomeMenu();
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            switch (choice)
            {
                case 1:
                    registerUser();
                    break;

                case 2:
                    loggedInUserID = loginUser();
                    break;

                case 3:
                    cout << "Exiting... Bye Bye 👋" << endl;
                    return 0;

                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
        else
        {
            displayDashboard();
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            switch (choice)
            {
                case 1:
                    addTransaction(loggedInUserID);
                    break;

                case 2:
                    viewTransactions(loggedInUserID);
                    break;

                case 3:
                    addBudget(loggedInUserID);
                    break;

                case 4:
                    viewBudget(loggedInUserID);
                    break;

                case 5:
                    viewSummary(loggedInUserID);
                    break;

                case 6:
                    cout << "Logged out successfully.\n";
                    loggedInUserID = -1;
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }

    return 0;
}
