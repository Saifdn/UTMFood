/****************************** UTM FOOD ******************************\
Project: UTMFood
Programming Technique II
Semester 2, 2022/2023

Section: 06
Member 1's Name: AHMAD SAIFUDIN BIN NARDI SUSANTO A22EC0035
Member 2's Name: MOHD DANIAL HAKIM BIN ZAHARI A22EC0077
Member 3's Name: LIO KOCK HOCK A22EC0185

<Application File>
Main program

See https://github.com/Saifdn/UTMFood.

\***************************************************************************/

#include "UTMFood.hpp"
#include <iostream>

using namespace std;

int main()
{
    Account *acc;
    Customer customer;
    Vendor vendor;
    int choice;
    char end;

    do
    {
        system("CLS");
        displayLogo();
        cout << "+===================+" << endl
             << "      Main Menu" << endl
             << "+===================+" << endl
             << "1. Registration" << endl
             << "2. Log In" << endl
             << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {

            system("CLS");
            displayLogo();
            cout << "+==================+" << endl
                 << "    Registration" << endl
                 << "+==================+" << endl
                 << "1. Customer" << endl
                 << "2. Vendor" << endl
                 << "Enter choice: ";
            cin >> choice;

            if (choice == 1)
            {
                system("CLS");
                displayLogo();
                acc = &customer;
                acc->createAccount();
            }
            else
            {
                system("CLS");
                displayLogo();
                acc = &vendor;
                acc->createAccount();
            }
        }

        else
        {

            system("CLS");
            displayLogo();
            cout << "+==================+" << endl
                 << "      Sign In" << endl
                 << "+==================+" << endl
                 << "1. Customer" << endl
                 << "2. Vendor" << endl
                 << "Enter choice: ";
            cin >> choice;

            if (choice == 1)
            {
                system("CLS");
                displayLogo();
                customer.logIn();
                // Display vendor available in utmfood
                vendor.stallSelection();
                // Display menu available from the vendor
                MenuItem menuitem(vendor);
                menuitem.displayMenu();
                OrderItem orderitem(&menuitem);
                orderitem.askOrder();
                cout << orderitem;
            }
            else
            {
                system("CLS");
                displayLogo();
                vendor.logIn();
                MenuItem menuItem(vendor);
                menuItem.vendorMenuInput();
                menuItem.displayMenu();
            }
        }

        cout<<"\nDo you want to continue the program (y/n): ";
        cin>>end;

    } while (end == 'y' || end == 'Y');

    system("PAUSE");
    return 0;
}