#include <iostream>
#include <cstring>
#include <map>
#include <ctime>
#include <fstream>
#include <vector>
#include "linkedlistfunction.h"

#include <cstdlib> // for using system()

using namespace std;
const char* exePath = "C:\\Users\\ICAI\\Desktop\\coding_imp\\Stock-Market-Simulator\\trial\\StockMarketSimulator.exe";

Node *STOCKS = createStockList();
class Trader;
void portfolio(Trader &t);

class Stock {
private:
    string symbol;
    double price;
    int qtyavail;
public:
    Stock(const string &sym, double pr, int qty) : symbol(sym), price(pr), qtyavail(qty) {}

    void updatePrice(double p) { price = p; }
    void updateQty(int q) { qtyavail = q; }
    double getPrice() const { return price; }
    int getQty() const { return qtyavail; }
    string getSymbol() const { return symbol; }

    void displayStock() const {
        cout << "Symbol: " << symbol << ", Price: " << price << ", Quantity Available: " << qtyavail << endl;
    }
};

class Trader {
private:
    string id;
    string name;
    string password;
    double balance;

public:
    friend void portfolio(Trader &t);
    friend void sell(Trader &t2);
    friend void buystock(Trader &t1);
    friend void updateUserBalance(Trader &t);
    friend void viewstock(Trader &t1);
    friend void processStockPurchase(Trader &t1, int stockChoice, const string &selectedSymbol, Node *STOCKS);

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

        cout << "Account created successfully and your current balance is: " << balance << " !" << endl;
    }

    bool checkPasswordMatch(const string& inputID, const string& inputPassword) {
        ifstream file("user_data.txt");

        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return false;
        }

        string storedID, storedName, storedPassword;
        double storedBalance;
        bool matchFound = false;

        // Read each line and extract user details
        while (file >> storedID >> storedName >> storedPassword >> storedBalance) {
            // Check if the ID matches, then check if the password matches
            if (storedID == inputID) {
                matchFound = (inputPassword == storedPassword);
                if (matchFound) {
                    id = storedID;
                    name = storedName;
                    balance = storedBalance;
                }
                break;
            }
        }
        file.close();
        return matchFound;
    }

    void login() {
        string inputID, inputPassword;
        cout << "Enter your Login ID: ";
        cin >> inputID;
        cout << "Enter your Password: ";
        cin >> inputPassword;
        if (checkPasswordMatch(inputID, inputPassword)) {
            cout << "Logged in successfully!" << endl;
            portfolio(*this);
        } else {
            cout << "Re-enter your ID and Password!" << endl;
            login();
        }
    }

    // Save purchase to file as a Trader member function
    void savePurchaseToFile(const Stock &stock, int quantity) {
        ofstream file("trader_portfolio.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Error opening file to save purchase." << endl;
            return;
        }
        cout << "Saving to file: " << id << " " << stock.getSymbol() << " " << stock.getPrice()
             << " " << quantity << " " << balance << endl;

        file << id << " " << stock.getSymbol() << " " << stock.getPrice() << " " << quantity << " " << balance << endl;
        file.close();
    }

    // View portfolio as a Trader member function
    void viewPortfolio(Trader &t) {
        ifstream file("trader_portfolio.txt");
        if (!file.is_open()) {
            cerr << "Error opening portfolio file." << endl;
            return;
        }

        cout << "Reading portfolio for ID: " << id << endl;
        string traderID, stockSymbol;
        double stockPrice;
        int stockQuantity;
        bool hasStocks = false;

        while (file >> traderID >> stockSymbol >> stockPrice >> stockQuantity >> balance) {
            if (traderID == id) {
                hasStocks = true;
                cout << stockSymbol << "\t" << stockPrice << "\t " << stockQuantity << endl;
                portfolio(t);
            }
        }

        if (!hasStocks) {
            cout << "No stocks in your portfolio.\n";
            portfolio(t);
        }
        file.close();
    }
};

class Market {
private:
    map<string, Stock> stocks;
};

Node* findStockNode(Node *head, const string &symbol) {
    Node *current = head;
    while (current != nullptr) {
        if (current->symbol == symbol) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void updateUserBalance(Trader &t) {
    // Read current user data
    ifstream file("user_data.txt");
    ofstream tempFile("temp_user_data.txt");
    
    if (!file.is_open() || !tempFile.is_open()) {
        cerr << "Error opening files." << endl;
        return;
    }

    string storedID, storedName, storedPassword;
    double storedBalance;

    // Update balance for the trader
    while (file >> storedID >> storedName >> storedPassword >> storedBalance) {
        if (storedID == t.id) {
            storedBalance = t.balance; // Update balance for the current trader
        }
        // Write back to temp file
        tempFile << storedID << " " << storedName << " " << storedPassword << " " << storedBalance << endl;
    }

    file.close();
    tempFile.close();

    // Replace the original file with the updated one
    remove("user_data.txt");
    rename("temp_user_data.txt", "user_data.txt");
}

void processStockPurchase(Trader &t1, int stockChoice, const string &selectedSymbol, Node *STOCKS) {
    show(STOCKS, selectedSymbol);
    Node *selectedStockNode = findStockNode(STOCKS, selectedSymbol);
    if (selectedStockNode == nullptr) {
        cout << "Stock not found!" << endl;
        return;
    }

    Stock selectedStock(selectedSymbol, selectedStockNode->price, selectedStockNode->qtyAvailable);

    cout << "Enter quantity you want to buy for " << selectedSymbol << ": ";
    int quantity;
    cin >> quantity;

    if (selectedStock.getQty() < quantity) {
        cout << "Quantity exceeded. Choose between 0 and " << selectedStock.getQty() << ":\n";
        buystock(t1);
    } else {
        int total = quantity * selectedStock.getPrice();
        if (t1.balance >= total) {
            t1.balance -= total;
            t1.savePurchaseToFile(selectedStock, quantity);
            updateUserBalance(t1); // Update user balance in the user_data.txt
            cout << "Purchase successful! New balance: " << t1.balance << "\n";
            portfolio(t1);
        } else {
            cout << "Insufficient balance.\n" << endl;
            buystock(t1);
        }
    }
}

void buystock(Trader &t1) {
    int stockChoice;
    cout << "Choose the stock you want to view for purchase:\n";
    cout << "1) AAPL   2) GOOGL   3) MSFT   4) AMZN   5) META\n";
    cout << "6) TSLA   7) NFLX    8) NVDA   9) DIS    10) JPM\n";
    cout << "Enter the number of the stock: ";
    cin >> stockChoice;

    string symbols[10] = {"AAPL", "GOOGL", "MSFT", "AMZN", "META", "TSLA", "NFLX", "NVDA", "DIS", "JPM"};

    if (stockChoice >= 1 && stockChoice <= 10) {
        string selectedSymbol = symbols[stockChoice - 1];
        processStockPurchase(t1, stockChoice, selectedSymbol, STOCKS);
    } else {
        cout << "Invalid choice.\n";
        buystock(t1);
    }
}

void sell(Trader &t2) {
    cout << "Your current portfolio:\n";
    t2.viewPortfolio(t2);

    string stockSymbol;
    cout << "Enter the symbol of the stock you want to sell: ";
    cin >> stockSymbol;

    Node *stockNode = findStockNode(STOCKS, stockSymbol);
    if (stockNode == nullptr) {
        cout << "Stock not found!\n";
        return;
    }

    // Check how much of the stock the trader owns
    ifstream file("trader_portfolio.txt");
    if (!file.is_open()) {
        cerr << "Error opening portfolio file." << endl;
        return;
    }

    string traderID;
    double stockPrice;
    int stockQuantity;
    bool foundStock = false;
    int traderStockQuantity = 0; // To track how much the trader has

    // Read through the portfolio to find the stock
    while (file >> traderID >> stockSymbol >> stockPrice >> stockQuantity >> t2.balance) {
        if (traderID == t2.id && stockSymbol == stockNode->symbol) {
            traderStockQuantity = stockQuantity;
            foundStock = true;
            break;
        }
    }

    file.close();

    if (!foundStock) {
        cout << "You don't own any shares of " << stockSymbol << endl;
        return;
    }

    cout << "You own " << traderStockQuantity << " shares of " << stockSymbol << endl;
    int sellQuantity;
    cout << "Enter the quantity you want to sell (max " << traderStockQuantity << "): ";
    cin >> sellQuantity;

    if (sellQuantity > traderStockQuantity || sellQuantity <= 0) {
        cout << "Invalid quantity!\n";
        return;
    }

    // Update trader's balance and save to file
    double sellPrice = stockNode->price;
    t2.balance += sellPrice * sellQuantity; // Update the balance

    // Update the trader's portfolio
    ofstream outFile("trader_portfolio_temp.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening temp portfolio file." << endl;
        return;
    }

    ifstream inFile("trader_portfolio.txt");
    if (!inFile.is_open()) {
        cerr << "Error opening original portfolio file." << endl;
        return;
    }

    // Copy data to a temporary file and update stock quantity
    while (inFile >> traderID >> stockSymbol >> stockPrice >> stockQuantity >> t2.balance) {
        if (traderID == t2.id && stockSymbol == stockNode->symbol) {
            // Subtract the quantity being sold
            stockQuantity -= sellQuantity;
            if (stockQuantity > 0) {
                outFile << traderID << " " << stockSymbol << " " << stockPrice << " " << stockQuantity << " " << t2.balance << endl;
            } else {
                // If quantity is zero, don't write the stock
                cout << "All shares of " << stockSymbol << " sold.\n";
            }
        } else {
            // Copy the stock entry as is
            outFile << traderID << " " << stockSymbol << " " << stockPrice << " " << stockQuantity << " " << t2.balance << endl;
        }
    }

    inFile.close();
    outFile.close();

    // Rename temp file to original file
    remove("trader_portfolio.txt");
    rename("trader_portfolio_temp.txt", "trader_portfolio.txt");

    // Make sure to update the user balance in the user_data.txt after the sale
    updateUserBalance(t2); // This will ensure the user's balance is saved properly
    cout << "Sale successful! New balance: " << t2.balance << endl;
    portfolio(t2);
}

void portfolio(Trader &t) {
    cout << "Welcome " << t.name << endl;
    cout << "Your current balance is: " << t.balance << endl;
    int ch;
    cout << "Enter your choice: 1) View stock 2) Buy stock 3) Sell stock 4) Exit\n";
    cin >> ch;
    if (ch == 1) {
        t.viewPortfolio(t);
    } else if (ch == 2) {
        int result = 0; // Uncomment if system(exePath) is used
        if (result == 0) {
            cout << "Simulator executed successfully." << endl;
            buystock(t);
        } else {
            cerr << "Failed to execute the simulator." << endl;
        }
    } else if (ch == 3) {
        sell(t);
    } else {
        exit(0);
    }
}

int main() {
    Trader trader;
    int choice;
    cout << "1) Create Account  2) Login\n";
    cout << "Enter choice: ";
    cin >> choice;
    if (choice == 1) {
        trader.createUser();
    } else if (choice == 2) {
        trader.login();
    } else {
        cout << "Invalid choice.\n";
    }
    return 0;
}

/* g++ simulator.cpp linkedlistfunction.cpp -o simulator -DMAIN_FUNCTION_LINKEDLIST */