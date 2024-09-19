#include<iostream>
#include<cstring>
#include<map>
using namespace std;
class Stock{
    private:
    string name;
    double price;
    int qtyavail;

    public:
    Stock(){}
    Stock(string n, double p, int q) : name(n), price(p), qtyavail(q){}
    void updatePrice(double p){
        price = p;
    }
    void updateQty(int q){
        qtyavail = q;
    }
    double getPrice(){
        return price;
    }
    int getQty(){
        return qtyavail;
    }
    void printStock(){
        cout<<"Stock: "<<name<<" | Price: "<<price<<" | Available Qty: "<<qtyavail<<endl;
    }
    string getName(){
        return name;
    }
    
};

class Portfolio {
    private:
        map<string, int> holdings; 
    public:
        void addStock(Stock &stock, int qty) {
            holdings[stock.getName()] += qty;
        }

        void removeStock(Stock& stock, int qty) {
            if (holdings[stock.getName()] >= qty) {
                holdings[stock.getName()] -= qty;
            }
            if (holdings[stock.getName()] == 0) {
                holdings.erase(stock.getName());
            }
        }

        int getStockQty(Stock& stock) {
            if (holdings.find(stock.getName()) != holdings.end()) {
                return holdings[stock.getName()];
            }
            return 0;
        }

        void printPortfolio() {
            for (auto& item : holdings) {
                cout<<"Stock: "<<item.first<<" | Quantity: "<<item.second<<endl;
            }
        }
};

class Trader{
    private:
    int id;
    string name;
    double balance;
    Portfolio portfolio;
    public:
        Trader(int traderId, string traderName, double initBalance) : id(traderId), name(traderName), balance(initBalance) {}

        bool buyStock(Stock& stock, int qty) {
            double totalCost = stock.getPrice() * qty;
            if (balance >= totalCost && stock.getQty() >= qty) {
                balance -= totalCost;
                portfolio.addStock(stock, qty);
                stock.updateQty(stock.getQty() - qty);
                cout<<"Purchased "<<qty<<" of "<<stock.getName()<<" at price "<<stock.getPrice()<<endl;
                return true;
            } 
            else{
                cout<<"Insufficient balance or stock quantity!"<<endl;
                return false;
            }
        }

        bool sellStock(Stock& stock, int qty) {
            if (portfolio.getStockQty(stock) >= qty) {
                double totalRevenue = stock.getPrice() * qty;
                balance += totalRevenue;
                portfolio.removeStock(stock, qty);
                stock.updateQty(stock.getQty() + qty);
                cout << "Sold " << qty << " of " << stock.getName() << " at price " << stock.getPrice() << endl;
                return true;
            } 
            else {
                cout << "Insufficient stock to sell!" << endl;
                return false;
            }
        }

        void printPortfolio() {
            portfolio.printPortfolio();
        }
};

class Market{
    private:
        map<string, Stock> mstocks;
    public:
        void addStock(string name, double price, int qty) {
            mstocks[name] = Stock(name, price, qty);
        }

        Stock* getStock(string name) {
            if (mstocks.find(name) != mstocks.end()) {
                return &mstocks[name];
            }
            return nullptr;
        }

        void printMarket() {
            for (auto& pair : mstocks) {
                pair.second.printStock();
            }
        }
};

class Transaction {
    private:
        int transid;
        string traderName;
        string stockName;
        int qty;
        double price;
        string transacType; 
        time_t timestamp;
    public:
        Transaction(int id, string tname, string sname, int q, double p, string type)
            : transid(id), traderName(tname), stockName(sname), qty(q), price(p), transacType(type) {
            timestamp = time(0); // current time
        }

        void printTransaction() const {
            cout << "Transaction ID: " << transid << " | Trader: " << traderName
                 << " | Stock: " << stockName << " | Qty: " << qty 
                 << " | Price: " << price << " | Type: " << transacType
                 << " | Timestamp: " << ctime(&timestamp);
        }
};

int main() {
    // Example Usage
    Market market;
    market.addStock("AAPL", 150.0, 1000);
    market.addStock("TSLA", 750.0, 500);
    
    Trader trader(1, "John Doe", 10000.0);
    
    Stock* appleStock = market.getStock("AAPL");
    if (appleStock) 
        trader.buyStock(*appleStock, 10);
    
    Stock* teslaStock = market.getStock("TSLA");
    if (teslaStock) 
        trader.sellStock(*teslaStock, 5); // Insufficient stock example

    trader.printPortfolio();
    market.printMarket();
    
    Transaction t1(1, "John Doe", "AAPL", 10, 150.0, "BUY");
    t1.printTransaction();
    
    return 0;
}

