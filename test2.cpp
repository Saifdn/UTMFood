// AHMAD SAIFUDIN BIN NARDI SUSANTO
// LIO KOCK HOCK
// DANIAL HAKIM BIN ZAHARI
// PROJECT UTM FOOD
// updated 2.0

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#define DATA 6

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
        void setName(string _name) {name = _name;}
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
                fstream file;
                file.open("Vendor/"+un+".txt", ios::in);

                getline(file, username);
                getline(file, password);
                getline(file, name);
                getline(file, address);
                getline(file, email);
                getline(file, phone);
                file.close();

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

        // NEW: DisplayVendor!
        string* DisplayVendor(){
            fstream file;
            string line;
            int vendorNum = 0;

            file.open("Menu/listVendor.txt", ios::in);

            while(getline(file, line)){
                vendorNum++;
            }

            file.close();
            int id[vendorNum];
            string* vendorName = new string[vendorNum];

            file.open("Menu/listVendor.txt", ios::in);

            for(int i=0; i<vendorNum; i++){
                getline(file, line, ' ');
                id[i] = stoi(line);

                getline(file, line);
                vendorName[i] = line;
            }
            file.close();

            for(int i = 0; i < vendorNum; i++){
                cout<<left
                    <<setw(2)<<id[i]
                    <<setw(20)<<vendorName[i]<<endl;
            }

            return vendorName;
        }

        void StallSelection(){
            string* result = DisplayVendor();

            cout<<"These are the Stall only stall available in UTM"<<endl;
            cout<<"Enter your choice: "<<endl;
            int i;
            cin>>i;

            name = result[i-1];
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
        MenuItem(Vendor _vendor){
            id = new int[50];
            foodName = new string[50];
            price = new float[50];
            vendor = &_vendor;
        }
        ~MenuItem(){
            delete [] id;
            delete [] foodName;
            delete [] price;
        }

        string getFoodName(int i){return foodName[i];}

        int getFoodNum(){return foodNum;}

        float getPrice(int i){return price[i];}

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

            // cout<<"VENDOR: "<<vendor->getName()<<endl; //check
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

            StoreListVendor();
        }

        // NEW: Store the newly registered vendor's stall
        void StoreListVendor()
        {
            fstream file;
            string line;
            int vendorNum = 0;
            bool isVendorNameExists = false;

            // UPDATE: Prevent listing vendor name twice
            file.open("Menu/listVendor.txt", ios::in);
            while (getline(file, line)) {
                // Check if the vendor name already exists in the file
                if (line.find(vendor->getName()) != string::npos) {
                    isVendorNameExists = true;
                    break;
                }
            }
            file.close();

            if(!isVendorNameExists){
                file.open("Menu/listVendor.txt", ios::in);
                while(getline(file, line)){
                    vendorNum++;
                }
                file.close();

                file.open("Menu/listVendor.txt", ios::app);
                file<<vendorNum+1<<" "<<vendor->getName()<<endl;
                file.close();
            }
            
        }

};

class OrderItem
{
    private:
        float totalPayment=0;
        string FoodOrdered[100];
        float FoodPrice[100];
        MenuItem* menuItem;
        
    public:
        OrderItem(MenuItem *menuitem)
        {
            menuItem = menuitem;
        }

        void calculateTotalPayment(int i, int count){
            totalPayment = totalPayment + menuItem->getPrice(i);
            FoodOrdered[count] = menuItem->getFoodName(i);
            FoodPrice[count] = menuItem->getPrice(i);
        }

        void FoodSelection(int id, int count)
        {
            for(int i=0; i<menuItem->getFoodNum(); i++)
            {
                if(id == i+1)
                {
                    calculateTotalPayment(i, count);
                }
            }
        }

        void AskOrder()
        {
            int id, count=0;
            cout<<"0 Exit"<<endl;
            do
            { 
                cout<<"\nEnter the id of your desired food!!"<<endl;
                cin>>id;
                if(id!=0)
                    FoodSelection(id, count);
                count++;
            }while(id!=0);
            
            cout<<"\nHere is your receipt! Thank You!"<<endl;
            for(int i=0; i<count-1; i++)
            {
                cout<<i+1<<". "<<FoodOrdered[i]<<"   RM"<<FoodPrice[i]<<endl;
            }
            cout<<"Total payment = "<<totalPayment;
        }
};

void displayLogo4(){
    cout << "+=============================================+"<<endl;
    cout << "|  _   _ _____ __  __ _____ ___   ___  ____   |" << endl;
    cout << "| | | | |_   _|  \\/  |  ___/ _ \\ / _ \\|  _ \\  |" << endl;
    cout << "| | | | | | | | |\\/| | |_ | | | | | | | | | | |" << endl;
    cout << "| | |_| | | | | |  | |  _|| |_| | |_| | |_| | |" << endl;
    cout << "|  \\___/  |_| |_|  |_|_|   \\___/ \\___/|____/  |" << endl;
    cout << "+=============================================+"<<endl<<endl;
}


int main(){

    Account *acc;
    Customer customer;
    Vendor vendor;
    int choice;

    system("CLS");
    displayLogo4();
    cout<<"+==================+"<<endl
        <<" Menu"<<endl
        <<"+==================+"<<endl
        <<"1. Registration"<<endl
        <<"2. Log In"<<endl
        <<"Enter choice: ";
    cin>>choice;
    
    if(choice == 1){

        system("CLS");
        displayLogo4();
        cout<<"+==================+"<<endl
            <<" Registration"<<endl
            <<"+==================+"<<endl
            <<"1. Customer"<<endl
            <<"2. Vendor"<<endl
            <<"Enter choice: ";
        cin>>choice;

        if(choice == 1){
            acc = &customer;
            acc->createAccount();
        }
        else{
            acc = &vendor;
            acc->createAccount();
        }
    }

    
    else{

        system("CLS");
        displayLogo4();
        cout<<"+==================+"<<endl
            <<" Sign In"<<endl
            <<"+==================+"<<endl
            <<"1. Customer"<<endl
            <<"2. Vendor"<<endl
            <<"Enter choice: ";
        cin>>choice;

        if(choice == 1){
            customer.logIn();
            // Display vendor available in utmfood
            vendor.StallSelection();
            // Display menu available from the vendor
            MenuItem menuitem(vendor);
            menuitem.displayMenu();
            OrderItem orderitem(&menuitem);
            orderitem.AskOrder();
        }
        else{
            vendor.logIn();
            MenuItem menuItem(vendor);
            menuItem.VendorMenuInput();
            menuItem.displayMenu();
        }
    }
    return 0;
}
