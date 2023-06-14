// AHMAD SAIFUDIN BIN NARDI SUSANTO
// LIO KOCK HOCK

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Account{
    protected:
        string username;
        string password;
        string name;
        string address;
        string email;
        string phone;
    public:
        Account(){};
        string getUsername() {return username;}
        string getPassword() {return password;}
        string getName() {return name;}
        string getAddress() {return address;}
        string getEmail() {return email;}
        string getPhone() {return phone;}
        bool authenticate (string username, string password){
            fstream file, file2;
            string un, pw;
            file.open("Vendor/" + username+".txt", ios::in);
            file2.open("Customer/" + username+".txt", ios::in);
            file>>un>>pw;
            file2>>un>>pw;
            file.close();
            file2.close();
            if(un == username && pw == password)
                return 1;
            else
                return 0;
        }
        void logIn(){
            string un, pw;
            cout<<"Enter username: ";
            cin>>un;
            cout<<"Enter password: ";
            cin>>pw;

            if(authenticate(un, pw) == true){
                cout<<"You have succesfully sign in"<<endl;
            }
            else{
                cout<<"The password is incorrect"<<endl;
            }
        }
        void signUp(){
            cin.ignore();
            cout<<"Enter username: ";
            getline(cin, username);
            cout<<"Enter password: ";
            getline(cin, password);
            cout<<"Enter full name: ";
            getline(cin, name);
            cout<<"Enter address : ";
            getline(cin, address);
            cout<<"Enter email   : ";
            getline(cin, email);
            cout<<"Enter phone   : ";
            getline(cin, phone);
        }
        virtual void createAccount() = 0;
};

class Customer: public Account{
    public:
        Customer() {};
        Customer(string _username, string _password, string _name, string _address, string _email, string _phone){
            username = _username;
            password = _password;
            name = _name;
            address = _address;
            email = _email;
            phone = _phone;
        }
        virtual void createAccount(){
            signUp();
            fstream file;
            file.open("Customer/"+username+".txt", ios::out);
            file<<username<<endl
                <<password<<endl
                <<name<<endl
                <<address<<endl
                <<email<<endl
                <<phone<<endl;
            file.close();
        }
};

class Vendor: public Account{
    public:
        Vendor(){}

        Vendor(string _username, string _password, string _name, string _address, string _email, string _phone){
            username = _username;
            password = _password;
            name = _name;
            address = _address;
            email = _email;
            phone = _phone;
        }


        virtual void createAccount(){
            signUp();
            fstream file;
            file.open("Vendor/"+username+".txt", ios::out);
            file<<username<<endl
                <<password<<endl
                <<name<<endl
                <<address<<endl
                <<email<<endl
                <<phone<<endl;
            file.close();
        }
};

// class menuitem
class MenuItem{
    private:
        int foodNum = 0;
        int *id;
        string* foodName;
        float* price;
        Vendor* vendor;
        fstream file;
    public:
        MenuItem(Vendor *_vendor){
            id = new int[50];
            foodName = new string[50];
            price = new float[50];
            vendor = _vendor;
        }
        ~MenuItem(){
            delete [] id;
            delete [] foodName;
            delete [] price;
        }

        string getFoodName(){return *foodName;}

        int getFoodNum(){return foodNum;}

        float getPrice(int i){return price[i];}

        // void setMenu(string food[], float prc[]){
        //     file.open("Menu/"+vendor->getName()+".txt", ios::out);
        //     for(int i = 0; i < foodNum; i++){  
        //         file<<i+1<<","
        //             <<food[i]<<","
        //             <<prc[i]<<endl;
        //     }  
        //     file.close();             
        // }

        void displayMenu(){
            string line;

            file.open("Menu/"+vendor->getName()+".txt", ios::in);
            while(getline(file, line)){
                foodNum++;
            }
            file.close();

            file.open("Menu/"+vendor->getName()+".txt",ios::in);
            for (int i = 0; i < foodNum; i++) {
                getline(file, line, ',');
                id[i] = stoi(line);

                getline(file, line, ',');
                foodName[i] = line;

                getline(file, line);
                price[i] = stof(line);
            }
            file.close();

            for(int i = 0; i < foodNum; i++){
                cout<<left
                    <<setw(2)<<id[i]
                    <<setw(20)<<foodName[i]
                    <<fixed<<setprecision(2)
                    <<setw(6)<<price[i]<<endl;
            }
        }

        void VendorMenuInput(){

            cout<<"VENDOR: "<<vendor->getName()<<endl;
            char choice = 'y';
            file.open("Menu/"+vendor->getName()+".txt", ios::out);
            for(int i = 0 ; choice == 'y' || choice == 'Y'; i++)
            {
                cin.ignore();
                cout<<"Name of food: ";
                getline(cin, foodName[i]);
                cout<<"Price       : ";
                cin>>price[i];
                cout<<"Do you want to enter again (y/n): ";
                cin>>choice;

                file<<i+1<<","
                    <<foodName[i]<<","
                    <<price[i]<<endl;
            }
            file.close();
        }

};

class OrderItem
{
    private:
        float totalPayment = 0;
        MenuItem* menuItem;
        // Order order;
    public:
        OrderItem(MenuItem menuitem)
        {
            menuItem = &menuitem;
        }

        void calculateTotalPayment(int i){
            totalPayment = totalPayment + menuItem->getPrice(i);
        }

        void FoodSelection(int id)
        {
            for(int i=0; i<menuItem->getFoodNum(); i++)
            {
                if(id == i+1)
                {
                    calculateTotalPayment(i);
                }
            }
        }

        void askUser()
        {
            int id;
            cout<<"Enter the id of your desired food!!"<<endl;
            cin>>id;
            FoodSelection(id);

            cout<<"\nTotal payment = "<<totalPayment;
        }
};

class Order{
    private:
        OrderItem orderItem;
    public:

};


int main(){

    int choice;

    cout<<"|| Menu"<<endl
        <<"1. Registration"<<endl
        <<"2. Log In"<<endl
        <<"Enter choice: ";
    cin>>choice;

    Account *customer = new Customer();
    Account *vendor = new Vendor();

    if(choice == 1){
        cout<<"|| Menu"<<endl
        <<"1. Customer"<<endl
        <<"2. Vendor"<<endl
        <<"Enter choice: ";
        cin>>choice;
        if(choice == 1){
            customer->createAccount();
        }
        else{
            vendor->createAccount();
        }
    }
    else{
        cout<<"|| Menu"<<endl
        <<"1. Customer"<<endl
        <<"2. Vendor"<<endl
        <<"Enter choice: ";
        cin>>choice;
        if(choice == 1){
            customer->logIn();
        }
        else{
            vendor->logIn();
            MenuItem menuItem(static_cast<Vendor*>(vendor));
            menuItem.VendorMenuInput();
            menuItem.displayMenu();
        }
    }

    // OrderItem orderitem(menuitem);
    // orderitem.askUser();

    delete customer;
    delete vendor;
    return 0;
}