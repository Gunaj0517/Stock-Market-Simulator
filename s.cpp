#include <iostream>
#include <map>
#include <ctime>
#include <string>
using namespace std;

// Forward declaration for use in Transaction class
class Stock;
class Trader;

// Stock class representing individual stocks
class Stock {
private:
    string name;
    double price;
    int qtyavail;

public:
    Stock() {}
    Stock(string n, double p, int q) : name(n), price(p), qtyavail(q) {}

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int getQty() {
        return qtyavail;
    }

    void updatePrice(double p) {
        price = p;
    }

    void updateQty(int q) {
        qtyavail = q;
    }

    void printStock() {
        cout << "Stock: " << name << " | Price: " << price << " | Available Qty: " << qtyavail << endl;
    }
};

// Trader class to manage a trader's portfolio and transactions
class Trader {
private:
    string name;
    double balance;
    map<string, int> portfolio; // key: stock name, value: quantity owned

public:
    Trader() {}
    Trader(string tname, double bal) : name(tname), balance(bal) {}

    string getName() {
        return name;
    }

    double getBalance() {
        return balance;
    }

    bool buyStock(Stock &stock, int qty) {
        double totalCost = stock.getPrice() * qty;
        if (balance >= totalCost && stock.getQty() >= qty) {
            balance -= totalCost;
            portfolio[stock.getName()] += qty;
            stock.updateQty(stock.getQty() - qty);
            cout << "Purchased " << qty << " of " << stock.getName() << " at price " << stock.getPrice() << endl;
            return true;
        } else {
            cout << "Insufficient balance or stock quantity!" << endl;
            return false;
        }
    }

    bool sellStock(Stock &stock, int qty) {
        if (portfolio[stock.getName()] >= qty) {
            double totalRevenue = stock.getPrice() * qty;
            balance += totalRevenue;
            portfolio[stock.getName()] -= qty;
            stock.updateQty(stock.getQty() + qty);
            cout << "Sold " << qty << " of " << stock.getName() << " at price " << stock.getPrice() << endl;
            return true;
        } else {
            cout << "Insufficient stock to sell!" << endl;
            return false;
        }
    }

    void showPortfolio() {
        cout << "\n" << name << "'s Portfolio:" << endl;
        for (auto const &stock : portfolio) {
            cout << "Stock: " << stock.first << " | Quantity: " << stock.second << endl;
        }
        cout << "Balance: $" << balance << endl;
    }
};

// Market class that contains available stocks
class Market {
private:
    map<string, Stock> stocks;

public:
    void addStock(Stock s) {
        stocks[s.getName()] = s;
    }

    void updateStockPrice(string name, double newPrice) {
        if (stocks.find(name) != stocks.end()) {
            stocks[name].updatePrice(newPrice);
        } else {
            cout << "Stock not found in the market." << endl;
        }
    }

    Stock* getStock(string name) {
        if (stocks.find(name) != stocks.end()) {
            return &stocks[name];
        } else {
            cout << "Stock not found!" << endl;
            return nullptr;
        }
    }

    void listStocks() {
        cout << "\nMarket Stock List:" << endl;
        for (auto &entry : stocks) {
            entry.second.printStock();
        }
    }
};

// Transaction class for logging transactions
class Transaction {
private:
    static int transactionCounter;
    int transactionID;
    Trader trader;
    Stock stock;
    int qty;
    string type;
    time_t timestamp;

public:
    Transaction(Trader t, Stock s, int q, string transactionType)
        : trader(t), stock(s), qty(q), type(transactionType) {
        transactionID = ++transactionCounter;
        timestamp = time(0);
    }

    void logTransaction() {
        cout << "\nTransaction ID: " << transactionID << endl;
        cout << "Trader: " << trader.getName() << endl;
        cout << "Stock: " << stock.getName() << endl;
        cout << "Quantity: " << qty << endl;
        cout << "Transaction Type: " << type << endl;
        cout << "Timestamp: " << ctime(&timestamp);
    }
};

int Transaction::transactionCounter = 0;

int main() {
    // Create market and add stocks
    Market market;
    market.addStock(Stock("AAPL", 150.0, 100));  // Apple stock
    market.addStock(Stock("GOOG", 2800.0, 50));  // Google stock
    market.addStock(Stock("AMZN", 3400.0, 30));  // Amazon stock

    // List stocks in the market
    market.listStocks();

    // Create a trader with an initial balance
    Trader trader("John Doe", 10000.0);

    // Trader buys Apple stock
    Stock* appleStock = market.getStock("AAPL");
    if (appleStock != nullptr) {
        trader.buyStock(*appleStock, 5);  // Buying 5 shares of Apple
        Transaction t1(trader, *appleStock, 5, "Buy");
        t1.logTransaction();
    }

    // Trader sells Google stock (error case: Trader doesn't own Google stock yet)
    Stock* googleStock = market.getStock("GOOG");
    if (googleStock != nullptr) {
        trader.sellStock(*googleStock, 1);  // Trying to sell 1 share of Google
    }

    // Update stock prices in the market
    market.updateStockPrice("AAPL", 155.0);  // Apple price updated to $155
    market.updateStockPrice("GOOG", 2900.0);  // Google price updated to $2900

    // List updated stocks in the market
    market.listStocks();

    // Trader buys Google stock after price update
    if (googleStock != nullptr) {
        trader.buyStock(*googleStock, 1);  // Buying 1 share of Google
        Transaction t2(trader, *googleStock, 1, "Buy");
        t2.logTransaction();
    }

    // Show trader's portfolio and balance
    trader.showPortfolio();

    return 0;
}
