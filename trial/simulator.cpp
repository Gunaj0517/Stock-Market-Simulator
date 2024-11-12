#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <vector>
#include <conio.h>
#include "linkedlistfunction.h"

#include <cstdlib> // for using system()

using namespace std;/*
const char *exePath = "\"C:\\Users\\TARUN TIWARI\\OneDrive\\Desktop\\Stock-Market-Simulator\\trial\\simulator.exe\"";
const char *exeFluctuator = "\"C:\\Users\\TARUN TIWARI\\OneDrive\\Desktop\\Stock-Market-Simulator\\trial\\fluctuator.exe\"";
const char *exePredictor = "\"C:\\Users\\TARUN TIWARI\\OneDrive\\Desktop\\Stock-Market-Simulator\\trial\\predictor.exe\"";
*/

const char *exePath = "C:\\Users\\ICAI\\Desktop\\coding_imp\\Stock-Market-Simulator\\trial\\StockMarketSimulator.exe";
const char *exeFluctuator = "C:\\Users\\ICAI\\Desktop\\coding_imp\\Stock-Market-Simulator\\trial\\fluctuator.exe";
const char *exePredictor = "C:\\Users\\ICAI\\Desktop\\coding_imp\\Stock-Market-Simulator\\trial\\predictor.exe";

void Cleardisplay()
{
    system("cls"); // Clear the console screen
}
void clearScreen()
{
    cout << "\e[1mPRESS ANY KEY TO CONTINUE...\e[m";
    getch();
    Cleardisplay();
}
void blue()
{
    printf("\033[0;34m");
}
void purple()
{
    printf("\033[0;35m");
}
void red()
{
    printf("\033[0;31m");
}
void green()
{
    printf("\033[0;32m");
}
void yellow()
{
    printf("\033[0;33m");
}
void reset()
{
    printf("\033[0m");
}
void highlight()
{
    printf("\033[0;41m");
}

Node *STOCKS = createStockList();
class Trader;
void portfolio(Trader &t);

class Stock
{
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

    void displayStock() const
    {
        cout << "Symbol: " << symbol << ", Price: " << price << ", Quantity Available: " << qtyavail << endl;
    }
};

class Trader
{
private:
    string id;
    string name;
    string password;
    double balance;

public:
    friend void returnPortfolioValues(Trader &t);
    friend void portfolio(Trader &t);
    friend void sell(Trader &t2);
    friend void buystock(Trader &t1);
    friend void updateUserBalance(Trader &t);
    friend void processStockPurchase(Trader &t1, int stockChoice, const string &selectedSymbol, Node *STOCKS);

    void login()
    {
        string inputID, inputPassword;
        cout << "Enter your Login ID: ";
        cin >> inputID;
        cout << "Enter your Password: ";
        cin >> inputPassword;
        if (checkPasswordMatch(inputID, inputPassword))
        {
            Cleardisplay();
            green();
            cout << endl
                 << "                                                                                   \e[1mLogged in Successfully!\e[m" << endl;
            reset();
            cout << endl;
            portfolio(*this);
        }
        else
        {
            cout << "Re-enter your ID and Password!" << endl;
            login();
        }
    }

    void createUser()
    {
        ofstream file("user_data.txt", ios::app); // Append mode to add multiple users
        balance = 15000;
        cout << "\n\n\n\e[1;31m+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "                                                                                                                                                                                         "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "                                                                                                                                                                                         "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "                                                                                                                                                                                         "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "                                                                                                                                                                                         "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "\e[1;33m                                                                                       WELCOME  TO  STOCK  MARKET  SIMULATOR    \e[m                                                                                    "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "                                                                                                                                                                                         "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "                                                                                                                                                                                         "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "                                                                                                                                                                                         "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m"
             << "\e[m"
             << "                                                                                                                                                                                         "
             << "\e[1;31m"
             << "\e[m\n";
        cout << "\e[1;31m+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\e[m";
        cout << endl
             << endl
             << endl
             << endl;
        clearScreen();
        cout << "Enter your name : ";
        cin >> name;
        cout << "Create your ID : ";
        cin >> id;
        cout << "Create your password : ";
        cin >> password;

        if (!file.is_open())
        {
            cerr << "Error opening file." << endl;
            return;
        }

        // Write user details to file in a structured way
        file << id << " " << name << " " << password << " " << balance << endl;
        file.close();
        green();
        cout << "Account created successfully and your current balance is : " << balance << " !" << endl;
        reset();
        clearScreen();
        login();
    }

    bool checkPasswordMatch(const string &inputID, const string &inputPassword)
    {
        ifstream file("user_data.txt");

        if (!file.is_open())
        {
            cerr << "Error opening file." << endl;
            return false;
        }

        string storedID, storedName, storedPassword;
        double storedBalance;
        bool matchFound = false;

        // Read each line and extract user details
        while (file >> storedID >> storedName >> storedPassword >> storedBalance)
        {
            // Check if the ID matches, then check if the password matches
            if (storedID == inputID)
            {
                matchFound = (inputPassword == storedPassword);
                if (matchFound)
                {
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

    // Save purchase to file as a Trader member function
    void savePurchaseToFile(const Stock &stock, int quantity)
    {
        ofstream file("trader_portfolio.txt", ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file to save purchase." << endl;
            return;
        }
        cout << "Saving to file: " << id << " " << stock.getSymbol() << " " << stock.getPrice()
             << " " << quantity << " " << balance << endl;

        file << id << " " << stock.getSymbol() << " " << stock.getPrice() << " " << quantity << " " << balance << endl;
        file.close();
    }

    // View portfolio as a Trader member function
    void viewPortfolio(Trader &t)
    {
        ifstream file("trader_portfolio.txt");
        if (!file.is_open())
        {
            cerr << "Error opening portfolio file." << endl;
            return;
        }

        Cleardisplay();
        yellow();
        cout << endl
             << endl
             << "Reading portfolio for ID: " << id << endl
             << endl;
        reset();
        string traderID, stockSymbol;
        double stockPrice;
        int stockQuantity;
        bool hasStocks = false;
        cout << "                                                    x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n";
        yellow();
        cout << endl
             << endl
             << endl
             << "\t\t\t\t\t                       Stock     Stock Price        Stock Quantity    Balance";
        reset();
        while (file >> traderID >> stockSymbol >> stockPrice >> stockQuantity >> balance)
        {
            if (traderID == id)
            {
                hasStocks = true;
                blue();
                cout << "\n                                                                " << stockSymbol << "\t   " << stockPrice << "\t\t " << stockQuantity << "\t\t" << balance << endl;
                reset();
            }
        }
        cout << "\n\n\n                                                    x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n";
        if (!hasStocks)
        {
            cout << "No stocks in your portfolio.\n"
                 << endl
                 << endl;
            portfolio(*this);
        }
        file.close();
    }
};

Node *findStockNode(Node *head, const string &symbol)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->symbol == symbol)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void updateUserBalance(Trader &t)
{
    // Read current user data
    ifstream file("user_data.txt");
    ofstream tempFile("temp_user_data.txt");

    if (!file.is_open() || !tempFile.is_open())
    {
        cerr << "Error opening files." << endl;
        return;
    }

    string storedID, storedName, storedPassword;
    double storedBalance;

    // Update balance for the trader
    while (file >> storedID >> storedName >> storedPassword >> storedBalance)
    {
        if (storedID == t.id)
        {
            storedBalance = t.balance;
            cout << "Updating balance for user: " << storedID << " to " << storedBalance << endl;
        }
        else
        {
            cout << "No match for user: " << storedID << " (expected: " << t.id << ")" << endl;
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

void processStockPurchase(Trader &t1, int stockChoice, const string &selectedSymbol, Node *STOCKS)
{
    show(STOCKS, selectedSymbol);
    Node *selectedStockNode = findStockNode(STOCKS, selectedSymbol);
    if (selectedStockNode == nullptr)
    {
        cout << "Stock not found!" << endl;
        return;
    }

    Stock selectedStock(selectedSymbol, selectedStockNode->price, selectedStockNode->qtyAvailable);
    // stock object

    cout << "Enter quantity you want to buy for " << selectedSymbol << " : ";
    int quantity;
    cin >> quantity;

    if (selectedStock.getQty() < quantity)
    {
        cout << "Quantity exceeded. Choose between 0 and " << selectedStock.getQty() << " :\n";
        buystock(t1);
    }
    else
    {
        int total = quantity * selectedStock.getPrice();
        if (t1.balance >= total)
        {
            t1.balance -= total;
            t1.savePurchaseToFile(selectedStock, quantity);
            updateUserBalance(t1); // Update user balance in the user_data.txt
            cout << "Purchase successful! New balance: " << t1.balance << "\n";
            portfolio(t1);
        }
        else
        {
            cout << "Insufficient balance.\n"
                 << endl;
            buystock(t1);
        }
    }
}

void buystock(Trader &t1)
{
    int stockChoice;
    cout << "Choose the stock you want to view for purchase:\n";
    cout << "1) AAPL   2) GOOGL   3) MSFT   4) AMZN   5) META\n";
    cout << "6) TSLA   7) NFLX    8) NVDA   9) DIS    10) JPM\n";
    cout << endl;
    cout << "Enter the number of the stock: ";
    cin >> stockChoice;

    string symbols[10] = {"AAPL", "GOOGL", "MSFT", "AMZN", "META", "TSLA", "NFLX", "NVDA", "DIS", "JPM"};

    if (stockChoice >= 1 && stockChoice <= 10)
    {
        string selectedSymbol = symbols[stockChoice - 1];
        processStockPurchase(t1, stockChoice, selectedSymbol, STOCKS);
    }
    else
    {
        cout << "Invalid choice.\n";
        buystock(t1);
    }
}

void sell(Trader &t2)
{
    std::cout << "Your current portfolio :\n";
    t2.viewPortfolio(t2);

    std::string stockSymbol;
    std::cout << "Enter the symbol of the stock you want to sell : ";
    std::cin >> stockSymbol;

    Node *stockNode = findStockNode(STOCKS, stockSymbol);
    if (stockNode == nullptr)
    {
        std::cout << "Stock not found!\n";
        portfolio(t2);
        return; // Added return to prevent further execution
    }

    std::ifstream file("trader_portfolio.txt");
    if (!file.is_open())
    {
        std::cerr << "Error opening portfolio file.\n";
        return;
    }

    std::string traderID;
    double stockPrice;
    int stockQuantity;
    bool foundStock = false;
    int traderStockQuantity = 0;
    int bal = 0;

    // Read through the portfolio to find the stock
    while (file >> traderID >> stockSymbol >> stockPrice >> stockQuantity >> bal)
    {
        if (traderID == t2.id && stockSymbol == stockNode->symbol)
        {
            traderStockQuantity = stockQuantity;
            foundStock = true;
            break;
        }
    }

    file.close();

    if (!foundStock)
    {
        std::cout << "You don't own any shares of " << stockSymbol << "\n";
        return;
    }

    std::cout << "You own " << traderStockQuantity << " shares of " << stockSymbol << "\n";
    int sellQuantity;
    std::cout << "Enter the quantity you want to sell (max " << traderStockQuantity << "): ";
    std::cin >> sellQuantity;

    if (sellQuantity > traderStockQuantity || sellQuantity <= 0)
    {
        std::cout << "Invalid quantity!\n";
        return;
    }

    double sellPrice = stockNode->price;
    t2.balance += (sellPrice * sellQuantity); // Update the balance

    std::ofstream outFile("trader_portfolio_temp.txt");
    if (!outFile.is_open())
    {
        std::cerr << "Error opening temp portfolio file.\n";
        return;
    }

    std::ifstream inFile("trader_portfolio.txt");
    if (!inFile.is_open())
    {
        std::cerr << "Error opening original portfolio file.\n";
        return;
    }

    // Copy data to a temporary file and update stock quantity
    while (inFile >> traderID >> stockSymbol >> stockPrice >> stockQuantity >> bal)
    {
        if (traderID == t2.id && stockSymbol == stockNode->symbol)
        {
            stockQuantity -= sellQuantity;
            if (stockQuantity > 0)
            {
                outFile << traderID << " " << stockSymbol << " " << stockPrice << " " << stockQuantity << " " << t2.balance << "\n";
            }
            else
            {
                std::cout << "All shares of " << stockSymbol << " sold.\n";
            }
        }
        else
        {
            outFile << traderID << " " << stockSymbol << " " << stockPrice << " " << stockQuantity << " " << bal << "\n";
        }
    }

    inFile.close();
    outFile.close();

    // Ensure the file streams are closed before renaming
    if (std::remove("trader_portfolio.txt") != 0)
    {
        std::cerr << "Error deleting original portfolio file.\n";
    }
    else if (std::rename("trader_portfolio_temp.txt", "trader_portfolio.txt") != 0)
    {
        std::cerr << "Error renaming temp file to portfolio file.\n";
    }
    else
    {
        std::cout << "Sale successful! New balance: " << t2.balance << "\n";
        portfolio(t2);
        updateUserBalance(t2); // Update the user balance
    }
}

void returnPortfolioValues(Trader &t)
{
    ifstream file("user_data.txt");
    if (!file.is_open())
    {
        cerr << "Error: Could not open file.\n";
        return;
    }

    string id, name, password;
    double balance;
    bool found = false;

    while (file >> id >> name >> password >> balance)
    {
        if (id == t.id)
        {
            t.name = name;
            t.password = password;
            t.balance = balance;
            cout << "\n\n\n\e[1;31m+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "                                                                                                                                                                                         "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "                                                                                                                                                                                         "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "                                                                                                                                                                                         "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "                                                                                                                                                                                         "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "\e[1;33m                                                                                          WELCOME      \e[m                                                                                    "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "\e[1;33m                                                                                           " << name << "  \e[m                                                                                     "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "                                                                                                                                                                                         "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "                                                                                                                                                                                         "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "                                                                                                                                                                                         "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m"
                 << "\e[m"
                 << "                                                                                                                                                                                         "
                 << "\e[1;31m"
                 << "\e[m\n";
            cout << "\e[1;31m+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\e[m";
            cout << endl
                 << endl
                 << endl
                 << endl;
            cout << "\e[1mYOUR CURRENT BALANCE IS : " << balance << "\e[m" << endl
                 << endl
                 << endl
                 << endl
                 << endl;
            clearScreen();
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "ID not found.\n";
    }

    file.close();
}

void portfolio(Trader &t)
{
    returnPortfolioValues(t);
    int ch;
    cout << "\e[1;35m                                                                                      +====================================+\e[m" << endl;
    cout << "\e[1;35m                                                                                      |                                    |\e[m" << endl;
    cout << "\e[1;35m                                                                                      |                                    |\e[m" << endl;
    cout << "\e[1;35m                                                                                      |\e[m             1)View Stock           \e[1;35m|\e[m" << endl;
    cout << "\e[1;35m                                                                                      |\e[m             2)Buy Stock            \e[1;35m|\e[m" << endl;
    cout << "\e[1;35m                                                                                      |\e[m             3)Sell Stock           \e[1;35m|\e[m" << endl;
    cout << "\e[1;35m                                                                                      |\e[m             4)Fluctuator           \e[1;35m|\e[m" << endl;
    cout << "\e[1;35m                                                                                      |\e[m             5)Predictor            \e[1;35m|\e[m" << endl;
    cout << "\e[1;35m                                                                                      |\e[m             6)Exit                 \e[1;35m|\e[m" << endl;
    cout << "\e[1;35m                                                                                      |                                    |\e[m" << endl;
    cout << "\e[1;35m                                                                                      |                                    |\e[m" << endl;
    cout << "\e[1;35m                                                                                      +====================================+\e[m" << endl;
    cout << endl
         << endl
         << "\e[1mEnter your choice : \e[m";
    cin >> ch;
    if (ch == 1)
    {
        t.viewPortfolio(t);
        clearScreen();
        portfolio(t);
    }
    else if (ch == 2)
    {
        Cleardisplay();
        yellow();
        int result = 0;//system(exePath);
        if (result == 0)
        {
            cout << "Simulator executed successfully." << endl;
            reset();
            cout << endl;
            buystock(t);
        }
        else
        {
            cerr << "Failed to execute the simulator." << endl;
        }
    }
    else if (ch == 3)
    {
        Cleardisplay();
        sell(t);
    }
    else if (ch == 4)
    {
        Cleardisplay();
        system(exeFluctuator);
        clearScreen();
        portfolio(t);
    }
    else if (ch == 5)
    {
        Cleardisplay();
        system(exePredictor);
        clearScreen();
        portfolio(t);
    }
    else
    {
        exit(0);
    }
}

int main()
{
    Trader trader;
    Cleardisplay();
    int choice;
    cout << "\e[1;35m                                                                                      +====================================+\e[m" << endl;
    cout << "\e[1;35m                                                                                      |                                    |\e[m" << endl;
    cout << "\e[1;35m                                                                                      |                                    |\e[m" << endl;
    cout << "\e[1;35m                                                                                      |\e[m            1)Create Account        \e[1;35m|\e[m" << endl;
    cout << "\e[1;35m                                                                                      |\e[m            2)Login                 \e[1;35m|\e[m" << endl;
    cout << "\e[1;35m                                                                                      |                                    |\e[m" << endl;
    cout << "\e[1;35m                                                                                      |                                    |\e[m" << endl;
    cout << "\e[1;35m                                                                                      +====================================+\e[m" << endl;
    cout << endl
         << endl
         << "\e[1mEnter your choice : \e[m";
    cin >> choice;
    if (choice == 1)
    {
        Cleardisplay();
        trader.createUser();
    }
    else if (choice == 2)
    {
        Cleardisplay();
        trader.login();
    }
    else
    {
        cout << "Invalid choice.\n";
    }
    return 0;
}

/* g++ simulator.cpp linkedlistfunction.cpp -o simulator -DMAIN_FUNCTION_LINKEDLIST */
