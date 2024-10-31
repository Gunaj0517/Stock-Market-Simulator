#include<iostream>
#include<cstring>
#include<map>
#include<ctime>
#include<fstream>
#include<vector>
#include<cstdlib>
#include"curl_wrapper.h"

#include <cstdlib> //for using system()

using namespace std;
const char* exePath = "C:\\Users\\ICAI\\Desktop\\coding_imp\\Stock-Market-Simulator\\trial\\StockMarketSimulator.exe";
class Trader;
class Market;
void portfolio(Trader &t,Market &m);
class Stock{
    private:
    string name;
    double price;
    int qtyavail;
    public:
    void updatePrice(double p){
        price = p;
    }
   
public:
    void returnStocks()
    {
        cout<<name<<price<<qtyavail;
    }
    void setDetails(const string& stockName, double stockPrice, int quantity) {
        name = stockName;
        price = stockPrice;
        qtyavail = quantity;
    }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQtyAvail() const { return qtyavail; }
    void updateQty(int quantity) {
        qtyavail = quantity;
    }
};
class Trader{
private:
    string id;
    string name;
    string password;
    double balance;
    map<string,int>assets;
public:
    friend void portfolio(Trader &t,Market &m);
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
            cout << "Logged in successfully  !" << endl;
        }
        else{
            cout << "Re-Enter your ID and Password!" << endl;
            login();
        }
    }
    
    double getbalance() const{return balance;}
    void updateBalance(double amount) { balance -= amount; }
    void addAsset(const string& stockName, int quantity) { assets[stockName] += quantity; }
};

class Market{
    private:
    vector<Stock>stocks;
    public:
    void loadStocks(const vector<string>& symbols, const string& apiKey) {
        for (const auto& symbol : symbols) {
            Stock stock;
            json stockData = fetchStockData(symbol, apiKey); // Fetching data
            stock.setDetails(symbol, stockData["price"], stockData["qtyavail"]);
            stocks.push_back(stock);
        }
    }

    void displayStocks() const {
        int index = 1;
        for (const auto& stock : stocks) {
            cout << index++ << ") " << stock.getName()
                 << " - Price: $" << stock.getPrice()
                 << ", Available Qty: " << stock.getQtyAvail() << endl;
        }
    }

    Stock& getStockByChoice(int choice) {
        return stocks[choice - 1];
    }

    int getStockCount() const { return stocks.size(); }
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

void buystock(Trader &t, Market &market) {
    int choice;
    market.displayStocks(); // Show available stocks
    cout << "Enter your choice for which you want to buy stock: ";
    cin >> choice;

    if (choice < 1 || choice > market.getStockCount()) {
        cout << "Invalid choice. Please try again." << endl;
        return;
    }

    Stock &selectedStock = market.getStockByChoice(choice);
    int qty;
    cout << "Enter quantity you want to buy: ";
    cin >> qty;

    // Check if the requested quantity is available
    if (qty > selectedStock.getQtyAvail()) {
        cout << "Not enough stock available." << endl;
        return;
    }

    double totalCost = selectedStock.getPrice() * qty;
    if (t.getbalance() < totalCost) {
        cout << "Insufficient balance to buy " << qty << " shares of " << selectedStock.getName() << endl;
        return;
    }

    // Update trader's balance and stock quantity
    t.updateBalance(totalCost);
    t.addAsset(selectedStock.getName(), qty);
    selectedStock.updateQty(selectedStock.getQtyAvail() - qty); // Decrease available quantity

    cout << "Successfully purchased " << qty << " shares of " << selectedStock.getName() << " at $" << selectedStock.getPrice() << " each." << endl;
    cout << "New balance: $" << t.getbalance() << endl;
}

void portfolio(Trader &t,Market &m)
{
    cout<<"Welcome "<<t.name<<endl;
    cout<<"Your current balance is: "<<t.getbalance()<<endl;
    int ch;
    cout<<"enter your choice: 1)view stock 2)buy stock 3)sell stock";
    cin>>ch;
    if(ch==1)
    {
        
    }
    else if(ch==2)
    {
        int result = system(exePath);
        if (result == 0) {
            std::cout << "Simulator executed successfully." << std::endl;
        } else {
            std::cerr << "Failed to execute the simulator." << std::endl;
        }
        
    }
    else if(ch==3)
    {
        buystock(t,m);
    }
}

int main(){
    
    Trader t;
    Market m;
    vector<string> symbols = {"AAPL", "GOOGL", "MSFT"};
    string apiKey = "YOUR_API_KEY"; // Replace with actual API key
    m.loadStocks(symbols, apiKey);
    t.login();
    portfolio(t, m);
}