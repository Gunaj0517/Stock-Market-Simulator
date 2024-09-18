#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <iostream>
using namespace std;

// Stock class
class Stock {
private:
    string name;
    string sector;
    double price;
    int qtyavail;
    double dividend;

public:
    Stock(string nm, string sec, double p, int qty, double div) 
        : name(nm), sector(sec), price(p), qtyavail(qty), dividend(div) {}

    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQtyAvail() const { return qtyavail; }
    double getDividend() const { return dividend; }

    void updatePrice(double newPrice) { price = newPrice; }
    void updateQuantity(int newQty) { qtyavail = newQty; }

    void display() const {
        cout << "Stock: " << name 
             << ", Sector: " << sector 
             << ", Price: " << price 
             << ", Quantity Available: " << qtyavail 
             << ", Dividend: " << dividend << endl;
    }
};

#endif
