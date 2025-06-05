#include<iostream>
#include<string>
#include "users.h"
#include "transaction.h"
#include "budget.h"
#include "summary.h"
#include "db.h"
using namespace std;

int loggedInuserID = -1; //set global 

void displayMenu()
{
    cout<<"================================"<<endl;
    cout<<"Welcome to Finance Management System"<<endl;
    cout<<"================================"<<endl;
    cout<<"1. Register"<<endl;
    cout<<"2. Login"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"Enter your choice: ";
}

void displayDashboard()
{
    cout<<"================================"<<endl;
    cout<<"Welcome to Finance Management System Dashboard"<<endl;
    cout<<"================================"<<endl;
    cout<<"1. Add Transaction"<<endl;
    cout<<"2. View Transactions"<<endl;
    cout<<"3. Set Budget"<<endl;
    cout<<"4. View Budget"<<endl;
    cout<<"5. Monthly Summary"<<endl;
    cout<<"6. Logout"<<endl;
    cout<<"Enter your choice: ";
}

int main()
{
    int choice;
    while(true)
    {
        if(loggedInuserID == -1)
        {
            displayMenu();
            cin>>choice;

            switch(choice)
            {
                case 1:
                    registerUser();
                    break;
                case 2:
                    loggedInuserID = loginUser();
                    break;
                case 3:
                    cout<<"Exiting... Bye Bye"<<endl;
                    return 0;
                    break;
                default:
                    cout<<"Invalid choice. Please try"<<endl;
            }
        }
        else
        {
            displayDashboard();
            cin >> choice;
            if(cin.fail()) 
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter a valid number.\n";
                continue;
            }


            switch(choice)
            {
                case 1:
                    addTransaction(loggedInuserID);
                    break;
                case 2:
                    viewTransactions(loggedInuserID);
                    break;
                case 3:
                   addBudget(loggedInuserID);
                   break;
                case 4:
                    viewBudget(loggedInuserID);
                    break;
                case 5:
                    viewSummary(loggedInuserID);
                    break;
                case 6:
                    cout<<"Exiting... Bye Bye"<<endl;
                    loggedInuserID = -1;
                    break;
                default:
                    cout<<"Invalid choice. Please try"<<endl;
            }
        }
    }
    return 0;
}