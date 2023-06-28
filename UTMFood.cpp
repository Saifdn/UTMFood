/****************************** UTM FOOD ******************************\
Project: UTMFood
Programming Technique II
Semester 2, 2022/2023

Section: 06
Member 1's Name: AHMAD SAIFUDIN BIN NARDI SUSANTO A22EC0035
Member 2's Name: MOHD DANIAL HAKIM BIN ZAHARI A22EC0077
Member 3's Name: LIO KOCK HOCK A22EC0185

<Implementation File>
Class definition, function definition, overloading operator

See https://github.com/Saifdn/UTMFood.

\***************************************************************************/

#include "UTMFood.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

/*=========================================================
    Function Definition
=========================================================*/
void displayLogo()
{
    cout << "+=============================================+" << endl;
    cout << "|  _   _ _____ __  __ _____ ___   ___  ____   |" << endl;
    cout << "| | | | |_   _|  \\/  |  ___/ _ \\ / _ \\|  _ \\  |" << endl;
    cout << "| | | | | | | | |\\/| | |_ | | | | | | | | | | |" << endl;
    cout << "| | |_| | | | | |  | |  _|| |_| | |_| | |_| | |" << endl;
    cout << "|  \\___/  |_| |_|  |_|_|   \\___/ \\___/|____/  |" << endl;
    cout << "+=============================================+" << endl
         << endl;
}

/*=========================================================
    Definition class Account
=========================================================*/
Account::Account() {}

void Account::setName(string _name) { name = _name; }

string Account::getUsername() { return username; }

string Account::getPassword() { return password; }

string Account::getName() { return name; }

string Account::getAddress() { return address; }

string Account::getEmail() { return email; }

string Account::getPhone() { return phone; }

bool Account::authenticate(string username, string password)
{
    fstream file, file2;
    string un, pw;

    file.open("Vendor/" + username + ".txt", ios::in);
    file2.open("Customer/" + username + ".txt", ios::in);

    file >> un >> pw;
    file2 >> un >> pw;

    file.close();
    file2.close();

    if (un == username && pw == password)
        return 1;
    else
        return 0;
}

void Account::logIn()
{
    string un, pw;
    fstream file;

A:
    cout << "*******************************\n"
         << "        ACCOUNT SIGN IN        \n"
         << "-------------------------------\n";
    cout << "Username: ";
    cin >> un;
    cout << "Password: ";
    cin >> pw;

    if (authenticate(un, pw) == true)
    {
        cout << "\n*You have succesfully sign in!\n"
             << endl;

        file.open("Vendor/" + un + ".txt", ios::in);
        getline(file, username);
        getline(file, password);
        getline(file, name);
        getline(file, address);
        getline(file, email);
        getline(file, phone);
        file.close();
    }
    else
    {
        cout << "*The password is incorrect" << endl;
        goto A;
    }
}

void Account::signUp()
{
    cout << "**********************************\n"
         << "        CREATE NEW ACCOUNT        \n"
         << "----------------------------------\n";
    cin.ignore();

    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    cout << "Enter full name: ";
    getline(cin, name);
    cout << "Enter address : ";
    getline(cin, address);
    cout << "Enter email   : ";
    getline(cin, email);
    cout << "Enter phone   : ";
    getline(cin, phone);
}

/*=========================================================
    Definition class Customer
=========================================================*/
Customer::Customer() {}

Customer::Customer(string _username, string _password, string _name, string _address, string _email, string _phone)
{
    username = _username;
    password = _password;
    name = _name;
    address = _address;
    email = _email;
    phone = _phone;
}

void Customer::createAccount()
{
    fstream file;

    signUp();
    file.open("Customer/" + username + ".txt", ios::out);
    file << username << endl
         << password << endl
         << name << endl
         << address << endl
         << email << endl
         << phone << endl;
    file.close();
}

/*=========================================================
    Definition class Vendor
=========================================================*/
Vendor::Vendor() {}

Vendor::Vendor(string _username, string _password, string _name, string _address, string _email, string _phone)
{
    username = _username;
    password = _password;
    name = _name;
    address = _address;
    email = _email;
    phone = _phone;
}

void Vendor::createAccount()
{
    fstream file;

    signUp();
    file.open("Vendor/" + username + ".txt", ios::out);
    file << username << endl
         << password << endl
         << name << endl
         << address << endl
         << email << endl
         << phone << endl;
    file.close();
}

string *Vendor::displayVendor()
{
    fstream file;
    string line;
    int vendorNum = 0;

    file.open("Menu/listVendor.txt", ios::in);
    while (getline(file, line))
    {
        vendorNum++;
    }
    file.close();

    int id[vendorNum];
    string *vendorName = new string[vendorNum];

    file.open("Menu/listVendor.txt", ios::in);

    for (int i = 0; i < vendorNum; i++)
    {
        getline(file, line, ' ');
        id[i] = stoi(line);

        getline(file, line);
        vendorName[i] = line;
    }
    file.close();

    for (int i = 0; i < vendorNum; i++)
    {
        cout << left
             << setw(2) << id[i]
             << setw(20) << vendorName[i] << endl;
    }

    return vendorName;
}

void Vendor::stallSelection()
{
    system("CLS");
    displayLogo();

    cout << "********************************\n"
         << "        AVAILABLE VENDOR        \n"
         << "--------------------------------\n";

    string *result = displayVendor();

    cout << "*Please Enter Vendor's ID of Your Choice!: ";
    int i;
    cin >> i;

    name = result[i - 1];
}

/*=========================================================
    Definition class MenuItem
=========================================================*/
MenuItem::MenuItem(Vendor _vendor)
{
    id = new int[50];
    foodName = new string[50];
    price = new float[50];
    vendor = &_vendor;
}
MenuItem::~MenuItem()
{
    delete[] id;
    delete[] foodName;
    delete[] price;
}

string MenuItem::getFoodName(int i) { return foodName[i]; }

int MenuItem::getFoodNum() { return foodNum; }

float MenuItem::getPrice(int i) { return price[i]; }

void MenuItem::displayMenu()
{
    string line;

    file.open("Menu/" + vendor->getName() + ".txt", ios::in);
    while (getline(file, line))
    {
        foodNum++;
    }
    file.close();

    file.open("Menu/" + vendor->getName() + ".txt", ios::in);
    for (int i = 0; i < foodNum; i++)
    {
        getline(file, line, ',');
        id[i] = stoi(line);

        getline(file, line, ',');
        foodName[i] = line;

        getline(file, line);
        price[i] = stof(line);
    }
    file.close();

    system("CLS");
    displayLogo();
    cout << "****************************************\n"
         << "                MENU LIST               \n"
         << "----------------------------------------\n";

    for (int i = 0; i < foodNum; i++)
    {
        cout << left
             << setw(2) << id[i]
             << setw(30) << foodName[i]
             << right
             << setw(3) << "RM "
             << fixed << setprecision(2)
             << setw(5) << price[i] << endl;
    }
}

void MenuItem::vendorMenuInput()
{
    char choice = 'y';

    file.open("Menu/" + vendor->getName() + ".txt", ios::out);

    system("CLS");
    displayLogo();
    cout << "**********************************\n"
         << "          MENU MANAGEMENT         \n"
         << "----------------------------------\n";

    for (int i = 0; choice == 'y' || choice == 'Y'; i++)
    {
        cin.ignore();
        cout << "Name of food: ";
        getline(cin, foodName[i]);
        cout << "Price       : ";
        cin >> price[i];
        cout << "Do you want to enter again (y/n): ";
        cin >> choice;
        cout << endl;

        file << i + 1 << ","
             << foodName[i] << ","
             << price[i] << endl;
    }

    file.close();

    storeListVendor();
}

void MenuItem::storeListVendor()
{
    fstream file;
    string line;
    int vendorNum = 0;
    bool isVendorNameExists = false;

    // Prevent listing vendor name twice
    file.open("Menu/listVendor.txt", ios::in);
    while (getline(file, line))
    {
        // Check if the vendor name already exists in the file
        if (line.find(vendor->getName()) != string::npos)
        {
            isVendorNameExists = true;
            break;
        }
    }
    file.close();

    if (!isVendorNameExists)
    {
        file.open("Menu/listVendor.txt", ios::in);
        while (getline(file, line))
        {
            vendorNum++;
        }
        file.close();

        file.open("Menu/listVendor.txt", ios::app);
        file << vendorNum + 1 << " " << vendor->getName() << endl;
        file.close();
    }
}

/*=========================================================
    Definition class OrderItem
=========================================================*/
OrderItem::OrderItem(MenuItem *_MenuItem) { menuItem = _MenuItem; }

void OrderItem::calculateTotalPayment(int i, int count)
{
    totalPayment = totalPayment + menuItem->getPrice(i);
    FoodOrdered[count] = menuItem->getFoodName(i);
    FoodPrice[count] = menuItem->getPrice(i);
}

void OrderItem::foodSelection(int id, int count)
{
    for (int i = 0; i < menuItem->getFoodNum(); i++)
    {
        if (id == i + 1)
        {
            calculateTotalPayment(i, count);
        }
    }
}

void OrderItem::askOrder()
{
    int id;

    cout << "0 Exit" << endl;

    do
    {
        cout << "Enter The ID of Your Desired Food: ";
        cin >> id;
        if (id != 0)
            foodSelection(id, count);
        count++;
    } while (id != 0);
}

/*=========================================================
    Overloading Operator
=========================================================*/
ostream &operator<<(ostream &out, OrderItem orderitem)
{
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);

    system("CLS");
    displayLogo();
    out << "\nHere is your receipt! Thank You!" << endl;

    out << endl
        << "****************************************\n"
        << "              ORDER RECEIPT             \n"
        << "----------------------------------------\n"
        << asctime(ti) << endl
        << endl;

    for (int i = 0; i < orderitem.count - 1; i++)
    {
        out << left
            << setw(2) << i + 1
            << setw(30) << orderitem.FoodOrdered[i]
            << right
            << setw(3) << "RM "
            << setw(5) << orderitem.FoodPrice[i]
            << endl;
    }
    out << setw(32) << "Total: "
        << setw(3) << "RM "
        << setw(5) << orderitem.totalPayment << endl;

    out << "----------------------------------------\n\n"
        << "****************************************\n";

    return out;
}