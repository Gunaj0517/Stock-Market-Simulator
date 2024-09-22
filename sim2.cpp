#include<iostream>
#include<string>
#include<map>
#include<ctime>
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
        void addStock(Stock &stock,int qtyowned){
            holdings[stock.getName()]+=qtyowned;
        }
        void removeStock(Stock& stock, int qtyowned){
            if(holdings[stock.getName()]>=qtyowned){
                holdings[stock.getName()]-=qtyowned;
            }
            if(holdings[stock.getName()]==0){
                holdings.erase(stock.getName());
            }
        }
        int getStockQty(Stock& stock){
            if(holdings.find(stock.getName())!=holdings.end()){
                return holdings[stock.getName()];
            }
            return 0;
        }
        void printPortfolio(){
            cout<<endl<<"Trader Portfolio: "<<endl;
            map<string, int>::iterator item;
            for(item=holdings.begin(); item!=holdings.end(); item++){
                cout<<"Stock: "<<item->first <<" | Quantity: "<< item->second<<endl;
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
        Trader(int i, string n, double b) : id(i), name(n), balance(b){}

        bool buyStock(Stock& stock, int qty){
            double totalCost=stock.getPrice()*qty;
            if(balance>=totalCost && stock.getQty()>=qty){
                balance-=totalCost;
                portfolio.addStock(stock, qty);
                stock.updateQty(stock.getQty()-qty);
                cout<<endl<<"Purchased "<<qty<<" of "<<stock.getName()<<" at price "<<stock.getPrice()<<endl;
                return true;
            } 
            else{
                cout << "Insufficient balance or stock quantity!" << endl;
                return false;
            }
        }
        bool sellStock(Stock& stock, int qty){
            if(portfolio.getStockQty(stock)>=qty){
                double totalRevenue=stock.getPrice()*qty;
                balance+=totalRevenue;
                portfolio.removeStock(stock, qty);
                stock.updateQty(stock.getQty()+qty);
                cout<<endl<<"Sold "<<qty<<" of "<<stock.getName()<<" at price "<<stock.getPrice()<<endl;
                return true;
            } 
            else{
                cout<<endl<<"Insufficient stock to sell!"<<endl;
                return false;
            }
        }
        void printPortfolio(){
            portfolio.printPortfolio();
        }
};

class Market{
    private:
        map<string, Stock> mstocks;

    public:
        void addStock(string name, double price, int qty){
            mstocks[name]=Stock(name, price, qty);
        }
        Stock* getStock(string name){
            if(mstocks.find(name)!=mstocks.end()){
                return &mstocks[name];
            }
            return nullptr;
        }
        void printMarket(){
            cout<<endl<<"Stocks Available:"<<endl;
            map<string, Stock>::iterator pair;
            for(pair=mstocks.begin(); pair!=mstocks.end(); pair++){
                pair->second.printStock();
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
            : transid(id), traderName(tname), stockName(sname), qty(q), price(p), transacType(type){
            timestamp = time(0);
        }
        void printTransaction(){
            cout<<endl<<"Transaction ID: "<<transid<<" | Trader: "<<traderName;
            cout<<" | Stock: "<<stockName<<" | Qty: "<<qty;
            cout<<" | Price: "<<price<<" | Type: "<<transacType;
            cout<<" | Timestamp: "<<ctime(&timestamp);
        }
};

int main(){
    Trader T1(1, "Brinda", 10000.0);
    Trader T2(2, "Gunaj", 10000.0);
    Trader T3(3, "Parth", 10000.0);
    Trader T4(4, "Yashi", 10000.0);

    Market market;
    market.addStock("AAPL", 150.0, 1000);   //Apple
    market.addStock("MSFT", 300.0, 1200);   // Microsoft
    market.addStock("TSLA", 750.0, 800);    // Tesla
    market.addStock("AMZN", 3500.0, 400);   // Amazon
    market.addStock("NFLX", 590.0, 600);    // Netflix
    market.addStock("FB", 365.0, 900);      // Facebook (Meta)
    market.addStock("NVDA", 220.0, 1500);   // Nvidia
    market.addStock("DIS", 175.0, 700);     // Disney
    market.addStock("ORCL", 85.0, 1000);    // Oracle

    market.printMarket();
    
    Stock* appleStock=market.getStock("AAPL");
    if(appleStock)
        T2.buyStock(*appleStock, 10);
    
    Stock* teslaStock = market.getStock("TSLA");
    if(teslaStock) 
        T1.sellStock(*teslaStock, 5); // Insufficient stock example

    T2.printPortfolio();
    market.printMarket();
    
    Transaction t1(1, "John Doe", "AAPL", 10, 150.0, "BUY");
    t1.printTransaction();
    
    return 0;
}

