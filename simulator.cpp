#include<iostream>
#include<cstring>
#include<map>
#include<ctime>
using namespace std;

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
};

class Trader{
    private:
    int id;
    string name;
    double balance;
    map<Stock,int>assets;
    public:

};

class Market{
    private:
    map<string,Stock>mstocks;
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
