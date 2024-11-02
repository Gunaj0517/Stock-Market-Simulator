#include<iostream>
#include<cstring>
#include<map>
#include<ctime>
#include<fstream>
#include<vector>
#include"linkedlistfunction.cpp"

#include <cstdlib> //for using system()

using namespace std;
const char* exePath = "C:\\Users\\ICAI\\Desktop\\coding_imp\\Stock-Market-Simulator\\trial\\StockMarketSimulator.exe";

Node *STOCKS=createStockList();

class Trader;
void portfolio(Trader &t);
class Stock{
    private:
    string name;
    double price;
    int qtyavail;
    public:
    void updatePrice(double p){
        price = p;
    }
    void updateQty(int q){
        qtyavail = q;
    }
    double getPrice(){
        return price;
    }
    int getqty(){
        return qtyavail;
    }
public:
    void returnStocks()
    {
        cout<<name<<price<<qtyavail;
    }
};
class Trader{
private:
    string id;
    string name;
    string password;
    double balance;
    map<string,int,int>assets;
    //
public:
    friend void portfolio(Trader &t);
    void createUser() {
    ofstream file("user_data.txt", ios::app); // Append mode to add multiple users
    
    balance = 15000;
    cout << "Welcome To The Simulator" << endl;
    cout << "Create your ID: ";
    cin >> id;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Create your password: ";
    cin >> password;

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    // Write user details to file in a structured way
    file << id << " " << name << " " << password << " " << balance << endl;
    file.close();

    cout << "Account created successfully and your current balance is: "<<balance<<" !" << endl;
}

bool checkPasswordMatch(const string& inputID, const string& inputPassword) {
    ifstream file("user_data.txt");

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return false;
    }

    string id, name, storedPassword;
    int balance;
    bool matchFound = false;

    // Read each line and extract user details
    while (file >> id >> name >> storedPassword >> balance) {
        // Check if the ID matches, then check if the password matches
        if (id == inputID) {
            matchFound = (inputPassword == storedPassword);
            if (matchFound) {
                this->id = id;
                this->name = name; // Use retrieved name
                this->balance = balance; // Use retrieved balance
        }
        break; 
    }
    }
    file.close();
    return matchFound;
}
    void login()
    {
        string id, password;
        cout<<"Enter your Login ID: ";
        cin>>id;
        cout<<"Enter your Password: ";
        cin>>password;
        if(checkPasswordMatch(id,password)){
            cout << "Logined successfully  !" << endl;
            portfolio(*this);
        }
        else{
            cout << "Re-Enter your ID and Password!" << endl;
            login();
        }
    }
    
};

class Market{
    private:
    map<string,Stock>stocks;
};

class Transaction{
    int transid;
    Trader trader;
    Stock stock;
    int qty;
    double price;
    string transacType;
    //date datatype ka idkkkk, bakery management wala dat time ka code ctrl c + ctrl v kerlete haiiiiiii :))))
    public:
    
};

void buystock(Trader &t1)
{
    int stockChoice;
    cout << "Choose the stock you want to view for purchase:\n";
    cout << "1) AAPL   2) GOOGL   3) MSFT   4) AMZN   5) META\n";
    cout << "6) TSLA   7) NFLX    8) NVDA   9) DIS    10) JPM\n";
    cout << "Enter the number of the stock: ";
    cin >> stockChoice;
    string symbols[MAX_STOCKS] = {"AAPL", "GOOGL", "MSFT", "AMZN", "META", "TSLA", "NFLX", "NVDA", "DIS", "JPM"};
    switch(stockChoice)
    {
        case 1:
        {
            if (stockChoice >= 1 && stockChoice <= MAX_STOCKS) {
                string selectedSymbol = symbols[stockChoice - 1];
                STOCKS.(head, selectedSymbol);
                cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
                cin >> quantity;
                cout << "You selected to buy " << quantity << " units of " << selectedSymbol << ".\n";
            } else {
                cout << "Invalid choice.\n";
            }
            break;

        }
        case 2:
        {
            int qty;
            cout<<"enter quantity you want to buy for GOOGL:";
            cin>>qty;
            break;
        }
        case 3:
        {
            int qty;
            cout<<"enter quantity you want to buy for MSFT:";
            cin>>qty;
            break;
        }
        case 4:
        {
            int qty;
            cout<<"enter quantity you want to buy for AMZN:";
            cin>>qty;
            break;
        }
        case 5:
        {
            int qty;
            cout<<"enter quantity you want to buy for META:";
            cin>>qty;
            break;
        }
        case 6:
        { 
            int qty;
            cout<<"enter quantity you want to buy for TSLA:";
            cin>>qty;
            break;
        }
        case 7:
        {
            int qty;
            cout<<"enter quantity you want to buy for NFLX:";
            cin>>qty;
            break;
        }
        case 8:
        {
            int qty;
            cout<<"enter quantity you want to buy for NVDA:";
            cin>>qty;
            break;
        }
        case 9:
        {
            int qty;
            cout<<"enter quantity you want to buy for DIS:";
            cin>>qty;
            break;
        }
        case 10:
        {
            int qty;
            cout<<"enter quantity you want to buy for JPM:";
            cin>>qty;
            break;
        }
    }
}

void portfolio(Trader &t)
{
    cout<<"Welcome "<<t.name<<endl;
    cout<<"Your current balance is: "<<t.balance<<endl;
    int ch;
    cout<<"enter your choice: 1)view stock 2)buy stock 3)sell stock";
    cin>>ch;
    if(ch==1)
    {
        
    }
    else if(ch==2)
    {
        int result = 0;//system(exePath);
        if (result == 0) {
            std::cout << "Simulator executed successfully." << std::endl;
            buystock(t);
        } else {
            std::cerr << "Failed to execute the simulator." << std::endl;
        }
        
    }
    else if(ch==3)
    {

    }
}

int main(){
    
    Trader t;
    //t.createUser();
    t.login();
}