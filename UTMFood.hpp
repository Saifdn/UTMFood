/****************************** UTM FOOD ******************************\
Project: UTMFood
Programming Technique II
Semester 2, 2022/2023

Section: 06
Member 1's Name: AHMAD SAIFUDIN BIN NARDI SUSANTO A22EC0035
Member 2's Name: MOHD DANIAL HAKIM BIN ZAHARI A22EC0077
Member 3's Name: LIO KOCK HOCK A22EC0185

<Specification File>
Class declaration

See https://github.com/Saifdn/UTMFood.

\***************************************************************************/

#ifndef UTMFOOD_HPP
#define UTMFOOD_HPP

#include <string>
#include <fstream>

using namespace std;

class Account
{
protected:
    string username;
    string password;
    string name;
    string address;
    string email;
    string phone;

public:
    Account();
    void setName(string);
    string getUsername();
    string getPassword();
    string getName();
    string getAddress();
    string getEmail();
    string getPhone();
    bool authenticate(string, string);
    void logIn();
    void signUp();
    virtual void createAccount() = 0;
};

class Customer : public Account
{
public:
    Customer();
    Customer(string, string, string, string, string, string);
    virtual void createAccount();
};

class Vendor : public Account
{
public:
    Vendor();
    Vendor(string, string, string, string, string, string);
    virtual void createAccount();
    string *displayVendor();
    void stallSelection();
};

class MenuItem
{
private:
    int foodNum = 0;
    int *id;
    string *foodName;
    float *price;
    Vendor *vendor;
    fstream file;

public:
    MenuItem(Vendor);
    ~MenuItem();
    string getFoodName(int);
    int getFoodNum();
    float getPrice(int);
    void displayMenu();
    void vendorMenuInput();
    void storeListVendor();
};

class OrderItem
{
private:
    float totalPayment = 0;
    string FoodOrdered[100];
    float FoodPrice[100];
    MenuItem *menuItem;
    int count = 0;

public:
    OrderItem(MenuItem *);
    void calculateTotalPayment(int, int);
    void foodSelection(int, int);
    void askOrder();
    friend ostream &operator<<(ostream &, OrderItem);
};

void displayLogo();

#endif